cmake_minimum_required(VERSION 3.20)
project(ExpressionTree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Libraries mirror the static-library projects from TepLab3.sln.
add_library(SmartPointer STATIC SmartPointer/RefCounter.cpp)
target_include_directories(SmartPointer PUBLIC SmartPointer)

add_library(TepLab4LogicLib STATIC
    TepLab4LogicLib/error.cpp
    TepLab4LogicLib/result_tests.cpp
)
target_include_directories(TepLab4LogicLib PUBLIC TepLab4LogicLib)
target_link_libraries(TepLab4LogicLib PUBLIC SmartPointer)

add_library(TepLab3LogicLib STATIC
    TepLab3LogicLib/formula_elements.cpp
    TepLab3LogicLib/interface.cpp
    TepLab3LogicLib/node.cpp
    TepLab3LogicLib/string_helpers.cpp
    TepLab3LogicLib/tree.cpp
)
target_include_directories(TepLab3LogicLib PUBLIC TepLab3LogicLib)
target_link_libraries(TepLab3LogicLib PUBLIC TepLab4LogicLib SmartPointer)

add_executable(TepLab3 TepLab3/main.cpp)
target_link_libraries(TepLab3 PRIVATE TepLab3LogicLib)

option(BUILD_TESTS "Build the googletest suite from TepLab3Tests" ON)
if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(googletest)

    enable_testing()
    add_executable(TepLab3Tests TepLab3Tests/test.cpp)
    target_include_directories(TepLab3Tests PRIVATE TepLab3Tests)
    target_link_libraries(TepLab3Tests PRIVATE TepLab3LogicLib GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(TepLab3Tests)
endif()
