# Parallax Mapping 2D Images: Simulating Parallax Effect on Images Using OpenGL

## Project Overview
This project simulates a parallaz effect (2.5D) on a regular 2D image in an OpenGL scene. The image is passed first to extract depth map, surface normals, and intrinsic decomposition.These maps are used as input textures to the OpenGL scene.

## Table of Contents
- [Project Overview](#project-overview)
- [Usage](#usage)
- [Pipeline](#pipeline)


## Usage
This project is used to provide a pipeline to have a more accurate backdrops in VFX scenes. 
It can be used in all sorts of VFX scenes with static images as backdrops such as windows and moving cars.

## Pipeline

1. **Depth Estimation (Python)**:
   - Uses Depth Anythin V2 model to generate depth maps to be used as textures. (https://github.com/DepthAnything/Depth-Anything-V2)

2. **Surface Normals Estimation (Python)**:
   - Uses DSINE model to run the estimation on the image. (

3. **Intrinsic Image Decomposition(Python)**:
   - Running ML model to decompose layers of the RGB image to be used for adjusting lighting of the image. (https://github.com/compphoto/Intrinsic)
  

4. **OpenGL Parallax Occlusion(C++)**:
   - Taking the outputs from the ML models as textures, this code creates an OpenGL while simulating parallax mapping (https://github.com/JoeyDeVries/LearnOpenGL/tree/master/src/5.advanced_lighting/5.3.parallax_occlusion_mapping)


[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/RM1pL2Qm)
