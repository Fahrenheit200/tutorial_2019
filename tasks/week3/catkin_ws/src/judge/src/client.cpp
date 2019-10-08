/******************************************************************
 * @file        client.cpp
 * @brief       This file define a client, which can create and sent a random float to the server.
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
#include <stdlib.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "client");
	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<judge::def_message>("jud");
	judge::def_message srv;
	ros::Rate loop_rate(1.0);
	while(ros::ok())
	{
		float num;
		//生产0-1的随机数
		num=rand()%(1000)/(float)(1000);
		ROS_INFO("Send:%f",num);
		//写入数据
		srv.request.ask=num;
		//判断从服务器接收到的相应
		if(client.call(srv))
		{
			if(srv.response.result==1)
				ROS_INFO("Yes");
			else
				ROS_INFO("No");
		}
		loop_rate.sleep();
	}

  return 0;
}
