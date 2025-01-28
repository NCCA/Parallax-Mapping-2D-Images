## Running the Code
First you need to install vcpkg for the used libraries
```markdown
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat
vcpkg integrate install
```
and then use it to install the following libraries
- glm
- glad
- glfw3
- GLEW
- OpenCV
- assimp
## Building the Code
After cloning the repo and setting up this folder. create a build folder to run cmake
```markdown
mkdir build
cd build
cmake ..
cmake --build .\ 
