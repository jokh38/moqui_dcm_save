#include "moqui_dcm_save/library.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

// DICOM Constants
constexpr size_t UID_BUFFER_SIZE = 100;
constexpr uint16_t MAX_16_BIT_VALUE = 65535;
constexpr double MIN_DOSE_SCALING = 1e-6;

#if DCMTK_FOUND
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dcdeftag.h"
#include "dcmtk/dcmdata/dcfilefo.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/ofstd/ofstd.h"
#endif

void moqui_dcm_save::Library::hello() {
    std::cout << "Hello from Library!" << std::endl;
}

auto moqui_dcm_save::Library::add(int first_value, int second_value) -> int {
    return first_value + second_value;
}

auto moqui_dcm_save::Library::is_dcmtk_available() -> bool {
#if DCMTK_FOUND
    return true;
#else
    return false;
#endif
}

auto moqui_dcm_save::Library::get_dicom_version() -> std::string {
#if DCMTK_FOUND
    return "DCMTK " + std::to_string(PACKAGE_VERSION_NUMBER);
#else
    return "DCMTK not available";
#endif
}

auto moqui_dcm_save::Library::save_dose_as_dicom(const std::vector<double>& dose_data,
                                                 const std::vector<uint32_t>& dimensions,
                                                 double scale, const std::string& output_path,
                                                 const DicomInfo& dcm_info, bool two_cm_mode)
    -> bool {
#if DCMTK_FOUND
    try {
        // Validate inputs
        if (dose_data.empty() || dimensions.size() != 3) {
            std::cerr << "Error: Invalid dose data or dimensions" << std::endl;
            return false;
        }

        uint32_t total_length = dimensions[0] * dimensions[1] * dimensions[2];
        if (dose_data.size() != total_length) {
            std::cerr << "Error: Dose data size mismatch with dimensions" << std::endl;
            return false;
        }

        // Create output directory if it doesn't exist
        std::filesystem::create_directories(output_path);

        std::string output_filename = dcm_info.output_name + ".dcm";
        std::string full_output_path = std::filesystem::path(output_path) / output_filename;

        // Initialize DICOM file
        DcmFileFormat dcm_file;
        DcmDataset* dataset = dcm_file.getDataset();

        // Create meta information
        DcmMetaInfo* meta_info = dcm_file.getMetaInfo();
        meta_info->putAndInsertString(DCM_MediaStorageSOPClassUID, UID_RTDoseStorage);
        meta_info->putAndInsertString(DCM_TransferSyntaxUID,
                                      UID_LittleEndianExplicitTransferSyntax);
        meta_info->putAndInsertString(DCM_ImplementationClassUID, "1.2.276.0.7230010.3.0.3.6.1");
        meta_info->putAndInsertString(DCM_ImplementationVersionName, "MOQUI_DCM_SAVE_1.0");
        meta_info->putAndInsertString(DCM_SourceApplicationEntityTitle, "MOQUI_DCM_SAVE");

        // Set SOP Class UID for RT Dose in the main dataset
        dataset->putAndInsertString(DCM_SOPClassUID, UID_RTDoseStorage);

        // Generate unique identifiers
        char sop_instance_uid[UID_BUFFER_SIZE];
        char series_instance_uid[UID_BUFFER_SIZE];
        dcmGenerateUniqueIdentifier(sop_instance_uid, SITE_INSTANCE_UID_ROOT);
        dcmGenerateUniqueIdentifier(series_instance_uid, SITE_INSTANCE_UID_ROOT);

        // Set UIDs in both meta information and dataset
        meta_info->putAndInsertString(DCM_MediaStorageSOPInstanceUID, sop_instance_uid);
        dataset->putAndInsertString(DCM_SOPInstanceUID, sop_instance_uid);
        dataset->putAndInsertString(DCM_SeriesInstanceUID, series_instance_uid);

        // Try to read metadata from RTPLAN file using DCMTK
        bool plan_read_success = false;
        if (!dcm_info.plan_name.empty() && std::filesystem::exists(dcm_info.plan_name)) {
            try {
                // Use DCMTK to read the RTPLAN file
                DcmFileFormat plan_file;
                OFCondition status = plan_file.loadFile(dcm_info.plan_name.c_str());
                if (status.good()) {
                    DcmDataset* plan_dataset = plan_file.getDataset();
                    if (plan_dataset) {
                        // Extract patient metadata
                        OFString patient_name, patient_id, patient_birth_date, patient_sex;
                        OFString study_instance_uid, series_instance_uid_plan, accession_number;
                        OFString study_date, study_time, frame_of_reference_uid;

                        plan_dataset->findAndGetOFString(DCM_PatientName, patient_name);
                        plan_dataset->findAndGetOFString(DCM_PatientID, patient_id);
                        plan_dataset->findAndGetOFString(DCM_PatientBirthDate, patient_birth_date);
                        plan_dataset->findAndGetOFString(DCM_PatientSex, patient_sex);
                        plan_dataset->findAndGetOFString(DCM_StudyInstanceUID, study_instance_uid);
                        plan_dataset->findAndGetOFString(DCM_SeriesInstanceUID,
                                                         series_instance_uid_plan);
                        plan_dataset->findAndGetOFString(DCM_AccessionNumber, accession_number);
                        plan_dataset->findAndGetOFString(DCM_StudyDate, study_date);
                        plan_dataset->findAndGetOFString(DCM_StudyTime, study_time);
                        plan_dataset->findAndGetOFString(DCM_FrameOfReferenceUID,
                                                         frame_of_reference_uid);

                        // Copy metadata to dose file
                        if (!patient_name.empty()) {
                            dataset->putAndInsertString(DCM_PatientName, patient_name.c_str());
                        }
                        if (!patient_id.empty()) {
                            dataset->putAndInsertString(DCM_PatientID, patient_id.c_str());
                        }
                        if (!patient_birth_date.empty()) {
                            dataset->putAndInsertString(DCM_PatientBirthDate,
                                                        patient_birth_date.c_str());
                        }
                        if (!patient_sex.empty()) {
                            dataset->putAndInsertString(DCM_PatientSex, patient_sex.c_str());
                        }
                        if (!study_instance_uid.empty()) {
                            dataset->putAndInsertString(DCM_StudyInstanceUID,
                                                        study_instance_uid.c_str());
                        }
                        if (!accession_number.empty()) {
                            dataset->putAndInsertString(DCM_AccessionNumber,
                                                        accession_number.c_str());
                        }
                        if (!study_date.empty()) {
                            dataset->putAndInsertString(DCM_StudyDate, study_date.c_str());
                        }
                        if (!study_time.empty()) {
                            dataset->putAndInsertString(DCM_StudyTime, study_time.c_str());
                        }
                        if (!frame_of_reference_uid.empty()) {
                            dataset->putAndInsertString(DCM_FrameOfReferenceUID,
                                                        frame_of_reference_uid.c_str());
                        }

                        plan_read_success = true;
                        std::cout << "Successfully read metadata from RTPLAN file: "
                                  << dcm_info.plan_name << std::endl;
                    }
                } else {
                    std::cerr << "Warning: Could not read RTPLAN file: " << dcm_info.plan_name
                              << std::endl;
                }
            } catch (const std::exception& e) {
                std::cerr << "Warning: Error reading RTPLAN file: " << e.what() << std::endl;
            }
        } else {
            std::cerr << "Warning: RTPLAN file not found: " << dcm_info.plan_name << std::endl;
        }

        // Add mandatory tags if not read from plan
        if (!plan_read_success) {
            dataset->putAndInsertString(DCM_PatientName, "TEST^PATIENT");
            dataset->putAndInsertString(DCM_PatientID, "TEST12345");
            dataset->putAndInsertString(DCM_StudyInstanceUID, "1.2.3.4.5.6.7.8.9.0.1.2.3");
            dataset->putAndInsertString(DCM_FrameOfReferenceUID, "1.2.3.4.5.6.7.8.9.0.1.2.6");
        }

        // Add current date and time (using simple fallback values)
        dataset->putAndInsertString(DCM_InstanceCreationDate, "20240101");
        dataset->putAndInsertString(DCM_InstanceCreationTime, "120000");

        // Set image dimensions
        dataset->putAndInsertUint16(DCM_Rows, static_cast<Uint16>(dimensions[1]));
        dataset->putAndInsertUint16(DCM_Columns, static_cast<Uint16>(dimensions[0]));

        // Calculate dose grid scaling
        double max_dose = 0.0;
        for (double dose : dose_data) {
            if (dose > max_dose) {
                max_dose = dose;
            }
        }

        double dose_grid_scaling = (max_dose * scale) / MAX_16_BIT_VALUE;
        if (dose_grid_scaling <= 0.0) {
            dose_grid_scaling = MIN_DOSE_SCALING;  // Minimum scaling to avoid zero
        }

        dataset->putAndInsertFloat64(DCM_DoseGridScaling, dose_grid_scaling);

        // Set pixel spacing (assuming 1mm isotropic voxels)
        dataset->putAndInsertString(DCM_PixelSpacing, "1.0\\1.0");

        // Set image position patient (origin at 0,0,0)
        dataset->putAndInsertString(DCM_ImagePositionPatient, "0.0\\0.0\\0.0");

        // Set orientation (standard orientation)
        dataset->putAndInsertString(DCM_ImageOrientationPatient, "1.0\\0.0\\0.0\\0.0\\1.0\\0.0");

        // Convert dose data to 16-bit integers
        std::vector<Uint16> pixel_data(total_length);
        for (size_t i = 0; i < total_length; ++i) {
            pixel_data[i] = static_cast<Uint16>((dose_data[i] * scale) / dose_grid_scaling);
        }

        // Add pixel data
        dataset->putAndInsertUint16Array(DCM_PixelData, pixel_data.data(), total_length);

        // Add RT Dose specific tags
        dataset->putAndInsertString(DCM_Modality, "RTDOSE");
        dataset->putAndInsertString(DCM_SeriesDescription, "Monte Carlo Dose Distribution");

        // Save the DICOM file with explicit transfer syntax
        OFCondition status = dcm_file.saveFile(full_output_path.c_str(), EXS_LittleEndianExplicit);
        if (status.good()) {
            std::cout << "Successfully saved DICOM RT Dose file: " << full_output_path << std::endl;
            std::cout << "  Dose grid scaling: " << dose_grid_scaling << std::endl;
            std::cout << "  Maximum dose: " << max_dose * scale << " Gy" << std::endl;
            std::cout << "  TwoCentimeterMode: " << (two_cm_mode ? "enabled" : "disabled")
                      << std::endl;
            return true;
        } else {
            std::cerr << "Error: Failed to save DICOM file: " << status.text() << std::endl;
            return false;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: Exception during DICOM file creation: " << e.what() << std::endl;
        return false;
    }
#else
    // Fallback to MHD format when DCMTK is not available
    std::cerr << "Warning: DCMTK not available, falling back to MHD format" << std::endl;

    std::filesystem::create_directories(output_path);
    std::string mhd_filename = dcm_info.output_name + ".mhd";
    std::string full_mhd_path = std::filesystem::path(output_path) / mhd_filename;

    // Create simple MHD header
    std::ofstream mhd_file(full_mhd_path);
    if (!mhd_file.is_open()) {
        std::cerr << "Error: Could not create MHD file: " << full_mhd_path << std::endl;
        return false;
    }

    mhd_file << "ObjectType = Image\n";
    mhd_file << "NDims = 3\n";
    mhd_file << "DimSize = " << dimensions[0] << " " << dimensions[1] << " " << dimensions[2]
             << "\n";
    mhd_file << "ElementType = MET_DOUBLE\n";
    mhd_file << "ElementSpacing = 1.0 1.0 1.0\n";
    mhd_file << "ElementByteOrderMSB = False\n";

    std::string raw_filename = dcm_info.output_name + ".raw";
    mhd_file << "ElementDataFile = " << raw_filename << "\n";
    mhd_file.close();

    // Write raw data
    std::string raw_filepath = std::filesystem::path(output_path) / raw_filename;
    std::ofstream raw_file(raw_filepath, std::ios::binary);
    if (!raw_file.is_open()) {
        std::cerr << "Error: Could not create RAW file: " << raw_filepath << std::endl;
        return false;
    }

    std::vector<double> scaled_data(total_length);
    for (size_t i = 0; i < total_length; ++i) {
        scaled_data[i] = dose_data[i] * scale;
    }

    raw_file.write(reinterpret_cast<const char*>(scaled_data.data()),
                   total_length * sizeof(double));
    raw_file.close();

    std::cout << "Successfully saved MHD file: " << full_mhd_path << std::endl;
    return true;
#endif
}
