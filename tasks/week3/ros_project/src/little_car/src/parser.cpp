#include "parser.h"
little_car::little_car()
{
}
SVector3 little_car::get_velocity()
{
	return this->_velocity;
}

SVector3 little_car::get_position()
{
	return this->_position;
}
void little_car::set_velocity(SVector3 velocity)
{
	this->_velocity.x = velocity.x;
	this->_velocity.y = velocity.y;
	this->_velocity.z = velocity.z;
	return;
}
void little_car::add_noise()
{
	float sigma = _velocity.x + _velocity.y + _velocity.z;
	double noise[3];
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<double> normal(0,sigma);
	for(int i=0;i<3;i++)
	{		
		noise[i] = normal(gen);
	}
	odom_trans.header.stamp = ros::Time::now();
	/*
	_position.x += noise[0];					//更新小车的位置信息
	_position.y += noise[1];
	_position.z += noise[2];
    odom_trans.transform.translation.x = _position.x;	//小车 x 方向的移动 每次加上velocity.x的距离
    odom_trans.transform.translation.y = _position.y;
    odom_trans.transform.translation.z = _position.z;
	*/
	_velocity.x += noise[0];
	_velocity.y += noise[1];
	_velocity.z += noise[2];
	return;

}
void little_car::update_position()
{
	odom_trans.header.frame_id = "odom";
	odom_trans.child_frame_id = "base_link";
    odom_trans.header.stamp = ros::Time::now();
	_position.x += _velocity.x;	
	_position.y += _velocity.y;	
	_position.z += _velocity.z;	
    odom_trans.transform.translation.x = _position.x;//小车 x 方向的移动 每次加上velocity.x的距离
    odom_trans.transform.translation.y = _position.y;
    odom_trans.transform.translation.z = _position.z;
	odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(0.0);
	_pub_position.x = _position.x;
	_pub_position.y = _position.y;
	_pub_position.z = _position.z;
	return;
}
void little_car::update_()
{
	
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
	
	add_noise(); //添加噪声，请勿修改此函数
	update_position();//更新位置信息
	pos_pub.publish(_pub_position);//发布位置信息到 "car_position" 信息格式为 geometry::msgs::Point
	joint_pub.publish(joint_state);
	broadcaster.sendTransform(odom_trans);
	return;
}
