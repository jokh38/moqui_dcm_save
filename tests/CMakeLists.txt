add_executable(test_example test_example.cpp)
target_link_libraries(test_example PRIVATE moqui_dcm_save_lib gtest gtest_main)

add_test(NAME ExampleTest COMMAND test_example)

# DICOM Output Test
add_executable(test_dicom_output test_dicom_output.cpp)
target_link_libraries(test_dicom_output PRIVATE moqui_dcm_save_lib gtest
                                                gtest_main)

# Link with DCMTK if available
if(DCMTK_FOUND)
  target_link_libraries(test_dicom_output PRIVATE ${DCMTK_LIBRARIES})
  target_include_directories(test_dicom_output PRIVATE ${DCMTK_INCLUDE_DIRS})
  target_compile_definitions(test_dicom_output PRIVATE DCMTK_FOUND=1)
endif()

add_test(NAME DicomOutputTest COMMAND test_dicom_output)
