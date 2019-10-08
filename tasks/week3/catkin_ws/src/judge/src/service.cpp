/******************************************************************
 * @file        sevice.cpp
 * @brief       This file define a server, which can judge the number sent by client and return "Yes" or "No".
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
#include "judge/def_message.h"
#include <std_msgs/Float64.h>

/**
 * 定义回调函数
**/
bool j(judge::def_message::Request &req,judge::def_message::Response &res)
{
	ROS_INFO("Receive:%f",req.ask);
	if(req.ask<0.5)
	{
		ROS_INFO("Answer:1");
		//写入数据
  		res.result=1;
	}
	else
	{
		ROS_INFO("Answer:0");
		//写入数据
		res.result=0;
	}
	return true;
}

int main(int argc, char **argv)
{
	//初始化，定义节点名称
	ros::init(argc, argv, "service");
	ros::NodeHandle n;
	//响应
	ros::ServiceServer service=n.advertiseService("jud",j);
	ROS_INFO("Ready to judge.");
	ros::spin();
	return 0;
}
