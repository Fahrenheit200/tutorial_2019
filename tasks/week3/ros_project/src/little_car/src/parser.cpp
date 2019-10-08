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
	this->_velocity.z = 0.0;
	return;
}
void little_car::add_noise()
{
	float sigma = _noise[_noise_level];
	double noise[3];
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<double> normal(0, sigma);
	for (int i = 0; i < 3; i++)
	{
		noise[i] = normal(gen);
	}
	odom_trans.header.stamp = ros::Time::now();
	_velocity.x += noise[0];
	_velocity.y += noise[1];
	_velocity.z = 0;
	return;
}
void little_car::set_noise_level(int level)
{
	_noise_level = level;
}
void little_car::update_position()
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
	odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(_yaw);
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
	joint_state.name[0] = "base_to_wheel_1";
	joint_state.position[0] = 0;
	joint_state.name[1] = "base_to_wheel_2";
	joint_state.position[1] = 0;
	joint_state.name[2] = "base_to_wheel_3";
	joint_state.position[2] = 0;
	joint_state.name[3] = "base_to_wheel_4";
	joint_state.position[3] = 0;

	add_noise();
	update_position();
	pos_pub.publish(_pub_position);
	joint_pub.publish(joint_state);
	broadcaster.sendTransform(odom_trans);
	return;
}
void little_car::set_yaw(float yaw)
{
	_yaw = yaw;
	return;
}
