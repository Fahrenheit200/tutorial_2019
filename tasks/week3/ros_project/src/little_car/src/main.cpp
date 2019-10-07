#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
#include <iomanip>
#include <boost/bind.hpp>
#include <math.h>
using namespace std;
SVector3 velo={0,0,0};
const double r=1.5;
void Callback(const geometry_msgs::Point::ConstPtr& v)
{
    velo={v->x,v->y,v->z};
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
    little_car car;//初始化控制对象  小车
    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
    car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
    /* 
     *请添加一个Subscriber，从你自己编写的Publisher处订阅指令
     */
    ros::Subscriber sub = n.subscribe("v_little_car", 100, Callback);

    ros::Rate loop_rate(60);
    car.set_noise_level(0);  //设置噪声等级
    float yaw = 0.0;
    while (ros::ok()) {
	ros::spinOnce();

	SVector3 pos=car.get_position();

        //走S型曲线	
	if(fmod(pos.y,4*r)<r){
	    velo.x=velo.x*((r*(int)(pos.y/(4*r)+1)-pos.y)/r);
	    velo.y=velo.y*(pos.x/r);
	}
	else if(fmod(pos.y,4*r)>r && fmod(pos.y,4*r)<2*r){
	    velo.x=velo.x*((r*(int)(pos.y/(4*r)+1)-pos.y)/r);
	    velo.y=velo.y*(pos.x/r);
	}
	else if(fmod(pos.y,4*r)>2*r && fmod(pos.y,4*r)<3*r){
	    velo.x=velo.x*((pos.y-3*r*(int)(pos.y/(4*r)+1))/r);
	    velo.y=velo.y*(-pos.x/r);
	}
	else if(fmod(pos.y,4*r)>3*r && fmod(pos.y,4*r)<4*r){
	    velo.x=velo.x*((pos.y-3*r*(int)(pos.y/(4*r)+1))/r);
	    velo.y=velo.y*(-pos.x/r);
	}
	else {velo.y=0.00000001; velo.x=0.00000001;}
	car.set_velocity(velo);
        car.update_(); //小车状态更新
        loop_rate.sleep();
    }
    return 0;
}
