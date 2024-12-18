#ifndef IMAGE_H_
#define IMAGE_H_
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>


class Image
{
    public:
        Image();
        Image(std::string );
        ~Image();
        void set_path(std::string);
        std::string get_path();
        std::vector<std::vector<float>> get_depth_map();
        void readDepthMap();
        void displayImage(char* path);
        void displayDepthMap();

    private:
        std::string path;
        std::vector<std::vector<float>> depth_map;
        cv::Mat depth_normalized;


};


#endif