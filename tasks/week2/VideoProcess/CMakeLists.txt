# project name
PROJECT(opencv_test)
# requirement of cmake version
cmake_minimum_required(VERSION 3.5)

include_directories(include)
FILE(GLOB_RECURSE CURRENT_INCLUDE include/Recovery.h)

# set the directory of executable files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${opencv_test_SOURCE_DIR}/bin)

# find required opencv
find_package(OpenCV 3.2.0 REQUIRED)
# directory of opencv headers
include_directories(${OpenCV_INCLUDE_DIRS})


FILE(GLOB_RECURSE CURRENT_SOURCES src/main.cpp Recovery.cpp)
add_executable(opencv_test ${CURRENT_SOURCES} ${CURRENT_INCLUDE})

# directory of opencv library
link_directories(${OpenCV_LIBRARY_DIRS})
# opencv libraries
target_link_libraries(opencv_test ${OpenCV_LIBS})
