cmake_minimum_required(VERSION 3.14)
message("Module 1 'FaceDetection' starting ...")
project(FaceDetection)

## OPEN CV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

## DLIB
include(FetchContent)
FetchContent_Declare(dlib
  GIT_REPOSITORY https://github.com/davisking/dlib.git
)
FetchContent_MakeAvailable(dlib)

add_executable(FaceDetection
${PROJECT_SOURCE_DIR}/source/FaceDetection.cpp
${PROJECT_SOURCE_DIR}/source/main.cpp
)

target_link_libraries(FaceAlignment ${OpenCV_LIBS} dlib::dlib)