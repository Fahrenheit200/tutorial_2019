cmake_minimum_required(VERSION 2.8.3)
project(srv_cli)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  dynamic_reconfigure
  std_msgs
  message_generation
)

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate services in the 'srv' folder
 add_service_files(
   FILES
   LessThan.srv
 )


## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs
 )

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(server src/server.cpp)
target_link_libraries(server ${catkin_LIBRARIES})
add_dependencies(server srv_cli_generate_messages_cpp)

add_executable(client src/client.cpp)
target_link_libraries(client ${catkin_LIBRARIES})
add_dependencies(client srv_cli_generate_messages_cpp)

add_executable(dynamic_param_server src/dynamic_param_server.cpp)
target_link_libraries(dynamic_param_server ${catkin_LIBRARIES})
add_dependencies(dynamic_param_server srv_cli_generate_messages_cpp)

#add dynamic reconfigure api
#find_package(catkin REQUIRED dynamic_reconfigure)
generate_dynamic_reconfigure_options(
  cfg/dynamic_param.cfg
)

# make sure configure headers are built before any node using them
add_dependencies(dynamic_param_server ${PROJECT_NAME}_gencfg)
