#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "ImageData.h"
#include <string>
#include <json.hpp>

using json = nlohmann::json;

ImageData::ImageData() {
    std::cout<<"Def constructor\n";
    path = "";
}

ImageData::~ImageData() {
    std::cout<<"Destructor\n";
}

ImageData::ImageData(std::string newpath) {
    std::cout<<"Path constructor"<<newpath<<"\n";
    this->path = newpath;
}

void ImageData::set_path(std::string newpath)
{
    this->path = newpath;
}


std::string ImageData::get_path()
{
    
    return path;
}


void ImageData::set_depth_map(std::vector<std::vector<float>> new_depth_map)
{
    std::cout<<"Setting depth map\n";
    this->depth_map = new_depth_map;
}

std::vector<std::vector<float>> ImageData::get_depth_map()
{
    return depth_map;
}   

void ImageData::set_depth_normals(std::vector<std::vector<float>> new_depth_normals)
{
    this->depth_normals = new_depth_normals;
}

std::vector<std::vector<float>> ImageData::get_depth_normals()
{
    return depth_normals;
}   


void ImageData::set_Image_Intrinsic(std::vector<std::vector<float>> new_albedo, std::vector<std::vector<float>> new_residuals, std::vector<std::vector<float>> new_diffuse_shading)
{
    this->image_intrinsic.A = new_albedo;
    this->image_intrinsic.R = new_residuals;
    this->image_intrinsic.S = new_diffuse_shading;
}


Intrinsic ImageData::get_Image_Intrinsic()
{
    return image_intrinsic;
}   
