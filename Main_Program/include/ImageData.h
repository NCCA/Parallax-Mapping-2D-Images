#ifndef IMAGEDATA_H_
#define IMAGEDATA_H_
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>

struct Intrinsic
{
    std::vector<std::vector<float>> A;
    std::vector<std::vector<float>> R;
    std::vector<std::vector<float>> S;
};


class ImageData
{
    public:
        ImageData();
        ImageData(std::string );
        ~ImageData();

        void set_path(std::string);
        std::string get_path();

        void set_depth_map(std::vector<std::vector<float>>);
        std::vector<std::vector<float>> get_depth_map();

        void set_depth_normals(std::vector<std::vector<float>>);
        std::vector<std::vector<float>> get_depth_normals();

        void set_Image_Intrinsic(std::vector<std::vector<float>>, std::vector<std::vector<float>>, std::vector<std::vector<float>>);
        Intrinsic get_Image_Intrinsic();

    private:
        std::string path;
        std::vector<std::vector<float>> depth_map;
        std::vector<std::vector<float>> depth_normals;
        Intrinsic image_intrinsic;
        
};


#endif
