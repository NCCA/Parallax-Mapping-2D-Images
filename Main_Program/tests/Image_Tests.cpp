#include <gtest/gtest.h>
#include "Image.h"
#include <string>
#include <fstream>
TEST(Image,ctor)
{
    std::string path = "";
    Image inp;
    ASSERT_STREQ(inp.get_path().c_str(), path.c_str());
}

TEST(Image,param_ctor)
{
    std::string path = "input.json";
    Image inp(path);
    ASSERT_STREQ(inp.get_path().c_str(), path.c_str());
}

TEST(Image,open_file)
{
    std::string json_file = "JSON_files/20241213_122200254_iOS.json";
    Image inp(json_file);
    std::ifstream file(json_file);
    ASSERT_TRUE(file.is_open());
   
}

TEST(Image,File_not_Empty)
{
    std::string json_file = "JSON_files/20241213_122200254_iOS.json";
    Image inp(json_file);
    inp.readDepthMap();
    ASSERT_FALSE(inp.get_depth_map().empty());
    ASSERT_FALSE(inp.get_depth_map()[0].empty());

}



 