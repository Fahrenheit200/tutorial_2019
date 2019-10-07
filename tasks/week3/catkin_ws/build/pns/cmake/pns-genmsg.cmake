# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "pns: 1 messages, 0 services")

set(MSG_I_FLAGS "-Ipns:/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/pns/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(pns_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/pns/msg/def_message.msg" NAME_WE)
add_custom_target(_pns_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "pns" "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/pns/msg/def_message.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(pns
  "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/pns/msg/def_message.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pns
)

### Generating Services

### Generating Module File
_generate_module_cpp(pns
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pns
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(pns_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(pns_generate_messages pns_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/pns/msg/def_message.msg" NAME_WE)
add_dependencies(pns_generate_messages_cpp _pns_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pns_gencpp)
add_dependencies(pns_gencpp pns_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pns_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(pns
  "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/pns/msg/def_message.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pns
)

### Generating Services

### Generating Module File
_generate_module_eus(pns
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pns
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(pns_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(pns_generate_messages pns_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/pns/msg/def_message.msg" NAME_WE)
add_dependencies(pns_generate_messages_eus _pns_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pns_geneus)
add_dependencies(pns_geneus pns_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pns_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(pns
  "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/pns/msg/def_message.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pns
)

### Generating Services

### Generating Module File
_generate_module_lisp(pns
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pns
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(pns_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(pns_generate_messages pns_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/pns/msg/def_message.msg" NAME_WE)
add_dependencies(pns_generate_messages_lisp _pns_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pns_genlisp)
add_dependencies(pns_genlisp pns_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pns_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(pns
  "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/pns/msg/def_message.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pns
)

### Generating Services

### Generating Module File
_generate_module_nodejs(pns
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pns
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(pns_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(pns_generate_messages pns_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/pns/msg/def_message.msg" NAME_WE)
add_dependencies(pns_generate_messages_nodejs _pns_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pns_gennodejs)
add_dependencies(pns_gennodejs pns_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pns_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(pns
  "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/pns/msg/def_message.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pns
)

### Generating Services

### Generating Module File
_generate_module_py(pns
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pns
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(pns_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(pns_generate_messages pns_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/lomgahong/tutorial_2019/tasks/week3/catkin_ws/src/pns/msg/def_message.msg" NAME_WE)
add_dependencies(pns_generate_messages_py _pns_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pns_genpy)
add_dependencies(pns_genpy pns_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pns_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pns)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pns
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(pns_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pns)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pns
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(pns_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pns)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pns
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(pns_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pns)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pns
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(pns_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pns)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pns\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pns
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(pns_generate_messages_py std_msgs_generate_messages_py)
endif()
