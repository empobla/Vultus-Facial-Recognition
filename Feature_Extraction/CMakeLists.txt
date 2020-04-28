# Check rob's repo ;)
# https://github.com/robtry/face-alignment/blob/master/CMakeLists.txt

cmake_minimum_required(VERSION 3.14)
message("Module 3 'Feature Detection' starting ...")
project(FeatureDetection)

## OPEN CV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

## DLIB
include(FetchContent)
FetchContent_Declare(dlib
  GIT_REPOSITORY https://github.com/davisking/dlib.git
)
FetchContent_MakeAvailable(dlib)


add_executable(FeatureDetection
${PROJECT_SOURCE_DIR}/source/feature_detection.cpp
${PROJECT_SOURCE_DIR}/source/main.cpp
)

target_link_libraries(FeatureDetection ${OpenCV_LIBS} dlib::dlib)