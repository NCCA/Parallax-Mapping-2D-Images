cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")


project(DepthMapVisualizer)


find_package(nlohmann_json CONFIG REQUIRED)
find_package(exiv2 CONFIG REQUIRED)
find_package(libheif REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS core highgui imgproc)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(Image)


include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${nlohmann_json_INCLUDE_DIRS})
include_directories(${LIBHEIF_INCLUDE_DIR} ${EXIV2_INCLUDE_DIR})
target_include_directories(Image PRIVATE include)


target_sources(Image
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src/main.cpp 
    ${CMAKE_SOURCE_DIR}/src/Image.cpp 
    ${CMAKE_SOURCE_DIR}/src/ImageData.cpp
    ${CMAKE_SOURCE_DIR}/src/GLWindow.cpp
)


target_link_libraries(Image
    PRIVATE
    glfw
    nlohmann_json::nlohmann_json
    ${OpenCV_LIBS}
    exiv2lib
    heif
    glm::glm
    glad::glad
    ${LIBHEIF_LIBRARIES}
    ${EXIV2_LIBRARIES}
)


file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)


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
    ${CMAKE_SOURCE_DIR}/src/GLWindow.cpp
    ${CMAKE_SOURCE_DIR}/include/GLWindow.h
)


target_link_libraries(ImageTests
    PRIVATE
    glfw
    glad::glad
    nlohmann_json::nlohmann_json
    ${OpenCV_LIBS}
    GTest::gtest
    GTest::gtest_main
)


gtest_discover_tests(ImageTests)
