/******************************************************************
 * @file        publisher.cpp
 * @brief       This file create a publisher to control the little car.
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
 *  ****************************************************************/

#include "ros/ros.h"
#include "std_msgs/Char.h"
#include <std_msgs/Int64.h>

int main(int argc,char **argv)
{
	//初始化，定义节点名称
	ros::init(argc,argv,"publisher");
	ros::NodeHandle n;
	//pub的消息类型是str_msgs::Char，将在名为car_ctrl的topic上发布
	//缓冲区的大小为1000
	std_msgs::Char msg;
	ros::Publisher pub=n.advertise<std_msgs::Char>("car_ctrl",100);
	//定义发送消息的频率(Hz)
	ros::Rate Loop_rate(1);
	int time=0;

	while(ros::ok())
	{
		//控制小车直行
		if(time%10==0||time%10==1)
			msg.data='f';
		//控制小车向左
		if(time%10==2||time%10==3||time%10==4)
			msg.data='l';
		//控制小车向后
		if(time%10==5||time%10==6)
			msg.data='b';
		//控制小车向右
		if(time%10==7||time%10==8||time%10==9)
			msg.data='r';
		//屏幕显示消息
		ROS_INFO("Send:%c",msg.data);
		//将消息通过topic发送出去
		pub.publish(msg);
		Loop_rate.sleep();
		time++;
	}
	return 0;
}
