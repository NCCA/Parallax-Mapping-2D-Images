#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "Image.h"
#include "ImageData.h"
#include <string>
#include <json.hpp>

using json = nlohmann::json;

Image::Image() {
    std::cout<<"Def constructor\n";
    inp_image.set_path ("");
}

Image::~Image() {
    std::cout<<"Destructor\n";
}

Image::Image(std::string path) {
    std::cout<<"Path constructor"<<path<<"\n";
    inp_image.set_path (path);

}


void Image::readDepthMap()
{
    // Open the JSON file
    std::string json_file = inp_image.get_path();
    size_t pos = inp_image.get_path().rfind(".png");
    if (pos != std::string::npos) {
        // Replace ".png" with ".json"
        json_file.replace(pos, 4, ".json");
    }
    
    std::cout<<"Path "<<json_file<<"\n";
    std::ifstream file(json_file);
    // Parse the JSON file into a nlohmann::json object
    json j;
    if(file.is_open()) std::cout<<"File is open\n";
    else std::cout<<"File is not open\n";
    file >> j;
    file.close();
    
    // Convert the depth data from JSON into a 2D vector
    inp_image.set_depth_map(j.get<std::vector<std::vector<float>>>()) ;
    auto dep_map = inp_image.get_depth_map();

    // Convert the 2D vector to a cv::Mat for visualization
    int rows =dep_map.size();
    int cols = dep_map[0].size();
    cv::Mat depth_mat(rows, cols, CV_32F);
    std::cout<<"Rows: "<<rows<<"Cols: "<<cols<<"\n";
    // Fill the cv::Mat with depth data
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            depth_mat.at<float>(i, j) = dep_map[i][j];
        }
    }

    // Normalize the depth map to fit within a range suitable for visualization
    
    normalize(depth_mat, depth_normalized, 0, 255, cv::NORM_MINMAX);
    depth_normalized.convertTo(depth_normalized, CV_8U);

}

void Image::readDepthNormals()
{
    // Open the JSON file
    std::string json_file = inp_image.get_path();
    size_t pos = inp_image.get_path().rfind(".png");
    if (pos != std::string::npos) {
        // Replace ".png" with ".json"
        json_file.replace(pos, 4, "_normals.json");
    }
    std::cout<<"Path "<<json_file<<"\n";
    std::ifstream file(json_file);
    // Parse the JSON file into a nlohmann::json object
    json j;
    if(file.is_open()) std::cout<<"File is open\n";
    else std::cout<<"File is not open\n";
  
    file >> j;
    file.close();
  
    
   
    auto raw_data = j.get<std::vector<std::vector<std::vector<std::vector<float>>>>>();
    std::vector<std::vector<std::vector<float>>> depthm;
        for (const auto& dim1 : raw_data) {  
            depthm.insert(depthm.end(), dim1.begin(), dim1.end());
        }

        
        std::vector<std::vector<float>> first_channel;
        for (const auto& row : depthm) {
            std::vector<float> channel_row;
            for (const auto& pixel : row) {
                if (!pixel.empty()) {
                    channel_row.push_back(pixel[0]); 
                }
            }
            first_channel.push_back(channel_row);
        }

    inp_image.set_depth_normals(first_channel) ;

    auto im_normals = inp_image.get_depth_normals();

    // Convert the 2D vector to a cv::Mat for visualization
    int rows = im_normals.size();
    int cols = im_normals[0].size();
    cv::Mat depth_norm(rows, cols, CV_32F);
    std::cout<<"Rows: "<<rows<<"Cols: "<<cols<<"\n";
    // Fill the cv::Mat with depth data
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            depth_norm.at<float>(i, j) = im_normals[i][j];
        }
    }
  
    normalize(depth_norm, normals_normalized, 0, 255, cv::NORM_MINMAX);
    normals_normalized.convertTo(normals_normalized, CV_8U);
    
}
void Image::displayDepthMap()
{
    cv::namedWindow("Depth Map", cv::WINDOW_NORMAL);
    cv::imshow("Depth Map", depth_normalized);
    cv::waitKey(0);
}

void Image::displayDepthNormals()
{
    cv::namedWindow("Depth Normals", cv::WINDOW_NORMAL);
    cv::imshow("Depth Normals", normals_normalized);
    cv::waitKey(0);
}
