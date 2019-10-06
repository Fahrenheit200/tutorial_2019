cmake_minimum_required(VERSION 2.8.3)
project(pub_sub)

## Find catkin macros and libraries
find_package(catkin REQUIRED roscpp rospy std_msgs message_generation)

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate messages in the 'msg' folder
add_message_files(
   FILES
   MyMsg.msg
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
 include
 ${catkin_INCLUDE_DIRS}
)

add_executable(publisher src/publisher.cpp )
#必须添加add_dependencies，否则找不到自定义的msg产生的头文件
add_dependencies(publisher pub_sub_generate_messages_cpp)
target_link_libraries(publisher ${catkin_LIBRARIES})

add_executable(subscriber src/subscriber.cpp )
add_dependencies(subscriber pub_sub_generate_messages_cpp)
target_link_libraries(subscriber ${catkin_LIBRARIES})
