#include <stdio.h>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include "ImageData.h"
#include <string>


// Def constructor
ImageData::ImageData() {
    std::cout<<"Def constructor\n";
    path = "";
}

// Destructor
ImageData::~ImageData() {
    std::cout<<"Destructor\n";
}
// Parameterized constructor
ImageData::ImageData(std::string image, std::string depth_map, std::string depth_normals, std::string albedo, std::string residuals, std::string diffuse_shading) {
    
    this->path = image;
    this->depth_map = depth_map;
    this->depth_normals = depth_normals;
    this->image_intrinsic.A = albedo;
    this->image_intrinsic.R = residuals;
    this->image_intrinsic.D = diffuse_shading;
}
// Setter and Getters for testing
void ImageData::set_path(std::string newpath)
{
    this->path = newpath;
}


std::string ImageData::get_path()
{
    
    return path;
}


void ImageData::set_depth_map(std::string new_depth_map)
{
    std::cout<<"Setting depth map\n";
    this->depth_map = new_depth_map;
}

std::string ImageData::get_depth_map()
{
    return depth_map;
}   

void ImageData::set_depth_normals(std::string new_depth_normals)
{
    this->depth_normals = new_depth_normals;
}

std::string ImageData::get_depth_normals()
{
    return depth_normals;
}   


void ImageData::set_Image_Intrinsic(std::string new_albedo, std::string new_residuals, std::string new_diffuse_shading)
{
    this->image_intrinsic.A = new_albedo;
    this->image_intrinsic.R = new_residuals;
    this->image_intrinsic.D = new_diffuse_shading;
}


Intrinsic ImageData::get_Image_Intrinsic()
{
    return image_intrinsic;
}   

