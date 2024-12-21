cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
# Set project name and version
project(DepthMapVisualizer)

# Find OpenCV package

# Specify where to find nlohmann/json (assumes vcpkg or other package manager is handling it)
# If you have installed nlohmann/json manually, you might need to point CMake to its include directory

# find_package(nlohmann_json REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

find_package(OpenCV REQUIRED COMPONENTS core highgui imgproc)
find_package(OpenCV REQUIRED)

# Ensure OpenCV is linked with highgui and correct backend

# Include directories for OpenCV and nlohmann_json


add_executable(Image)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${nlohmann_json_INCLUDE_DIRS})


target_include_directories(Image PRIVATE include)

target_sources(Image
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src/main.cpp 
    ${CMAKE_SOURCE_DIR}/src/Image.cpp 
    ${CMAKE_SOURCE_DIR}/src/ImageData.cpp
       
)

# Link the OpenCV libraries to your executable
target_link_libraries(Image PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(Image PRIVATE ${OpenCV_LIBS})
file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)
#target_link_libraries(Image PRIVATE OpenCV::Core OpenCV::Highgui)
# Link nlohmann_json (this is a header-only library, so no additional link command is needed)
# However, if nlohmann_json is installed in a separate directory, you may need to link the library.

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
enable_testing()
add_executable(ImageTests)
target_include_directories(ImageTests PRIVATE include)

target_sources(ImageTests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/tests/Image_Tests.cpp

        ${CMAKE_SOURCE_DIR}/src/Image.cpp
        ${CMAKE_SOURCE_DIR}/include/Image.h
        ${CMAKE_SOURCE_DIR}/include/ImageData.h
        ${CMAKE_SOURCE_DIR}/src/ImageData.cpp
)
target_link_libraries(ImageTests PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(ImageTests PRIVATE ${OpenCV_LIBS})
target_link_libraries(ImageTests
    PRIVATE
        GTest::gtest
        GTest::gtest_main
        
)

gtest_discover_tests(ImageTests)
