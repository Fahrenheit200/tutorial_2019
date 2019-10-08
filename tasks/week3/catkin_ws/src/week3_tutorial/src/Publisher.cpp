#include "ros/ros.h"
#include "week3_tutorial/myName.h"
#include <sstream>

int main(int argc, char **argv)
{
		ros::init(argc, argv, "Publisher");   //初始化节点并设置名称
		ros::NodeHandle n;
		ros::Publisher chatter_pub = n.advertise<week3_tutorial::myName>("message", 1000);
		ros::Rate loop_rate(5);   //发送数据的频率设置为5Hz
		while(ros::ok())   
		{
				week3_tutorial::myName msg;   //创建一个消息变量
				std::stringstream ss;
				ss<< "Hello, FaxingLei";
				msg.myName = ss.str();
				ROS_INFO("%s", msg.myName.c_str());
				chatter_pub.publish(msg);   //持续发布消息
				ros::spinOnce();
  				loop_rate.sleep();  //以5Hz的频率挂起
		}
		return 0;
}
