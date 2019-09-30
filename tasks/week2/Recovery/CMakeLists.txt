cmake_minimum_required(VERSION 3.10)
project(main)

find_package(OpenCV 3.2.0 REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/)


include_directories(include)
include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCES src/Recovery.cpp test/test.cpp)

add_executable(main  ${SOURCES})

target_link_libraries(main ${OpenCV_LIBS})
