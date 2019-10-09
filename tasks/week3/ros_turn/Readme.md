## Title Here: Readme Tutorial

- Author: 黄浩东
- Revised: 黄浩东
- Date: 2019-10-07 
- Version: 1.0.0
- Abstract: 完成控制小车实现转弯 

### Functions:
	在无噪声的情况下，通过Publisher控制小车转弯（转一个圆形） 
        多线程&20Hz
### Interfaces:

    ros::Rate loop_rate(20);//设置20Hz 

    while (ros::ok()) {
	    velocity={(radius*cos(angle)),(radius*sin(angle)),0.0}; //radius=0.008,angle=0
	    yaw=angle; 
	    car.set_yaw(yaw);
	    
	    car.set_velocity(velocity); //设置小车速度
            car.update_();//小车状态更新
	    
	    angle+=degree/4;//degree=PI/180
	    

            ros::MultiThreadedSpinner spinner(4);//采用多线程
            spinner.spin();

            loop_rate.sleep();
    }
        
### Depend Libraries:
        #include "parser.h"
        #include <urdf/model.h>
        #include <string>
        #include <sensor_msgs/JointState.h>
        #include <tf/transform_broadcaster.h>
        #include <geometry_msgs/Point.h>
        #include <ros/ros.h>
        #include <random>
        #include <iomanip>
        #include <math.h>

依赖库：
        -依赖ros 
编译提示：
        $ catkin_make //在ros_turn目录下 
        $ source devel/setup.bash 
测试程序：
        $ roslaunch launch/little_car.launch
