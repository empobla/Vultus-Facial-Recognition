cmake_minimum_required(VERSION 3.14)
project(GUI)

## OPEN CV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

## DLIB
find_package( dlib REQUIRED )


## MONGO
find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories("/usr/local/lib")

## Face Detection
include_directories(../Face_Detection/source/)
set(SOURCEDETECTION ../Face_Detection/source/FaceDetection.cpp)
# Face Alignment
include_directories(../Face_Alignment/src/faceAlignment)
set(SOURCEALIGNMENT ../Face_Alignment/src/faceAlignment/align.cpp)
# Feature Extraction
include_directories(../Feature_Extraction/source)
set(SOURCEEXTRACTION ../Feature_Extraction/source/feature_detection.cpp)
# DB
include_directories(../Database/src/include)
set(SOURCEDB ../Database/src/Cuatec.cpp ../Database/src/DBManagerInterface.cpp)
#Feature Recognition
include_directories(../_Face_Recognition/src/)
set(SOURCEFR ../_Face_Recognition/src/Face_Recognition.cpp)

add_executable(GraphicInterface
${PROJECT_SOURCE_DIR}/GUI.cpp
${SOURCEDETECTION}
${SOURCEALIGNMENT}
${SOURCEEXTRACTION}
${SOURCEDB}
${SOURCEFR}
${PROJECT_SOURCE_DIR}/Screens.cpp
)

target_link_libraries(GraphicInterface ${OpenCV_LIBS} dlib::dlib ${LIBMONGOCXX_LIBRARIES} ${LIBBSONCXX_LIBRARIES})
