#pragma once

#include <string>
#include <vector>

namespace moqui_dcm_save {

// Structure to hold DICOM plan information (mirroring moqui's dicom_t)
struct DicomInfo {
    std::string plan_name;      // Path to RTPLAN file
    std::string output_name;    // Base name for output files

    DicomInfo() = default;
    DicomInfo(const std::string& plan, const std::string& output)
        : plan_name(plan), output_name(output) {}
};

class Library {
   public:
    static void hello();
    static int add(int first_value, int second_value);

    // DICOM RT Dose output functionality
    static bool save_dose_as_dicom(const std::vector<double>& dose_data,
                                  const std::vector<uint32_t>& dimensions,
                                  double scale,
                                  const std::string& output_path,
                                  const DicomInfo& dcm_info,
                                  bool two_cm_mode = false);

    // Utility functions for DICOM testing
    static bool is_dcmtk_available();
    static std::string get_dicom_version();
};

}  // namespace moqui_dcm_save
