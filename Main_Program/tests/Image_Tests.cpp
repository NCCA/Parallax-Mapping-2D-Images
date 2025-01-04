#include <gtest/gtest.h>
#include "Image.h"
#include "ImageData.h"
#include "GLWindow.h"
#include <string>
#include <fstream>

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
    std::string path = "input.json";
    ImageData inp(path);
    ASSERT_STREQ(inp.get_path().c_str(), path.c_str());
}

// ImageData Class setting path and getting path
TEST(ImageData,correct_path)
{
    std::string json_file = "test_path.json";
    ImageData inp;
    inp.set_path(json_file);
    ASSERT_STREQ(inp.get_path().c_str(), json_file.c_str());
   
}


TEST(ImageData,setting_depth)
{
    std::string json_file = "test_path.json";
    ImageData inp;
    inp.set_path(json_file);
    ASSERT_STREQ(inp.get_path().c_str(), json_file.c_str());
   
}

TEST(ImageData,correct_path)
{
    std::string json_file = "test_path.json";
    ImageData inp;
    inp.set_path(json_file);
    ASSERT_STREQ(inp.get_path().c_str(), json_file.c_str());
   
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
    std::string path = "input.json";
    Image inp(path);
    ASSERT_STREQ(inp.inp_image.get_path().c_str(), path.c_str());
}

TEST(Image,read_depth)
{
    std::string json_file = "assets/JSON_files/20241121_111331369_iOS.png";
    Image inp(json_file);
    std::ifstream file(json_file);
    ASSERT_TRUE(file.is_open());
   
}

TEST(GLWindow,ctor)
{
    std::string title = " ";
    GLWindow win;
    ASSERT_EQ(win.getwidth(), 0);
    ASSERT_EQ(win.getheight(), 0);
    ASSERT_STREQ(win.gettitle(), title.c_str());
}

TEST(GLWindow,param_ctor)
{
    std::string title = "test window";
    GLWindow win(600, 400,title.c_str() );
    ASSERT_EQ(win.getwidth(), 600);
    ASSERT_EQ(win.getheight(), 400);
    ASSERT_STREQ(win.gettitle(), title.c_str());
}

TEST(GLWindow, libs_init)
{
    ASSERT_TRUE(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
    ASSERT_TRUE(glfwInit());
}

TEST(GLWindow, open_window)
{
    GLWindow win(600, 400, "test window");
    GLFWwindow* window = win.getGLWin();
    window = glfwCreateWindow(win.getwidth(), win.getheight(), win.gettitle(), nullptr, nullptr);
    ASSERT_TRUE(window);
    
}
 
