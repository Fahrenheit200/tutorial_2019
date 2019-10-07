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
using namespace std;

int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
	little_car car;//初始化控制对象  小车
    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
	
	SVector3 velocity={0,0.008,0};  //速度向量
	car.set_noise_level(0);		   //设置噪声等级
	float yaw = 0.0;
	
	const double degree=M_PI/180;
	const double radius=0.008;
	double angle=0;
	
	ros::Rate loop_rate(20);//设置20Hz 
	
    while (ros::ok()) {
	    velocity={(radius*cos(angle)),(radius*sin(angle)),0.0};
	    yaw=angle;
	    car.set_yaw(yaw);
	    
	    car.set_velocity(velocity);//设置小车速度
        car.update_();//小车状态更新
	    
	    angle+=degree/4;
	    
	    ros::MultiThreadedSpinner spinner(4);//采用多线程发布 
        spinner.spin();
        
		loop_rate.sleep();
    }


    return 0;
}
