#include <ros/ros.h>
#include<iostream>
#include "my_service/my.h"
#include < dynamic_reconfigure/server.h>
#include <cstdlib>
using namespace std;


int main(int argc, char** argv)

{

    // 初始化ROS节点

	ros::init(argc, argv, "my_client");



    // 创建节点句柄

	ros::NodeHandle node;



    // 发现/spawn服务后，创建一个服务客户端，连接名为/spawn的service

	ros::service::waitForService("/show_my");

	ros::ServiceClient my_client = node.serviceClient<my_service::my>("/show_my");



    // 初始化my的请求数据

	my_service::my srv;

	
srv.request.name = "WangGuangshuo";
	
	




    // 请求服务调用

	ROS_INFO("Call service to show my[name:%s] and the num", 

			 srv.request.name.c_str());



	my_client.call(srv);



	// 显示服务调用结果
	
	ROS_INFO("Show my result : %s", srv.response.result.c_str());

	for(int i=0;i<100000000;i++){}


	return 0;

}
