#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "Image.h"
#include "ImageData.h"
#include <windows.h>
#include <libheif/heif.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLWindow.h"
#include <string>

GLWindow::GLWindow()
{
     if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        
    }
    W_width = 0;
    W_height = 0;
    GLWin = nullptr;
    title = " ";
    //GLWin = glfwCreateWindow(W_width, W_height, "OpenGL Scene", NULL, NULL);
    std::cout<<"Window created\n";  
}
GLWindow::~GLWindow()
{
    glfwTerminate();
    std::cout<<"Window destroyed\n";
}

GLWindow::GLWindow(unsigned int width, unsigned int height, const char* newtitle)
    : W_width(width), W_height(height), GLWin(nullptr), title(newtitle) {
    initGLFW();
    openWin();
    initGLAD();
    setupViewport();
    //createQuad();
    //loadShaders();
}

int GLWindow::getheight()
{
    return W_height;
}

int GLWindow::getwidth()
{
    return W_width;
}

GLFWwindow* GLWindow::getGLWin()
{
    return GLWin;
}

const char* GLWindow::gettitle()
{
    return title;
}

void GLWindow::processInput() {
    if (glfwGetKey(GLWin, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(GLWin, true);
}


void GLWindow::initGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        exit(-1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void GLWindow::openWin() {
    GLWin = glfwCreateWindow(W_width, W_height, title, nullptr, nullptr);
    if (!GLWin) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(GLWin);
    glfwSetWindowUserPointer(GLWin, this); 
    glfwSetFramebufferSizeCallback(GLWin, framebuffer_size_callback);
}

void GLWindow::initGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        exit(-1);
    }
}

void GLWindow::setupViewport() {
    glViewport(0, 0, W_width, W_height);
}

void GLWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    GLWindow* scene = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
    if (scene) {
        glViewport(0, 0, width, height);
    }
}

void GLWindow::renderLoop() {
    while (!glfwWindowShouldClose(GLWin)) {
        processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(GLWin);
        glfwPollEvents();
    }
}

void GLWindow::run() {
    renderLoop();
}

