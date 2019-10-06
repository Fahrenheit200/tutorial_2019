# ros 
-Author: lee
-revised: lee
-date 2019-10-6
-version 3.0.0
-abstract: about ros coding

### publisher and subscribe
#### how to run
	 cd ros_project
	catkin_make
	source devel/setup.bash
	roslaunch week3msg week3msg.launch
	（可以在一个新终端 rosrun week3msg publisher）
#### depend 
	roscpp
	std_msgs
	message_generation
#### msg
	num.msg

### service and client and server
#### how to run
	 cd ros_project
        catkin_make
        source devel/setup.bash
        roscore
	rosrun week3msg service
	rosrun week3msg server
	rosrun week3msg client
	(以上四条要在四个终端，client需要重复)
#### depend
	 roscpp
        std_msgs
        message_generation
	dynamic_reconfigure
#### server
	将service传过来的值保存在动态服务器里
	

