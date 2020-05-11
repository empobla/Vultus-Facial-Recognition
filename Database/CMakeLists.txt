cmake_minimum_required(VERSION 3.2)

project(Database)

set(CMAKE_CXX_STANDARD 11) 

find_package( OpenCV REQUIRED )
set(OpenCV_DIR "/usr/local/include/opencv")
include_directories(${OpenCV_INCLUDE_DIRS})

## Mongo
find_package(mongocxx REQUIRED)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  find_package(Boost 1.56.0 REQUIRED)
  if (CMAKE_VERSION VERSION_LESS 3.15.0)
    target_include_directories(Database PRIVATE ${Boost_INCLUDE_DIRS})
  else()
    target_link_libraries(Database PRIVATE Boost::boost)
  endif()
endif()

add_executable(
    Database
    ${PROJECT_SOURCE_DIR}/test.cpp
    ${SOURCE_FILES}
)
target_link_libraries(Database PRIVATE mongo::mongocxx_shared ${OpenCV_LIBS})
