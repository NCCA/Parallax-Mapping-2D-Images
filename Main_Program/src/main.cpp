#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/photo/photo.hpp"
#include <vector>
#include "GLWindow.h"

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "shader.h"
#include "camera.h"
#include "model.h"

using namespace cv;


// Declaration of supporting functions, implementation is after the main function

void concatenateImages(std::string image_path, std::string extension_path, std::string output_path);
void convert_TIFF_PNG(std::string tiff_path, std:: string png_path);
void segmentImage(const std::string& imagePath, const std::string& depthMapPath, int layerCount);

// Declaration of functions used in main 

void renderQuad();
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void processInput(GLFWwindow *window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);



glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 900;
float heightScale = 0.1f;
float lightScale = 0.1f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float yaw = -90.0f;
float pitch = 0.0f;
float lastX = SCR_WIDTH / 2.0;
float lastY = SCR_HEIGHT / 2.0;
bool firstMouse = true;


GLWindow win;



int main()
{

    // Change the current working directory had to do so for my cmake to work
    const char* newDirectory = "C:/Users/omar-/Desktop/ASE_Project/build/";
    SetCurrentDirectory(newDirectory);
    char buffer[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, buffer);


 


    // //Run only once to get the PNG files
    // convert_TIFF_PNG("Images/ALBEDO_map.tiff", "Images/test_albedo.png");
    // convert_TIFF_PNG("Images/Residual_map.tiff", "Images/test_residuals.png");
    // convert_TIFF_PNG("Images/diffuse_shading_map.tiff", "Images/test_diffuse_shading.png");


    // To be run only one to segment and extend images 
    //segmentImage("Images/Image.png", "Images/depth_map.png",  2);
    // concatenateImages("Images/Image.png", "Images/Extension.png", "Images/concatenatedImage.png");
    // concatenateImages("Images/depth_map.png", "Images/depth_map.png", "Images/concatenateddepth.png");
    // concatenateImages("Images/depth_normals.png", "Images/depth_normals.png", "Images/concatenatenormals.png");
    // concatenateImages("Images/test_albedo.png", "Images/test_albedo.png", "Images/concatenatedalbedo.png");
    // concatenateImages("Images/test_residuals.png", "Images/test_residuals.png", "Images/concatenatedresidual.png");
    // concatenateImages("Images/test_diffuse_shading.png", "Images/test_diffuse_shading.png", "Images/concatenatedshading.png");

  
    
    
    // glfw: initialize and configure
    win.initGLFW();
    win.W_width = 1000;
    win.W_height = 800;
    

    // glfw window creation
    win.openWin();
    glfwMakeContextCurrent(win.GLWin);
    glfwSetFramebufferSizeCallback(win.GLWin, win.framebuffer_size_callback);
    glfwSetCursorPosCallback(win.GLWin, mouse_callback);
    glfwSetScrollCallback(win.GLWin, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(win.GLWin, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    win.initGLAD();
    // glad: load all OpenGL function pointers
   

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // To change to extneded images
    //win.updatePaths("Images/Extended.png"," Images/concatenateddepth.png", "Images/concatenatenormals.png", "Images/concatenatedalbedo.png", "Images/concatenatedresidual.png", "Images/concatenatedshading.png");

    Shader shader = win.processTextures("shaders/ImageFragment.glsl", "shaders/ImageVertex.glsl");
   
    // To change to extneded images
   // win.updatePaths("Images/Extended.png"," Images/concatenateddepth.png", "Images/concatenatenormals.png", "Images/concatenatedalbedo.png", "Images/concatenatedresidual.png", "Images/concatenatedshading.png");
   // Shader shader2 = win.processTextures("shaders/ImageFragment.glsl", "shaders/ImageVertex.glsl");
    // lighting info
    // -------------
    glm::vec3 lightPos(0.5f, 1.0f, 0.3f);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(win.GLWin))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(win.GLWin);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // configure view/projection matrices
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        shader.use();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        // render parallax-mapped quad
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        shader.setMat4("model", model);
        shader.setVec3("viewPos", camera.Position);
        shader.setVec3("lightPos", lightPos);
        shader.setFloat("heightScale", heightScale); // adjust with Q and E keys
        shader.setFloat("lightScale", lightScale); // adjust with K and L keys
        win.BindTextures(shader);
        renderQuad();

  
    

        glfwSwapBuffers(win.GLWin);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;


}

// Implementation of the supporting functions that deals with images

void segmentImage(const std::string& imagePath, const std::string& depthMapPath, int layerCount) {

    //read the image and the depth map
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_UNCHANGED);
    cv::Mat depthMap = cv::imread(depthMapPath, cv::IMREAD_GRAYSCALE);
    
   // test if the images are loaded correctly
    if (image.empty() || depthMap.empty()) {
        std::cerr << "Failed to load image or depth map." << std::endl;
        return;
    }

    // convert the depth map to float
    depthMap.convertTo(depthMap, CV_32F, 1.0 / 255.0);

   // create a mask to segment the image
    float layerStep = 1.0f / layerCount;

    float flayerStart = 0.0f;
    float flayerEnd = flayerStart + layerStep + 0.1f;

       
    cv::Mat mask = ((depthMap > flayerEnd) & (depthMap< 0.94) );
   
    // create a layer with the segmented image
    cv::Mat layer(image.rows, image.cols, CV_8UC4, cv::Scalar(0, 0, 0, 0));
 
    // fill the layer with the segmented image
    for (int r = 0; r < image.rows; ++r) {
        for (int c = 0; c < image.cols; ++c) {
            if (mask.at<uint8_t>(r, c)) {
                cv::Vec3b color = image.at<cv::Vec3b>(r, c);
                layer.at<cv::Vec4b>(r, c) = cv::Vec4b(color[0], color[1], color[2], 255); 
            }
        }
    }

    // save the segmented image
    cv::Mat segments = image.clone();
   
    image.copyTo(segments, mask);
  
    cv::Mat result = image.clone();
    segments.copyTo(result, mask); 
    
    // inpaint  masked gap
    cv::Mat inpainted;
  
    cv::inpaint(result, mask, inpainted, 5, cv::INPAINT_TELEA);
    
    // flip new image to create new pattern 
    cv::Mat flipped;
    cv::flip(inpainted, flipped, 1); 
    cv::imwrite( "Images/Extension.png", flipped);

}


void concatenateImages(std::string image_path, std::string extension_path, std::string output_path) {

    // read the images
    cv::Mat image = cv::imread(image_path);
    cv::Mat extension = cv::imread(extension_path);

    // test if the images are loaded correctly
    if (image.empty() || extension.empty()) {
        std::cout << "Could not open or find the images!" << std::endl;
        return ;
    }

    // concatenate the images
    cv::Mat merged;
    cv::Mat flipped;
    cv::flip(extension, flipped, 1); 
    cv::hconcat(image, flipped, merged);
    cv::imwrite(output_path, merged);

}

void convert_TIFF_PNG(std::string tiff_path, std:: string png_path)
{
    // read the tiff image
    cv::Mat image = cv::imread(tiff_path, cv::IMREAD_UNCHANGED);
    cv::Mat normalizedImage;
    double minVal, maxVal;
    cv::minMaxLoc(image, &minVal, &maxVal); 


    // normalize the image
    image.convertTo(normalizedImage, CV_8UC3, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
 

    // test if the image is loaded correctly
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the TIFF file" << std::endl;
        return ;
    }

    // save the image as a PNG file
    if (!cv::imwrite(png_path, normalizedImage)) {
        std::cerr << "Error: Could not write the PNG file" << std::endl;
        return ;
    
    }
}


// The following section is from :-
// Joey de Vries (2020). Learn OpenGL - Graphics Programming [online]. [Accessed 2025]. 
// Available from: "https://learnopengl.com/book/book_pdf.pdf".

// These functions and their usage in the main function is from the book above
// However they were modified to expand the features of the program
// Buttons were added to adjust lighting, height and moving up and down

// Learn OpenGL functions used in the main function

// renders a 1x1 quad in NDC with manually calculated tangent vectors
// ------------------------------------------------------------------
unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
    if (quadVAO == 0)
    {
        // positions
        glm::vec3 pos1(-1.0f,  1.0f, 0.0f);
        glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
        glm::vec3 pos3( 1.0f, -1.0f, 0.0f);
        glm::vec3 pos4( 1.0f,  1.0f, 0.0f);
        // texture coordinates
        glm::vec2 uv1(0.0f, 1.0f);
        glm::vec2 uv2(0.0f, 0.0f);
        glm::vec2 uv3(1.0f, 0.0f);
        glm::vec2 uv4(1.0f, 1.0f);
        // normal vector
        glm::vec3 nm(0.0f, 0.0f, 1.0f);

        // calculate tangent/bitangent vectors of both triangles
        glm::vec3 tangent1, bitangent1;
        glm::vec3 tangent2, bitangent2;
        // triangle 1
        // ----------
        glm::vec3 edge1 = pos2 - pos1;
        glm::vec3 edge2 = pos3 - pos1;
        glm::vec2 deltaUV1 = uv2 - uv1;
        glm::vec2 deltaUV2 = uv3 - uv1;

        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
        tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
        tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
        tangent1 = glm::normalize(tangent1);

        bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
        bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
        bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
        bitangent1 = glm::normalize(bitangent1);

        // triangle 2
        // ----------
        edge1 = pos3 - pos1;
        edge2 = pos4 - pos1;
        deltaUV1 = uv3 - uv1;
        deltaUV2 = uv4 - uv1;

        f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
        tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
        tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
        tangent2 = glm::normalize(tangent2);


        bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
        bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
        bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
        bitangent2 = glm::normalize(bitangent2);


        float quadVertices[] = {
            // positions            // normal         // texcoords  // tangent                          // bitangent
            pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
            pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
            pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

            pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
            pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
            pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
        };
        // configure plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // Move the camera forward and add to the height scale
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
        heightScale += 0.0008f;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // Move the camera backward and subtracts to the height scale
        {
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        heightScale -= 0.0008f;
}

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // Move the camera left
        camera.ProcessKeyboard(LEFT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // Move the camera right
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) // Move the camera up
        camera.ProcessKeyboard(UP, deltaTime); 

    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) // Move the camera down
        camera.ProcessKeyboard(DOWN, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) // Adjust the height scale down
    {
        if (heightScale > 0.0f)
            heightScale -= 0.0005f;
        else
            heightScale = 0.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) // Adjust the height scale up
    {
        if (heightScale < 1.0f)
            heightScale += 0.0005f;
        else
            heightScale = 1.0f;
    }

      if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) // Adjust the light scale down
    {
        if (lightScale > 0.1f)
            lightScale -= 0.0005f;
        else
            lightScale = 0.1f;
    }
    else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) // Adjust the light scale up
    {
    
            lightScale += 0.0005f;
      
    }
     else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) // Reset the height scale
    {
    
           heightScale = 0.0f;
      
    }


    
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
