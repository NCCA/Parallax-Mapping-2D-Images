#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "Image.h"
#include "ImageData.h"
#include <windows.h>

using json = nlohmann::json;

int main() {


     // Path to the JSON file containing the depth map
    std::string json_file = "assets/JSON_files/20241121_111331369_iOS.png";
   
    // Parse the JSON file into a nlohmann::json object
    json j;

    Image depth(json_file);
    // depth.readDepthMap(); 
    // depth.displayDepthMap();

    depth.readDepthNormals();
    depth.displayDepthNormals();
    
  
    return 0;
}
