#include <ros/ros.h>
#include <pub_sub/message.h>
#include <std_msgs/Float32.h>

void msgCallback(const pub_sub::message::ConstPtr &msg)
{
	ROS_INFO("Lisener: x = %f, y = %f, state = %s", msg->x, msg->y, msg->state.c_str());
}
int main(int argc, char** argv){
	ros::init(argc,argv,"subscriber");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("msg_info", 1, msgCallback);		//创建subscriber
	ros::spin();		//反复调用当前可触发的回调函数，阻塞
	return 0;
}
