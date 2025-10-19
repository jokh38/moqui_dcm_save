#pragma once

#include <string>
#include <vector>

namespace moqui_dcm_save {

// Structure to hold DICOM plan information (mirroring moqui's dicom_t)
struct DicomInfo {
    std::string plan_name;    // Path to RTPLAN file
    std::string output_name;  // Base name for output files

    DicomInfo() = default;
    DicomInfo(const std::string& plan, const std::string& output)
        : plan_name(plan), output_name(output) {}
};

class Library {
   public:
    static void hello();
    static auto add(int first_value, int second_value) -> int;

    // DICOM RT Dose output functionality
    static auto save_dose_as_dicom(const std::vector<double>& dose_data,
                                   const std::vector<uint32_t>& dimensions, double scale,
                                   const std::string& output_path, const DicomInfo& dcm_info,
                                   bool two_cm_mode = false) -> bool;

    // Utility functions for DICOM testing
    static auto is_dcmtk_available() -> bool;
    static auto get_dicom_version() -> std::string;
};

}  // namespace moqui_dcm_save
