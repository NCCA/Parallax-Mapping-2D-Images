#ifndef GLWINDOW_H_
#define GLWINDOW_H_
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Image.h"
#include "ImageData.h"
#include <windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLWindow.h"
#include "shader.h"

class GLWindow
{
    public:
       
        GLuint shaderProgram;
        GLuint depthTexture;
        GLuint quadVAO, quadVBO,quadEBO;
        GLWindow();
        GLWindow(unsigned int width, unsigned int height, const char*);
        ~GLWindow();
        Shader processTextures(std::string fragpath, std::string vertpath);
        void GLWindow::updatePaths(std::string path, std::string depth_map, std::string depth_normals, std::string albedo, std::string residuals, std::string diffuse_shading);
        int getheight();
        int getwidth();
        void BindTextures(Shader shader);
        GLFWwindow* getGLWin();
        const char* gettitle();
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        void processInput();
        void setupViewport(GLFWwindow* window);
        void initGLFW();
        void openWin();
        void initGLAD();
        void setupViewport();
    
        GLuint loadShader(const std::string& path, GLenum type);
        GLuint createShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
        GLuint PrepareTexture(std::string);
        void createQuadVAO();
        void renderQuad();


    // private:
        GLFWwindow* GLWin;
        int W_width;
        int W_height;
        const char * title;
        Image tex_data;
        GLuint diffuseMap ;
        GLuint normalMap  ;
        GLuint heightMap ;
        GLuint albedoMap  ;
        GLuint residualMap ;
        GLuint shadingMap ;
          
   
};


#endif
