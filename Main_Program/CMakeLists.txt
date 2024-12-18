cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(DepthMapVisualizer)


# find_package(nlohmann_json REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

find_package(OpenCV REQUIRED COMPONENTS core highgui imgproc)
find_package(OpenCV REQUIRED)




add_executable(Image)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${nlohmann_json_INCLUDE_DIRS})


target_include_directories(Image PRIVATE include)

target_sources(Image
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src/main.cpp ${CMAKE_SOURCE_DIR}/src/Image.cpp
       
)

# Link the OpenCV libraries to your executable
target_link_libraries(Image PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(Image PRIVATE ${OpenCV_LIBS})
#target_link_libraries(Image PRIVATE OpenCV::Core OpenCV::Highgui)

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
)
target_link_libraries(ImageTests PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(ImageTests PRIVATE ${OpenCV_LIBS})
target_link_libraries(ImageTests
    PRIVATE
        GTest::gtest
        GTest::gtest_main
        
)

gtest_discover_tests(ImageTests)
