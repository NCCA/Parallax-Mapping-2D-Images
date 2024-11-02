# Depth-Based Pixel Diffraction": Simulating Light Distortion in Video Using Depth Estimation

## Project Overview
This project simulates a realistic  diffraction effect on video using depth estimation. Using the Depth Estimation model, we generate depth maps from video frames and then apply pixel-based translation to mimic light distortion based on depth.

## Table of Contents
- [Project Overview](#project-overview)
- [Usage](#usage)
- [Pipeline](#pipeline)
- [TBC Constraints](#tbc-constraints)

## Usage
This project can be used for multiple applications according to features implemented. Uses include: 
- Applying underwater effects on videos
- Can be expanded to include multiple liquids diffraction rates
- Distorting videos for different glasses POV
- Applying binoculars or night vision goggles effects on videos

## Pipeline

1. **Depth Estimation (Python)**:
   - Uses Depth Estimation ML model to generate depth maps for each frame in the input video.

2. **Pixel Translation (C++)**:
   - Applies pixel shifts based on depth values to simulate diffraction.

3. **Video Reconstruction (C++)**:
   - Reassembles frames with the effect applied into a final output video.

## TBC Constraints
- The ML model to be used
- The graphics C++ library
- The data type that will be exported from  Python to C++
- The features and applications that will be developed as mention in the [Usage](#usage) section

[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/RM1pL2Qm)
