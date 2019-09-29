cmake_minimum_required(VERSION 3.10)   #版本要求

project(Demo)      #项目名称

include_directories(include)   #添加头文件

FILE(GLOB_RECURSE CURRENT_INCLUDE include/Recovery.h)

find_package(OpenCV 3.2.0 REQUIRED)

FILE(GLOB_RECURSE CURRENT_SOURCES src/main.cpp Recovery.cpp)

add_executable(Demo ${CURRENT_SOURCES} ${CURRENT_INCLUDE}) 

target_link_libraries(Demo ${OpenCV_LIBS})

