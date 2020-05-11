cmake_minimum_required(VERSION 3.2)

project(Verification)

## OPEN CV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

## DLIB
include(FetchContent)
FetchContent_Declare(dlib
  GIT_REPOSITORY https://github.com/davisking/dlib.git
)
FetchContent_MakeAvailable(dlib)

## Mongo
find_package(mongocxx REQUIRED)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  find_package(Boost 1.56.0 REQUIRED)
  if (CMAKE_VERSION VERSION_LESS 3.15.0)
    target_include_directories(Verification PRIVATE ${Boost_INCLUDE_DIRS})
  else()
    target_link_libraries(Verification PRIVATE Boost::boost)
  endif()
endif()

add_executable(Verification
${PROJECT_SOURCE_DIR}/verification.cpp
)

target_link_libraries(Verification PRIVATE mongo::mongocxx_shared ${OpenCV_LIBS} dlib::dlib)

add_custom_target(run
    COMMAND Verification
    DEPENDS Verification
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)