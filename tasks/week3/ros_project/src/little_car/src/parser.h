#ifndef __PARSER_H
#define __PARSER_H
#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
typedef struct
{
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;
}SVector3;
class little_car
{
	private:
		SVector3 _velocity;	//小车速度
		SVector3 _position;  //小车位置
		SVector3 _noise;		//噪声
		tf::TransformBroadcaster broadcaster;
		sensor_msgs::JointState joint_state;
		geometry_msgs::TransformStamped odom_trans;
		geometry_msgs::Point _pub_position;
		void add_noise();
		void update_position();
	public:
		ros::Publisher joint_pub;
		ros::Publisher pos_pub;
		little_car();
		SVector3 get_velocity();
		SVector3 get_position();
		void set_velocity(SVector3 velocity);
		void update_();
		int move_forward();	//前进函数
	//	void set_yaw();//设置小车偏航	
		


};




#endif
