/******************************************************************
 * @file        publisher.cpp
 * @brief       This file define a publisher.
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

int main(int argc,char **argv)
{
	//初始化，定义节点名称
	ros::init(argc,argv,"publisher");
	ros::NodeHandle n;
	//chatter_pub的消息类型是str_msgs::String，将在名为message的topic上发布
	//缓冲区的大小为1000
	pns::def_message n_msg;
	ros::Publisher pub=n.advertise<pns::def_message>("message",1000);
	//定义发送消息的频率(Hz)
	ros::Rate Loop_rate(1);
	while(ros::ok())
	{
		n_msg.a=rand();
		n_msg.b=rand();
		n_msg.c=rand();
		//屏幕显示消息
		ROS_INFO("Send:%d,%d,%d",n_msg.a,n_msg.b,n_msg.c);
		//将消息通过topic发送出去
		pub.publish(n_msg);
		Loop_rate.sleep();
	}
	return 0;
}
