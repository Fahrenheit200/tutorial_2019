/******************************************************************
 * @file        subscriber.cpp
 * @brief       This file define a subscriber.
 * Details.
 *
 * @version     1.0.0
 * @author      林嘉鸿
 * @email       1073097404@qq.com
 *
 * -----------------------------------------------------------------
 *  Change History:
 *  <Date>      |<Version>      |<Author>       |<Description>
 *  ----------------------------------------------------------------
 *  2019/10/07  |1.0.0          |林嘉鸿         |Create file
 *
 *******************************************************************/

#include "ros/ros.h"
#include <pns/def_message.h>
#include <std_msgs/Int64.h>

//回调函数
void chatterCallback(const pns::def_message& n_msg)
{

	ROS_INFO("Receive:%d,%d,%d",n_msg.a,n_msg.b,n_msg.c);
}


int main(int argc,char **argv)
{
	ros::init(argc,argv,"subscriber");
	ros::NodeHandle n;
	//指定接受的topic，缓冲区的大小以及要输出的语句
	ros::Subscriber sub=n.subscribe("message",1000,chatterCallback);
	ros::spin();
	return 0;
}
