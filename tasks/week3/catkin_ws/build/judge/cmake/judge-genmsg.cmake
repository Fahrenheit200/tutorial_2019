# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "judge: 0 messages, 1 services")

set(MSG_I_FLAGS "-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(judge_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/judge/srv/def_message.srv" NAME_WE)
add_custom_target(_judge_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "judge" "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/judge/srv/def_message.srv" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(judge
  "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/judge/srv/def_message.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/judge
)

### Generating Module File
_generate_module_cpp(judge
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/judge
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(judge_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(judge_generate_messages judge_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/judge/srv/def_message.srv" NAME_WE)
add_dependencies(judge_generate_messages_cpp _judge_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(judge_gencpp)
add_dependencies(judge_gencpp judge_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS judge_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages

### Generating Services
_generate_srv_eus(judge
  "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/judge/srv/def_message.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/judge
)

### Generating Module File
_generate_module_eus(judge
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/judge
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(judge_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(judge_generate_messages judge_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/judge/srv/def_message.srv" NAME_WE)
add_dependencies(judge_generate_messages_eus _judge_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(judge_geneus)
add_dependencies(judge_geneus judge_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS judge_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(judge
  "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/judge/srv/def_message.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/judge
)

### Generating Module File
_generate_module_lisp(judge
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/judge
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(judge_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(judge_generate_messages judge_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/judge/srv/def_message.srv" NAME_WE)
add_dependencies(judge_generate_messages_lisp _judge_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(judge_genlisp)
add_dependencies(judge_genlisp judge_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS judge_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages

### Generating Services
_generate_srv_nodejs(judge
  "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/judge/srv/def_message.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/judge
)

### Generating Module File
_generate_module_nodejs(judge
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/judge
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(judge_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(judge_generate_messages judge_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/judge/srv/def_message.srv" NAME_WE)
add_dependencies(judge_generate_messages_nodejs _judge_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(judge_gennodejs)
add_dependencies(judge_gennodejs judge_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS judge_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(judge
  "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/judge/srv/def_message.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/judge
)

### Generating Module File
_generate_module_py(judge
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/judge
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(judge_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(judge_generate_messages judge_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/judge/srv/def_message.srv" NAME_WE)
add_dependencies(judge_generate_messages_py _judge_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(judge_genpy)
add_dependencies(judge_genpy judge_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS judge_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/judge)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/judge
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(judge_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/judge)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/judge
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(judge_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/judge)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/judge
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(judge_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/judge)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/judge
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(judge_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/judge)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/judge\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/judge
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(judge_generate_messages_py std_msgs_generate_messages_py)
endif()
