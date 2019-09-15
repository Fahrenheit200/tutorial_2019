cmake_minimum_required(VERSION 2.8)
project(max_common_suffix)

set(CMAKE_CXX_STANDARD 11)

include_directories(inc)
add_executable(${PROJECT_NAME} src/MaxCommonSuffix.cpp test/main.cpp)

