cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")


project(DepthMapVisualizer)



find_package(OpenCV REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

add_executable(Image)


include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(Image PRIVATE assimp::assimp)

target_include_directories(Image PRIVATE include)


target_sources(Image
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src/main.cpp 
    ${CMAKE_SOURCE_DIR}/src/Image.cpp 
    ${CMAKE_SOURCE_DIR}/src/ImageData.cpp
    ${CMAKE_SOURCE_DIR}/src/GLWindow.cpp
    ${CMAKE_SOURCE_DIR}/include/shader.h  
    ${CMAKE_SOURCE_DIR}/include/camera.h 
    ${CMAKE_SOURCE_DIR}/include/model.h
    ${CMAKE_SOURCE_DIR}/include/mesh.h
)


target_link_libraries(Image
    PRIVATE
    glfw
    ${OpenCV_LIBS}
    glm::glm
    glad::glad
    GLEW::GLEW

    
)


file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)
file(COPY shaders/ DESTINATION ${CMAKE_BINARY_DIR}/shaders)

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
    ${CMAKE_SOURCE_DIR}/include/camera.h 
    ${CMAKE_SOURCE_DIR}/include/model.h
    ${CMAKE_SOURCE_DIR}/include/mesh.h
)



target_link_libraries(ImageTests
    PRIVATE
    glfw
    glad::glad
    ${OpenCV_LIBS}
    GTest::gtest
    GTest::gtest_main
)


gtest_discover_tests(ImageTests)

file(COPY Images/ DESTINATION ${CMAKE_BINARY_DIR}/Images)