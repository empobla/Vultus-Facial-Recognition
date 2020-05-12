# Check rob's repo ;)
# https://github.com/robtry/face-alignment/blob/master/CMakeLists.txt
#
# When doing "cmake" command, do: cmake ../ -DCMAKE_CXX_FLAGS="-std=c++11"

cmake_minimum_required(VERSION 3.14)
message("Module 1 'FaceDetection' starting ...")
project(FaceDetection)

## OPEN CV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(
FaceDetection
${PROJECT_SOURCE_DIR}/source/FaceDetection.cpp
${PROJECT_SOURCE_DIR}/source/main.cpp
)

target_link_libraries(FaceDetection ${OpenCV_LIBS})