#ifndef GLWINDOW_H_
#define GLWINDOW_H_
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Image.h"
#include "ImageData.h"
#include <windows.h>
#include <libheif/heif.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLWindow.h"

class GLWindow
{
    public:
        GLWindow();
        GLWindow(unsigned int width, unsigned int height, const char*);
        ~GLWindow();
        int getheight();
        int getwidth();
        GLFWwindow* getGLWin();
        const char* gettitle();
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        void processInput();
        void setupViewport(GLFWwindow* window);
        void initGLFW();
        void openWin();
        void initGLAD();
        void setupViewport();
        void renderLoop();
        void run();
    private:
        GLFWwindow* GLWin;
        int W_width;
        int W_height;
        const char * title;

   
};


#endif
