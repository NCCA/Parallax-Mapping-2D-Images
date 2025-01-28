#include <gtest/gtest.h>
#include "Image.h"
#include "ImageData.h"
#include "GLWindow.h"
#include <string>
#include <fstream>
#include <windows.h>


// I prefered using GTests for my base classes
// The GLWindow class I chose to put error checks in functions and also using OpenGL debugging callback

// ImageData Class constructor
TEST(ImageData,ctor)
{
    std::string path = "";
    ImageData inp;
    ASSERT_STREQ(inp.get_path().c_str(), path.c_str());
}

// ImageData Class parameter constructor
TEST(ImageData,param_ctor)
{
    std::string path = "image.png";
    std::string depth_map = "depth_map.png";
    std::string depth_normals = "depth_normals.png";
    std::string albedo = "test_albedo.png";
    std::string residuals = "test_residuals.png";
    std::string diffuse_shading = "test_diffuse_shading.png";

    ImageData inp(path,depth_map,depth_normals,albedo,residuals,diffuse_shading);
    Intrinsic intrinsic = inp.get_Image_Intrinsic();

    ASSERT_STREQ(inp.get_path().c_str(), path.c_str());
    ASSERT_STREQ(inp.get_depth_map().c_str(), depth_map.c_str());
    ASSERT_STREQ(inp.get_depth_normals().c_str(), depth_normals.c_str());
    ASSERT_STREQ(intrinsic.A.c_str(), albedo.c_str());
    ASSERT_STREQ(intrinsic.R.c_str(), residuals.c_str());
    ASSERT_STREQ(intrinsic.D.c_str(), diffuse_shading.c_str());
}

// // ImageData Class setting path and getting path
TEST(ImageData,correct_path)
{
    std::string file = "test_path.png";
    ImageData inp;
    inp.set_path(file);
    ASSERT_STREQ(inp.get_path().c_str(), file.c_str());
   
}


TEST(ImageData,setting_depth)
{
    std::string file = "test_path.png";
    ImageData inp;
    inp.set_depth_map(file);
    ASSERT_STREQ(inp.get_depth_map().c_str(), file.c_str());
   
}

TEST(ImageData,setting_depth_normals)
{
    std::string file = "test_path.png";
    ImageData inp;
    inp.set_depth_normals(file);
    ASSERT_STREQ(inp.get_depth_normals().c_str(), file.c_str());
   
}

TEST(ImageData,setting_Image_Intrinsic)
{
    std::string albedo = "test_albedo.png";
    std::string residuals = "test_residuals.png";
    std::string diffuse_shading = "test_diffuse_shading.png";
    ImageData inp;
    inp.set_Image_Intrinsic(albedo, residuals, diffuse_shading);
    Intrinsic intrinsic = inp.get_Image_Intrinsic();
    ASSERT_STREQ(intrinsic.A.c_str(), albedo.c_str());
    ASSERT_STREQ(intrinsic.R.c_str(), residuals.c_str());
    ASSERT_STREQ(intrinsic.D.c_str(), diffuse_shading.c_str());
}



// Image Class constructor

TEST(Image,ctor)
{
    std::string path = "";
    Image inp;
    ASSERT_STREQ(inp.inp_image.get_path().c_str(), path.c_str());
}

// Image Class parameter constructor
TEST(Image,param_ctor)
{
    std::string path = "image.png";
    std::string depth_map = "depth_map.png";
    std::string depth_normals = "depth_normals.png";
    std::string albedo = "test_albedo.png";
    std::string residuals = "test_residuals.png";
    std::string diffuse_shading = "test_diffuse_shading.png";

    Image inp(path,depth_map,depth_normals,albedo,residuals,diffuse_shading);
    Intrinsic intrinsic = inp.inp_image.get_Image_Intrinsic();

    ASSERT_STREQ(inp.inp_image.get_path().c_str(), path.c_str());
    ASSERT_STREQ(inp.inp_image.get_depth_map().c_str(), depth_map.c_str());
    ASSERT_STREQ(inp.inp_image.get_depth_normals().c_str(), depth_normals.c_str());
    ASSERT_STREQ(intrinsic.A.c_str(), albedo.c_str());
    ASSERT_STREQ(intrinsic.R.c_str(), residuals.c_str());
    ASSERT_STREQ(intrinsic.D.c_str(), diffuse_shading.c_str());
}




 