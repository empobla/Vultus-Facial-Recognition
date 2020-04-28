# https://docs.opencv.org/4.2.0/db/df5/tutorial_linux_gcc_cmake.html
# https://github.com/davisking/dlib/blob/master/examples/CMakeLists.txt

cmake_minimum_required(VERSION 3.14)
message("Module 2 'FaceAlignment' starting ...")
project(FaceAlignment)

## OPEN CV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

## DLIB
include(FetchContent)
FetchContent_Declare(dlib
  GIT_REPOSITORY https://github.com/davisking/dlib.git
)
FetchContent_MakeAvailable(dlib)

#include(./dlib/cmake ) ## old-way | need to download

# set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
# set(CMAKE_BUILD_FILES_DIRECTORY ${dir})

add_executable(FaceAlignment
#${PROJECT_SOURCE_DIR}/src/try.cpp
${PROJECT_SOURCE_DIR}/src/faceDetection/module1.cpp
${PROJECT_SOURCE_DIR}/src/faceAlignment/align.cpp
${PROJECT_SOURCE_DIR}/src/main.cpp
)

target_link_libraries(FaceAlignment ${OpenCV_LIBS} dlib::dlib)