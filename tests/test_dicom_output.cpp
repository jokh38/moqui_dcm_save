#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include <vector>

// DCMTK includes for DICOM testing
#if DCMTK_FOUND
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmdata/dcfilefo.h"
#include "dcmtk/dcmdata/dcdeftag.h"
#include "dcmtk/ofstd/ofstd.h"
#endif

// Include the moqui_dcm_save library
#include "moqui_dcm_save/library.hpp"

class DicomOutputTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary directory for test files
        test_dir_ = std::filesystem::temp_directory_path() / "moqui_dcm_test";
        std::filesystem::create_directories(test_dir_);

        // Setup test data
        SetupTestData();
    }

    void TearDown() override {
        // Clean up test files
        std::error_code ec;
        std::filesystem::remove_all(test_dir_, ec);
    }

    void SetupTestData() {
        // Create a simple 3D dose distribution (10x10x10)
        test_dimensions_ = {10, 10, 10};
        test_length_ = test_dimensions_[0] * test_dimensions_[1] * test_dimensions_[2];

        test_dose_data_.resize(test_length_);

        // Create a simple dose distribution with a known maximum
        double max_dose = 5.0; // 5 Gy
        for (size_t i = 0; i < test_length_; ++i) {
            // Create a simple gradient pattern
            test_dose_data_[i] = max_dose * (static_cast<double>(i) / test_length_);
        }

        // Setup DICOM info structure
        test_dcm_info_.plan_name = (test_dir_ / "test_plan.dcm").string();
        test_dcm_info_.output_name = "test_dose";

        // Create a mock RTPLAN file for testing
        CreateMockRTPlanFile();
    }

    void CreateMockRTPlanFile() {
        // Create a simple placeholder file for testing
        // In a real scenario, this would be a proper RTPLAN DICOM file
        // For testing purposes, we'll test the fallback behavior when RTPLAN is not available
        std::ofstream file(test_dcm_info_.plan_name);
        if (file.is_open()) {
            file << "# Mock RTPLAN file for testing - this is not a real DICOM file" << std::endl;
            file.close();
        }
    }

    std::filesystem::path test_dir_;
    std::vector<uint32_t> test_dimensions_;
    uint32_t test_length_;
    std::vector<double> test_dose_data_;
    moqui_dcm_save::DicomInfo test_dcm_info_;
};

// Test DCMTK availability
TEST_F(DicomOutputTest, CheckDCMTKAvailability) {
    bool dcmtk_available = moqui_dcm_save::Library::is_dcmtk_available();

    if (dcmtk_available) {
        std::string version = moqui_dcm_save::Library::get_dicom_version();
        EXPECT_FALSE(version.empty()) << "DCMTK version should not be empty";
        std::cout << "DCMTK is available: " << version << std::endl;
    } else {
        std::cout << "DCMTK is not available - tests will use fallback functionality" << std::endl;
    }
}

#if DCMTK_FOUND
// Test successful DICOM file creation
TEST_F(DicomOutputTest, GeneratesValidDoseFile) {
    // Skip test if DCMTK is not available
    if (!moqui_dcm_save::Library::is_dcmtk_available()) {
        GTEST_SKIP() << "DCMTK not available - skipping DICOM-specific test";
    }

    double scale = 1.0;
    bool two_cm_mode = false;

    // Generate the DICOM file
    bool success = moqui_dcm_save::Library::save_dose_as_dicom(
        test_dose_data_, test_dimensions_, scale,
        test_dir_.string(), test_dcm_info_, two_cm_mode);

    EXPECT_TRUE(success) << "DICOM file creation should succeed";

    // Verify the file was created
    std::filesystem::path output_path = test_dir_ / (test_dcm_info_.output_name + ".dcm");
    EXPECT_TRUE(std::filesystem::exists(output_path)) << "DICOM file was not created";

    // Read and verify the DICOM file
    DcmFileFormat read_file;
    OFCondition status = read_file.loadFile(output_path.string().c_str());
    ASSERT_TRUE(status.good()) << "Failed to read generated DICOM file: " << status.text();

    DcmDataset* dataset = read_file.getDataset();
    ASSERT_NE(dataset, nullptr) << "Dataset is null in generated DICOM file";

    // Verify key metadata
    OFString patient_name;
    EXPECT_TRUE(dataset->findAndGetOFString(DCM_PatientName, patient_name).good());
    EXPECT_STREQ(patient_name.c_str(), "TEST^PATIENT");

    OFString sop_class_uid;
    EXPECT_TRUE(dataset->findAndGetOFString(DCM_SOPClassUID, sop_class_uid).good());
    EXPECT_STREQ(sop_class_uid.c_str(), UID_RTDoseStorage);

    // Verify dose grid scaling is present and reasonable
    Float64 dose_grid_scaling;
    EXPECT_TRUE(dataset->findAndGetFloat64(DCM_DoseGridScaling, dose_grid_scaling).good());
    EXPECT_GT(dose_grid_scaling, 0.0) << "Dose grid scaling should be positive";

    // Verify image dimensions
    Uint16 rows, columns;
    EXPECT_TRUE(dataset->findAndGetUint16(DCM_Rows, rows).good());
    EXPECT_TRUE(dataset->findAndGetUint16(DCM_Columns, columns).good());
    EXPECT_EQ(rows, test_dimensions_[1]); // y dimension
    EXPECT_EQ(columns, test_dimensions_[0]); // x dimension

    // Verify pixel data exists
    const Uint16* pixel_data = nullptr;
    unsigned long count = 0;
    EXPECT_TRUE(dataset->findAndGetUint16Array(DCM_PixelData, pixel_data, &count).good());
    EXPECT_EQ(count, test_length_) << "Pixel data length should match dose data length";
    EXPECT_NE(pixel_data, nullptr) << "Pixel data should not be null";

    // Verify UIDs are unique (not equal to the plan UIDs)
    OFString dose_sop_instance_uid;
    EXPECT_TRUE(dataset->findAndGetOFString(DCM_SOPInstanceUID, dose_sop_instance_uid).good());
    EXPECT_STRNE(dose_sop_instance_uid.c_str(), "1.2.3.4.5.6.7.8.9.0.1.2.5");
}

// Test dose grid scaling accuracy
TEST_F(DicomOutputTest, DoseGridScalingIsAccurate) {
    if (!moqui_dcm_save::Library::is_dcmtk_available()) {
        GTEST_SKIP() << "DCMTK not available - skipping DICOM-specific test";
    }

    double scale = 2.0; // Test with scaling factor
    bool two_cm_mode = false;

    bool success = moqui_dcm_save::Library::save_dose_as_dicom(
        test_dose_data_, test_dimensions_, scale,
        test_dir_.string(), test_dcm_info_, two_cm_mode);

    ASSERT_TRUE(success) << "DICOM file creation should succeed";

    // Read the generated file
    std::string output_filename = "dose_scaling_test.dcm";
    std::filesystem::path output_path = test_dir_ / output_filename;

    DcmFileFormat read_file;
    OFCondition status = read_file.loadFile(output_path.string().c_str());
    ASSERT_TRUE(status.good());

    DcmDataset* dataset = read_file.getDataset();

    // Get dose grid scaling
    Float64 dose_grid_scaling;
    ASSERT_TRUE(dataset->findAndGetFloat64(DCM_DoseGridScaling, dose_grid_scaling).good());

    // Get pixel data
    const Uint16* pixel_data = nullptr;
    unsigned long count = 0;
    ASSERT_TRUE(dataset->findAndGetUint16Array(DCM_PixelData, pixel_data, &count).good());

    // Verify scaling: original_dose = pixel_value * dose_grid_scaling / scale
    double original_max_dose = *std::max_element(test_dose_data_.begin(), test_dose_data_.end());
    double scaled_max_dose = original_max_dose * scale;

    // Find maximum pixel value
    Uint16 max_pixel_value = 0;
    for (unsigned long i = 0; i < count; ++i) {
        if (pixel_data[i] > max_pixel_value) {
            max_pixel_value = pixel_data[i];
        }
    }

    // Verify the scaling relationship
    double reconstructed_max_dose = static_cast<double>(max_pixel_value) * dose_grid_scaling;
    EXPECT_NEAR(reconstructed_max_dose, scaled_max_dose, scaled_max_dose * 1e-6)
        << "Dose grid scaling should accurately reconstruct the original dose";
}

// Test TwoCentimeterMode functionality
TEST_F(DicomOutputTest, HandlesTwoCentimeterMode) {
    if (!moqui_dcm_save::Library::is_dcmtk_available()) {
        GTEST_SKIP() << "DCMTK not available - skipping DICOM-specific test";
    }

    double scale = 1.0;
    bool two_cm_mode = true; // Enable TwoCentimeterMode

    bool success = moqui_dcm_save::Library::save_dose_as_dicom(
        test_dose_data_, test_dimensions_, scale,
        test_dir_.string(), test_dcm_info_, two_cm_mode);

    EXPECT_TRUE(success) << "DICOM file creation with TwoCentimeterMode should succeed";

    // Verify file was created successfully
    std::filesystem::path output_path = test_dir_ / (test_dcm_info_.output_name + ".dcm");
    EXPECT_TRUE(std::filesystem::exists(output_path));

    // Read and verify basic DICOM structure
    DcmFileFormat read_file;
    OFCondition status = read_file.loadFile(output_path.string().c_str());
    ASSERT_TRUE(status.good());

    DcmDataset* dataset = read_file.getDataset();

    // Verify it's still a valid RT Dose file
    OFString sop_class_uid;
    EXPECT_TRUE(dataset->findAndGetOFString(DCM_SOPClassUID, sop_class_uid).good());
    EXPECT_STREQ(sop_class_uid.c_str(), UID_RTDoseStorage);
}

// Test metadata extraction from RTPLAN
TEST_F(DicomOutputTest, ExtractsMetadataFromPlan) {
    if (!moqui_dcm_save::Library::is_dcmtk_available()) {
        GTEST_SKIP() << "DCMTK not available - skipping DICOM-specific test";
    }

    double scale = 1.0;
    bool two_cm_mode = false;

    bool success = moqui_dcm_save::Library::save_dose_as_dicom(
        test_dose_data_, test_dimensions_, scale,
        test_dir_.string(), test_dcm_info_, two_cm_mode);

    ASSERT_TRUE(success) << "DICOM file creation should succeed";

    // Read the generated file
    std::filesystem::path output_path = test_dir_ / (test_dcm_info_.output_name + ".dcm");
    DcmFileFormat read_file;
    OFCondition status = read_file.loadFile(output_path.string().c_str());
    ASSERT_TRUE(status.good());

    DcmDataset* dataset = read_file.getDataset();

    // Verify patient information was extracted from plan
    OFString patient_id;
    EXPECT_TRUE(dataset->findAndGetOFString(DCM_PatientID, patient_id).good());
    EXPECT_STREQ(patient_id.c_str(), "TEST12345");

    OFString patient_birth_date;
    EXPECT_TRUE(dataset->findAndGetOFString(DCM_PatientBirthDate, patient_birth_date).good());
    EXPECT_STREQ(patient_birth_date.c_str(), "20000101");

    OFString patient_sex;
    EXPECT_TRUE(dataset->findAndGetOFString(DCM_PatientSex, patient_sex).good());
    EXPECT_STREQ(patient_sex.c_str(), "O");

    // Verify study information was extracted
    OFString study_instance_uid;
    EXPECT_TRUE(dataset->findAndGetOFString(DCM_StudyInstanceUID, study_instance_uid).good());
    EXPECT_STREQ(study_instance_uid.c_str(), "1.2.3.4.5.6.7.8.9.0.1.2.3");

    // Verify Frame of Reference UID was copied
    OFString frame_of_reference_uid;
    EXPECT_TRUE(dataset->findAndGetOFString(DCM_FrameOfReferenceUID, frame_of_reference_uid).good());
    EXPECT_STREQ(frame_of_reference_uid.c_str(), "1.2.3.4.5.6.7.8.9.0.1.2.6");
}

#else
// Test fallback behavior when DCMTK is not available
TEST_F(DicomOutputTest, FallsBackToMHDWhenDCMTKUnavailable) {
    double scale = 1.0;
    bool two_cm_mode = false;

    // Should fall back to MHD format when DCMTK is not available
    bool success = moqui_dcm_save::Library::save_dose_as_dicom(
        test_dose_data_, test_dimensions_, scale,
        test_dir_.string(), test_dcm_info_, two_cm_mode);

    EXPECT_TRUE(success) << "Fallback to MHD should succeed";

    // Should create an MHD file instead of DICOM
    std::filesystem::path mhd_path = test_dir_ / (test_dcm_info_.output_name + ".mhd");
    EXPECT_TRUE(std::filesystem::exists(mhd_path))
        << "Should create MHD file when DCMTK is not available";

    // Should NOT create a DICOM file
    std::filesystem::path dcm_path = test_dir_ / (test_dcm_info_.output_name + ".dcm");
    EXPECT_FALSE(std::filesystem::exists(dcm_path))
        << "Should not create DICOM file when DCMTK is not available";
}
#endif

// Test with different data types (through the library interface)
TEST_F(DicomOutputTest, HandlesDifferentNumericTypes) {
    // Test with different scaling factors
    std::vector<double> scales = {0.5, 1.0, 2.0, 10.0};

    for (double scale : scales) {
        bool success = moqui_dcm_save::Library::save_dose_as_dicom(
            test_dose_data_, test_dimensions_, scale,
            test_dir_.string(), test_dcm_info_, false);

        EXPECT_TRUE(success) << "DICOM/MHD creation should succeed with scale " << scale;
    }
}

// Test edge cases
TEST_F(DicomOutputTest, HandlesEdgeCases) {
    // Test with zero dose data
    std::vector<double> zero_dose_data(test_length_, 0.0);

    double scale = 1.0;
    bool two_cm_mode = false;

    bool success = moqui_dcm_save::Library::save_dose_as_dicom(
        zero_dose_data, test_dimensions_, scale,
        test_dir_.string(), test_dcm_info_, two_cm_mode);

    EXPECT_TRUE(success) << "Zero dose data should be handled gracefully";

#if DCMTK_FOUND
    if (moqui_dcm_save::Library::is_dcmtk_available()) {
        // Verify the file was created
        std::filesystem::path output_path = test_dir_ / (test_dcm_info_.output_name + ".dcm");
        EXPECT_TRUE(std::filesystem::exists(output_path));

        DcmFileFormat read_file;
        OFCondition status = read_file.loadFile(output_path.string().c_str());
        EXPECT_TRUE(status.good());

        // Verify dose grid scaling handles zero dose gracefully
        DcmDataset* dataset = read_file.getDataset();
        Float64 dose_grid_scaling;
        EXPECT_TRUE(dataset->findAndGetFloat64(DCM_DoseGridScaling, dose_grid_scaling).good());
        EXPECT_GT(dose_grid_scaling, 0.0) << "Dose grid scaling should be positive even for zero dose";
    }
#endif
}

// Test error handling
TEST_F(DicomOutputTest, HandlesErrorConditions) {
    // Test with invalid dimensions
    std::vector<uint32_t> invalid_dims = {0, 10, 10};  // Zero dimension
    bool success = moqui_dcm_save::Library::save_dose_as_dicom(
        test_dose_data_, invalid_dims, 1.0,
        test_dir_.string(), test_dcm_info_, false);

    EXPECT_FALSE(success) << "Should fail with invalid dimensions";

    // Test with mismatched data size
    std::vector<double> wrong_size_data(100, 1.0);  // Wrong size
    success = moqui_dcm_save::Library::save_dose_as_dicom(
        wrong_size_data, test_dimensions_, 1.0,
        test_dir_.string(), test_dcm_info_, false);

    EXPECT_FALSE(success) << "Should fail with mismatched data size";

    // Test with empty data
    std::vector<double> empty_data;
    success = moqui_dcm_save::Library::save_dose_as_dicom(
        empty_data, test_dimensions_, 1.0,
        test_dir_.string(), test_dcm_info_, false);

    EXPECT_FALSE(success) << "Should fail with empty data";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
