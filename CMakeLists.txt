cmake_minimum_required(VERSION 3.20)
project(
  moqui_dcm_save
  VERSION 0.1.0
  LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler warnings
if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Dependencies
include(FetchContent)

# Find DCMTK (optional for DICOM functionality)
find_package(DCMTK)
if(DCMTK_FOUND)
  message(STATUS "DCMTK found - DICOM support enabled")
  add_compile_definitions(DCMTK_FOUND=1)

  # Find GDCM for additional DICOM functionality
  find_package(GDCM QUIET)
  if(GDCM_FOUND)
    message(STATUS "GDCM found - additional DICOM functionality enabled")
    add_compile_definitions(GDCM_FOUND=1)
  else()
    message(WARNING "GDCM not found - some DICOM features may be limited")
    add_compile_definitions(GDCM_FOUND=0)
  endif()
else()
  message(
    WARNING
      "DCMTK not found - DICOM support disabled, falling back to MHD format")
  add_compile_definitions(DCMTK_FOUND=0)
  add_compile_definitions(GDCM_FOUND=0)
endif()

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(GTEST_FORCE_SHARED_CRT
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Library
add_library(moqui_dcm_save_lib src/library.cpp)

target_include_directories(
  moqui_dcm_save_lib
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>)

# Link DCMTK libraries if available
if(DCMTK_FOUND)
  target_link_libraries(moqui_dcm_save_lib PUBLIC ${DCMTK_LIBRARIES})
  target_include_directories(moqui_dcm_save_lib PUBLIC ${DCMTK_INCLUDE_DIRS})

  # Link GDCM if available
  if(GDCM_FOUND)
    target_link_libraries(moqui_dcm_save_lib PUBLIC ${GDCM_LIBRARIES})
    target_include_directories(moqui_dcm_save_lib PUBLIC ${GDCM_INCLUDE_DIRS})
  endif()
endif()

# Executable
add_executable(moqui_dcm_save src/main.cpp)

target_link_libraries(moqui_dcm_save PRIVATE moqui_dcm_save_lib)

# Tests
enable_testing()
add_subdirectory(tests)
