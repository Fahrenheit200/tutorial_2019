cmake_minimum_required(VERSION 3.12.1) 
find_package(OpenCV 3.2.0 REQUIRED)

project(main)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/)

include_directories(include) 
include_directories(${OpenCV_INCLUDE_DIRS})

set(my_source test/test.cpp src/Recovery.cpp)

add_executable(main  ${my_source}) 

target_link_libraries(main ${OpenCV_LIBS})
