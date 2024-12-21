#ifndef IMAGE_H_
#define IMAGE_H_
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "ImageData.h"


class Image
{
    public:
        Image();
        Image(std::string );
        ~Image();
        void readDepthMap();
        void readDepthNormals();
        void readImageIntrinsic();
        void displayImage(char* path);
        void displayDepthMap();
        void displayDepthNormals();
    private:
        ImageData inp_image;
        cv::Mat depth_normalized;
        cv::Mat normals_normalized;


};


#endif
