cmake_minimum_required(VERSION 3.15)

project(interview_prep
    VERSION 0.0.1
    DESCRIPTION "A reference implementation of the proposed std::experimental::simd data type for parallel programming"
    LANGUAGES CXX
)

# Include necessary submodules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# CMake includes
include(CTest)
include(FetchContent)
include(GNUInstallDirs)
include(CMakeDependentOption)

set(STD_EXPERIMENTAL_SIMD_PREDEFINED_TARGETS "_BuildTargets")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER ${STD_EXPERIMENTAL_SIMD_PREDEFINED_TARGETS})

# Ensure code coverage is switched off for Mac OS until the code coverage library addresses the AppleClang issue
cmake_dependent_option(ENABLE_CODE_COVERAGE "Enable code coverage" ON "\"${CMAKE_CXX_COMPILER_ID}\" STREQUAL \"Clang\" OR \"${CMAKE_CXX_COMPILER_ID}\" STREQUAL \"GNU\"" OFF)

add_library(interview_prep STATIC "")
target_include_directories(interview_prep
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_sources(interview_prep
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sites/codility/prefix_sums/min_avg_two_slice.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sites/codility/prefix_sums/min_avg_two_slice.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sites/codility/prefix_sums/num_zero_sub_arrays.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sites/codility/prefix_sums/num_zero_sub_arrays.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/topics/trees/binary.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/topics/trees/binary.cpp>
)

target_compile_features(interview_prep
    PUBLIC
        cxx_std_17
)

FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
)

FetchContent_GetProperties(catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
endif()

add_executable(test_interview_prep "")
target_sources(test_interview_prep
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sites/codility/prefix_sums/min_avg_two_slice.test.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sites/codility/prefix_sums/num_zero_sub_arrays.test.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/topics/trees/binary.test.cpp>
)

target_link_libraries(test_interview_prep
    PRIVATE
        interview_prep
        Catch2::Catch2
)

target_compile_options(test_interview_prep
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-Werror;-Wall>
)

set_target_properties(test_interview_prep PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

enable_testing()
add_test(
    NAME test_interview_prep
    COMMAND test_interview_prep
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(Catch)
catch_discover_tests(test_interview_prep)

if (ENABLE_CODE_COVERAGE)
    FetchContent_Declare(
        codecoverage
        GIT_REPOSITORY https://github.com/RWTH-HPC/CMake-codecov.git
    )

    FetchContent_GetProperties(codecoverage)
    if(NOT codecoverage_POPULATED)
        FetchContent_Populate(codecoverage)
        list(APPEND CMAKE_MODULE_PATH ${codecoverage_SOURCE_DIR}/cmake)
    endif()

    set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
    find_package(codecov)
    add_coverage(test_interview_prep)
    list(APPEND LCOV_REMOVE_PATTERNS "'/usr/*'")
    coverage_evaluate()
endif()