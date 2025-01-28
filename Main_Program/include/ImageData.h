#ifndef IMAGEDATA_H_
#define IMAGEDATA_H_
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>

struct Intrinsic
{
    std::string A;
    std::string R; 
    std::string D;
};


class ImageData
{
    public:
        ImageData();
        ImageData(std::string , std::string , std::string , std::string , std::string , std::string );
        ~ImageData();

        void set_path(std::string);
        std::string get_path();

        void set_depth_map(std::string);
        std::string get_depth_map();

        void set_depth_normals(std::string);
        std::string get_depth_normals();

        void set_Image_Intrinsic(std::string, std::string, std::string);
        Intrinsic get_Image_Intrinsic();



    private:
        std::string path;
        std::string depth_map;
        std::string depth_normals;
        Intrinsic image_intrinsic;
        
};


#endif