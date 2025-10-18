add_executable(test_example test_example.cpp)
target_link_libraries(test_example PRIVATE moqui_dcm_save_lib gtest gtest_main)

add_test(NAME ExampleTest COMMAND test_example)
