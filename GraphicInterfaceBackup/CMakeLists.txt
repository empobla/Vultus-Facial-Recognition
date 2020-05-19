# When doing "cmake" command, do: cmake ../ -DCMAKE_CXX_FLAGS="-std=c++11"

cmake_minimum_required(VERSION 3.14)
project(GUI)

## OPEN CV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(
GUI
${PROJECT_SOURCE_DIR}/Screens.cpp
${PROJECT_SOURCE_DIR}/GUI.cpp
)

target_link_libraries(GUI ${OpenCV_LIBS})