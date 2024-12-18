#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "Image.h"
#include <string>
#include <json.hpp>

using json = nlohmann::json;

Image::Image() {
    std::cout<<"Def constructor\n";
    path = "";
}

Image::~Image() {
    std::cout<<"Destructor\n";
}

Image::Image(std::string newpath) {
    std::cout<<"Path constructor"<<newpath<<"\n";
    this->path = newpath;
}

std::string Image::get_path()
{
    
    return path;
}

void Image::set_path(std::string newpath)
{
    this->path = newpath;
}

void Image::readDepthMap()
{
    // Open the JSON file
     std::cout<<"Path "<<path<<"\n";
    std::ifstream file(path);
    // Parse the JSON file into a nlohmann::json object
    json j;
    if(file.is_open()) std::cout<<"File is open\n";
    else std::cout<<"File is not open\n";
    file >> j;
    file.close();
    
    // Convert the depth data from JSON into a 2D vector
    depth_map = j.get<std::vector<std::vector<float>>>();

    // Convert the 2D vector to a cv::Mat for visualization
    int rows = depth_map.size();
    int cols = depth_map[0].size();
    cv::Mat depth_mat(rows, cols, CV_32F);
    std::cout<<"Rows: "<<rows<<"Cols: "<<cols<<"\n";
    // Fill the cv::Mat with depth data
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            depth_mat.at<float>(i, j) = depth_map[i][j];
        }
    }

    // Normalize the depth map to fit within a range suitable for visualization
    
    normalize(depth_mat, depth_normalized, 0, 255, cv::NORM_MINMAX);
    depth_normalized.convertTo(depth_normalized, CV_8U);

}

std::vector<std::vector<float>> Image::get_depth_map()
{
    return depth_map;
}   

void Image::displayDepthMap()
{
    cv::namedWindow("Depth Map", cv::WINDOW_NORMAL);
    cv::imshow("Depth Map", depth_normalized);
    cv::waitKey(0);
}