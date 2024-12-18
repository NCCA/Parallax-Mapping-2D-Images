#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "Image.h"

using json = nlohmann::json;


int main() {


     // Path to the JSON file containing the depth map
    std::string json_file = "JSON_files/20241121_111331369_iOS.json";
 
    
    Image depth(json_file);
    depth.readDepthMap();
    
    depth.displayDepthMap();
    
  
    return 0;
}