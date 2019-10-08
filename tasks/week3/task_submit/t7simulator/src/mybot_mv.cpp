#include "mybot_mv.h"
#include "geometry_msgs/Point.h"

MybotMv::MybotMv(float x, float y, float z)
{
	pos_pub = nh.advertise<geometry_msgs::Point>("car_postion", 1);
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_velocity.x = _velocity.y = _velocity.z = 0;
}
void MybotMv::update_position()
{
	odom_trans.header.frame_id = "odom";
	odom_trans.child_frame_id = "base_link";
    	odom_trans.header.stamp = ros::Time::now();
	_position.x += _velocity.x;
	_position.y += _velocity.y;
	_position.z += _velocity.z;
    	odom_trans.transform.translation.x = _position.x;
    	odom_trans.transform.translation.y = _position.y;
    	odom_trans.transform.translation.z = _position.z;
	odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(0);//小车方向的改变
	_pub_position.x = _position.x;
	_pub_position.y = _position.y;
	_pub_position.z = _position.z;
	return;
}
void MybotMv::update_()
{
/*
	joint_state.header.stamp = ros::Time::now();
	joint_state.name.resize(4);
	joint_state.position.resize(4);
	joint_state.name[0] ="base_to_wheel_1";
	joint_state.position[0] = 0;
    	joint_state.name[1] ="base_to_wheel_2";
    	joint_state.position[1] = 0;
    	joint_state.name[2] ="base_to_wheel_3";
    	joint_state.position[2] = 0;
	joint_state.name[3] ="base_to_wheel_4";
	joint_state.position[3] = 0;
*/
	update_position();
	pos_pub.publish(_pub_position);
//	joint_pub.publish(joint_state);
	broadcaster.sendTransform(odom_trans);
	return;
}
