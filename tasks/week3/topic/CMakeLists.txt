cmake_minimum_required(VERSION 2.8.3)
project(topic)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)
add_message_files(
  FILES
  myMsg.msg
)
generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(CATKIN_DEPENDS message_runtime)




include_directories(include  ${catkin_INCLUDE_DIRS})

add_executable(Publisher src/Publisher.cpp)
target_link_libraries(Publisher ${catkin_LIBRARIES})
add_dependencies(Publisher beginner_tutorials_generate_messages_cpp)

add_executable(Subscriber src/Subscriber.cpp)
target_link_libraries(Subscriber ${catkin_LIBRARIES})
add_dependencies(Subscriber beginner_tutorials_generate_messages_cpp)
