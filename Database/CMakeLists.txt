cmake_minimum_required(VERSION 3.10)

project(Database)

set(CMAKE_CXX_STANDARD 11) 

find_package( OpenCV REQUIRED )
set(OpenCV_DIR "/usr/local/include/opencv")
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories("/usr/local/lib")

add_executable(
    Database
    test.cpp
    ${SOURCE_FILES}
)

target_link_libraries(Database ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(Database ${LIBBSONCXX_LIBRARIES})
target_link_libraries(Database ${OpenCV_LIBS})


