#ifndef IMAGE_H_
#define IMAGE_H_
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "ImageData.h"


class Image
{
    public:
        ImageData inp_image;
        Image();
        Image(std::string , std::string , std::string , std::string , std::string , std::string );
        void setPaths(std::string , std::string , std::string , std::string , std::string , std::string );
        ~Image();
        void readImageData(std::string);


        unsigned char * image_data ;
        int width, height, channels;
        std::unordered_map <std::string, int> types;


};


#endif