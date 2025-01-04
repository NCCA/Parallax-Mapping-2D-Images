#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "Image.h"
#include "ImageData.h"
#include <windows.h>
#include <libheif/heif.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLWindow.h"

using json = nlohmann::json;

int main() {

//     std::string filePath = "assets/JSON_files/20241121_111331369_iOS.heic";
//   try {
//         // Open the HEIC file using Exiv2
//         std::unique_ptr<Exiv2::Image> image = Exiv2::ImageFactory::open( "assets/JSON_files/20241121_111331369_iOS.heic");

//         // Check if image was successfully opened
//         if (!image) {
//             std::cerr << "Error opening the HEIC file!" << std::endl;
//             return -1;
//         }

//         // Read the metadata (EXIF)
//         image->readMetadata();

//         // Retrieve EXIF data
//         Exiv2::ExifData &exifData = image->exifData();

//         // Print all EXIF data
//         if (exifData.empty()) {
//             std::cout << "No EXIF data found." << std::endl;
//         } else {
//             for (const auto &entry : exifData) {
//                 std::cout << entry.key() << " = " << entry.value() << std::endl;
//             }
//         }

//         // Example of extracting specific EXIF tags (if available):
//         bool foundFocalLength = false;
//         bool foundLensModel = false;

//         // Iterate through EXIF data to find specific tags
//         for (const auto &entry : exifData) {
//             if (entry.key() == "Exif.Photo.FocalLength") {
//                 std::cout << "Focal Length: " << entry.value() << std::endl;
//                 foundFocalLength = true;
//             }
//             if (entry.key() == "Exif.Photo.LensModel") {
//                 std::cout << "Lens Model: " << entry.value() << std::endl;
//                 foundLensModel = true;
//             }
//         }

//         if (!foundFocalLength) {
//             std::cout << "Focal Length not found in EXIF data." << std::endl;
//         }
//         if (!foundLensModel) {
//             std::cout << "Lens Model not found in EXIF data." << std::endl;
//         }

//     } catch (const Exiv2::Error& e) {
//         std::cerr << "Error reading EXIF data: " << e.what() << std::endl;
//         return -1;
//     }

     // Path to the JSON file containing the depth map
    std::string json_file = "assets/JSON_files/20241121_111331369_iOS.png";
   
    // Parse the JSON file into a nlohmann::json object
    json j;

    Image depth(json_file);
    // depth.readDepthMap(); 
    // depth.displayDepthMap();

    depth.readDepthNormals();
    depth.displayDepthNormals();

    GLWindow win(800,600,"OpenGL Window");
    win.run();
    
  
    return 0;
}

