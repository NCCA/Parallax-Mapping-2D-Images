#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "Image.h"
#include "ImageData.h"
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Def constructor
Image::Image() {
    std::cout<<"Def constructor\n";
    types = {
        {"Image", 0},
        {"Depth Map", 1},
        {"Depth Normals", 2},
        {"Albedo", 3},
        {"Residuals", 4},
        {"Diffuse Shading", 5}

};
}
// Parameterized constructor
Image::Image(std::string image, std::string depth_map, std::string depth_normals, std::string albedo, std::string residuals, std::string diffuse_shading) {
    
    inp_image.set_path(image);
    inp_image.set_depth_map(depth_map);
    inp_image.set_depth_normals(depth_normals);
    inp_image.set_Image_Intrinsic(albedo, residuals, diffuse_shading);
}

Image::~Image() {
    std::cout<<"Destructor\n";
}


// Sets the paths for the images that wil be loaded for textures
void Image::setPaths(std::string image, std::string depth_map, std::string depth_normals, std::string albedo, std::string residuals, std::string diffuse_shading) {
    inp_image.set_path(image);
    inp_image.set_depth_map(depth_map);
    inp_image.set_depth_normals(depth_normals);
    inp_image.set_Image_Intrinsic(albedo, residuals, diffuse_shading);
}

// Reads the file of the given type and stores the data in image_data to be used for textures
void Image::readImageData(std::string type)
{
    Intrinsic image_intrinsic = inp_image.get_Image_Intrinsic();
    
    stbi_set_flip_vertically_on_load(true);
    switch(types.at(type))
    {
        case 0:
            image_data = stbi_load(inp_image.get_path().c_str(), &width, &height, &channels, 0);
            break;
        case 1:
            image_data = stbi_load(inp_image.get_depth_map().c_str(), &width, &height, &channels, 0);
            break;
        case 2:
            image_data = stbi_load(inp_image.get_depth_normals().c_str(), &width, &height, &channels, 0);
            break;
        case 3:
            //Intrinsic image_intrinsic = inp_image.get_Image_Intrinsic();
            image_data = stbi_load(image_intrinsic.A.c_str(), &width, &height, &channels, 0);
            std::cout<<"Path "<<image_intrinsic.A.c_str()<<"\n";
            break;
        case 4:
             //Intrinsic image_intrinsic = inp_image.get_Image_Intrinsic();
            image_data = stbi_load(image_intrinsic.R.c_str(), &width, &height, &channels, 0);
            break;
        case 5:
             //Intrinsic image_intrinsic = inp_image.get_Image_Intrinsic();
            image_data = stbi_load(image_intrinsic.D.c_str(), &width, &height, &channels, 0);
            break;
        default:
            std::cerr<<"Invalid type\n";
            break;
    }
    

}
