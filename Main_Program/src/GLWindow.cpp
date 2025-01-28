#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "Image.h"
#include "ImageData.h"
#include <windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLWindow.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "stb_image.h"



// OpenGL debugging callback
void enableOpenGLDebugging() {
    GLint flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback([](GLenum source, GLenum type, GLuint id,
                                  GLenum severity, GLsizei length,
                                  const GLchar* message, const void* userParam) {
            std::cerr << "OpenGL Debug Message: " << message << std::endl;
        }, nullptr);
    }
}



// Create a shader program from the given vertex and fragment shader paths
GLuint compileShader(const char* vertexCode, const char* fragmentCode) {
    GLuint vertex, fragment, program;

    // Vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, nullptr);
    glCompileShader(vertex);
    int success;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr << "Error: Vertex shader compilation failed\n" << infoLog << std::endl;
    }

    // Fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cerr << "Error: Fragment shader compilation failed\n" << infoLog << std::endl;
    }

    // Shader program
    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Error: Shader program linking failed\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}




// Default constructor
GLWindow::GLWindow()
{
     if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        
    }
    W_width = 0;
    W_height = 0;
    GLWin = nullptr;
    title = " ";

    // Defaulting the paths to my images and can be changed from utility function below
    std::string path = "Images/image.png";
    std::string depth_map = "Images/depth_map.png";
    std::string depth_normals = "Images/depth_normals.png";
    std::string albedo = "Images/test_albedo.png";
    std::string residuals = "Images/test_residuals.png";
    std::string diffuse_shading = "Images/test_diffuse_shading.png";

    tex_data.setPaths(path,depth_map,depth_normals,albedo,residuals,diffuse_shading);
   
    std::cout<<"Window created\n";  
}

// Parameterized constructor
GLWindow::GLWindow(unsigned int width, unsigned int height, const char* newtitle )
    : W_width(width), W_height(height), GLWin(nullptr), title(newtitle) {
    // Setting up the window
    initGLFW();
 
    openWin();
  
    initGLAD();

    enableOpenGLDebugging();
   
    setupViewport();

    // Defaulting the paths to my images and can be changed from utility function below
    std::string path = "Images/image.png";
    std::string depth_map = "Images/depth_map.png";
    std::string depth_normals = "Images/depth_normals.png";
    std::string albedo = "Images/test_albedo.png";
    std::string residuals = "Images/test_residuals.png";
    std::string diffuse_shading = "Images/test_diffuse_shading.png";

   tex_data.setPaths(path,depth_map,depth_normals,albedo,residuals,diffuse_shading);

    // Load and create shaders
    shaderProgram = createShaderProgram( "shaders/ImageVertex.glsl","shaders/ImageFragment.glsl");



    depthTexture = PrepareTexture("Depth Map");

   
    // Create the quad VAO and VBO for rendering
    createQuadVAO();
 
  if (quadVAO == 0 || quadVBO == 0 || quadEBO == 0) {
    std::cerr << "Error: VAO, VBO, or EBO not created properly!" << std::endl;
}
    
}

// Destructor
GLWindow::~GLWindow() {
    if (quadEBO) glDeleteBuffers(1, &quadEBO);
    if (quadVBO) glDeleteBuffers(1, &quadVBO);
    if (quadVAO) glDeleteVertexArrays(1, &quadVAO);

    glfwTerminate();
    std::cout << "Window destroyed\n";
}

// Utility function to change image paths
void GLWindow::updatePaths(std::string path, std::string depth_map, std::string depth_normals, std::string albedo, std::string residuals, std::string diffuse_shading)
{

   tex_data.setPaths(path,depth_map,depth_normals,albedo,residuals,diffuse_shading);
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

// Function to load the shaders from the path and type to be used in the shader program
GLuint GLWindow::loadShader(const std::string& path, GLenum type) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << path << std::endl;
        return 0;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string shaderSource = buffer.str();
    //std::cout<<shaderSource<<"\n";
    const char* shaderCode = shaderSource.c_str();
    //std::cout<<shaderCode<<"\n";

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation failed: " << infoLog << std::endl;
        return 0;
    }
    return shader;
}

// Function to create shader program
GLuint GLWindow::createShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) {
    GLuint vertexShader = loadShader(vertexPath, GL_VERTEX_SHADER);
    GLuint fragmentShader = loadShader(fragmentPath, GL_FRAGMENT_SHADER);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
GLenum error = glGetError();
if (error != GL_NO_ERROR) {
    std::cerr << "OpenGL Error after linking: " << error << std::endl;
    return 0;
}
    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
     error = glGetError();
if (error != GL_NO_ERROR) {
    std::cerr << "OpenGL Error after getpr: " << error << std::endl;
    return 0 ;
}
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Program linking failed: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

// initialize the GLFW library with correct version and profile
void GLWindow::initGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        exit(-1);
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}


// Function to open the window

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
    std::cout<<GLWin<<"\n";

}

// Function to initialize GLAD
void GLWindow::initGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        exit(-1);
    }
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    GLenum error = glGetError();
if (error != GL_NO_ERROR) {
    std::cerr << "OpenGL Error after createQuadVAO: " << error << std::endl;
    return ;
}
}


// Function to set up the viewport
void GLWindow::setupViewport() {
    glViewport(0, 0, W_width, W_height);
    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    glDepthFunc(GL_LESS);     // Depth comparison function
}

// OpenGL callback function to handle window resizing
void GLWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    GLWindow* scene = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
    if (scene) {
        glViewport(0, 0, width, height);
    }
}


GLuint GLWindow::PrepareTexture(std::string im) {
    GLuint depthTex;
    glGenTextures(1, &depthTex);
    glBindTexture(GL_TEXTURE_2D, depthTex);
    
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL Error after glBindTexture: " << error << std::endl;
    }
   //unsigned char * image_data = 'f';
   //std::cout<<"Image data"<<image_data<<"\n";
    tex_data.readImageData(im);
    unsigned char * image_data = tex_data.image_data;
    int width = tex_data.width ,height =  tex_data.height, channels = tex_data.channels;
  
    if (image_data)
    {
        GLenum format;
        if (channels == 1)
            format = GL_RED;
        if (channels == 3)

            format = GL_RGB;
        else if (channels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, depthTex);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image_data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_2D, 0); 

        std::cout << "Depth map texture created successfully. ID: " << depthTex << std::endl;
        stbi_image_free(image_data);
    }
    else
    {
        std::cout << "Texture failed to load at path \n" ;
        stbi_image_free(image_data);
    }

    return depthTex;
}


void GLWindow::createQuadVAO() {
    if (quadVAO == 0) {
        float quadVertices[] = {
           -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f
        };

        unsigned int quadIndices[] = {
            0, 1, 2,
    0, 2, 3
        };

        // Generate buffers
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glGenBuffers(1, &quadEBO);

        glBindVertexArray(quadVAO);

        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        std::cout << "Quad VAO created: " << quadVAO << ", VBO: " << quadVBO << ", EBO: " << quadEBO << std::endl;
    }
}
void checkOpenGLError(const std::string& location) {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL Error at " << location << ": " << error << std::endl;
    }
}
// void GLWindow::renderQuad() {
//     if (quadVAO == 0) {
//         std::cerr << "Error: Quad VAO is not initialized!" << std::endl;
//         return;
//     }

//     glBindVertexArray(quadVAO);
// glGetError();
//    // GLenum error = 
//     // if (error != GL_NO_ERROR) {
//     //     std::cerr << "OpenGL Error at glBindVertexArray in renderQuad: " << error << std::endl;
//     //     return;
//     // }

//     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

//     // GLenum error = glGetError();
//     // if (error != GL_NO_ERROR) {
//     //     std::cerr << "OpenGL Error at glDrawElements in renderQuad: " << error << std::endl;
//     //     return;
//     // }

//     glBindVertexArray(0);
// }
// Function to create the shader and must be called if paths are changed
Shader GLWindow::processTextures(std::string fragpath, std::string vertpath)
{
    Shader shader(vertpath.c_str(), fragpath.c_str());

    // load textures
     diffuseMap = PrepareTexture("Image");
     normalMap = PrepareTexture("Depth Normals");
     heightMap = PrepareTexture("Depth Map");
     albedoMap = PrepareTexture("Albedo");
     residualMap = PrepareTexture("Residuals");
     shadingMap = PrepareTexture("Diffuse Shading");



    // shader configuration
    // --------------------
    shader.use();
    shader.setInt("diffuseMap", 0);
    shader.setInt("normalMap", 1);
    shader.setInt("depthMap", 2);
    shader.setInt("albedoMap", 3);
    shader.setInt("residualMap", 4);
    shader.setInt("shadingMap", 5);
    
    return shader;
}


// Function to bind all textures to the shader
void GLWindow::BindTextures(Shader shader)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normalMap);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, heightMap);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, albedoMap);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, residualMap);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, shadingMap);

}




