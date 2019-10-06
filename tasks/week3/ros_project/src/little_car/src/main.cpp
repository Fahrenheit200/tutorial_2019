#include "parser.h"
#include <urdf/model.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <keyrequest/ctrl.h>
#include <ros/ros.h>
#include <string>
#include <random>
#include <iomanip>
using namespace std;
/*mycode-----------------------------------------------------------------*/
int MOVE_MODE = 0;
double RADIUS = 1.5;
SVector3 velocity = {0, 0.004, 0};
void sMovement();
void ctrlCallback(const keyrequest::ctrl::ConstPtr &msg);
/*mycode-----------------------------------------------------------------*/
int main(int argc, char **argv)
{
	ros::init(argc, argv, "state_publisher");
	ros::NodeHandle n;
	little_car car;
	car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position", 1);
	ROS_INFO("Started.");

	/*mycode-----------------------------------------------------------------*/
	ros::Subscriber sub = n.subscribe("ctrlcmd", 1, ctrlCallback);
	ros::Rate ctrl_loop_rate(60);
	ros::Rate moveS_loop_rate(500);
	/*mycode-----------------------------------------------------------------*/

	car.set_noise_level(0);
	float yaw = 0.0;
	while (ros::ok())
	{
		/*mycode-----------------------------------------------------------------*/
		sMovement();
		ros::spinOnce();
		/*mycode-----------------------------------------------------------------*/

		car.set_velocity(velocity);
		car.update_();

		/*mycode-----------------------------------------------------------------*/
		if (MOVE_MODE == 1)
			moveS_loop_rate.sleep();
		else
			ctrl_loop_rate.sleep();
		/*mycode-----------------------------------------------------------------*/
	}
	return 0;
}
/*mycode-----------------------------------------------------------------*/
void sMovement()
{
	static double s = 0.001;
	static double dsign = 1;
	static double tsign = 1;
	static double radius = RADIUS;
	static double dx = 0.001;
	static int cnt = 0;
	if (MOVE_MODE == 0)
	{
		s = 0.001;
		dsign = 1;
		tsign = 1;
		radius = RADIUS;
		dx = 0.001;
		cnt = 0;
		return;
	}
	if (abs(s - radius) < 1e-6 || abs(s - 0) < 1e-6)
	{
		cnt++;
		if (cnt % 4 == 1)
		{
			s = dx;
			dsign = -1;
			tsign = 1;
		}
		if (cnt % 4 == 2)
		{
			s = radius - dx;
			dsign = 1;
			tsign = -1;
		}
		if (cnt % 4 == 3)
		{
			s = radius - dx;
			dsign = -1;
			tsign = -1;
		}
		if (cnt % 4 == 0)
		{
			s = dx;
			dsign = 1;
			tsign = 1;
		}
	}
	velocity.x = tsign * dx;
	velocity.y = dsign * 0.5 * (radius - 2 * s) / sqrt(radius * s - s * s) * dx;
	s = s + velocity.x;
	return;
}
void ctrlCallback(const keyrequest::ctrl::ConstPtr &msg)
{
	double speed = msg->speed;
	if (msg->cmd == int('w'))
	{
		MOVE_MODE = 0;
		velocity.x = 0.0;
		velocity.y = speed;
		velocity.z = 0.0;
	}
	else if (msg->cmd == int('s'))
	{
		MOVE_MODE = 0;
		velocity.x = 0.0;
		velocity.y = -speed;
		velocity.z = 0.0;
	}
	else if (msg->cmd == int('a'))
	{
		MOVE_MODE = 0;
		velocity.x = -speed;
		velocity.y = 0.0;
		velocity.z = 0.0;
	}
	else if (msg->cmd == int('d'))
	{
		MOVE_MODE = 0;
		velocity.x = speed;
		velocity.y = 0.0;
		velocity.z = 0.0;
	}
	else if (msg->cmd == int('1'))
	{
		MOVE_MODE = 1;
		RADIUS = msg->r;
		velocity.x = 0;
		velocity.y = 0;
		velocity.z = 0;
	}
	else
	{
		MOVE_MODE = 0;
		velocity.x = 0.0;
		velocity.y = 0.0;
		velocity.z = 0.0;
	}
	return;
}
/*mycode-----------------------------------------------------------------*/