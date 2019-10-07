#include "ros/ros.h"
#include "dynamic_test/my_cfgConfig.h"
#include<iostream>
#include<dynamic_reconfigure/server.h>

using namespace std;

/*
*产生min到max的随机浮点数
*/ 
float getRandData(int min,int max)
{
	srand((int)time(0));//用时间做种子 
	float m1=(float)(rand()%101)/101;
	min++;
	float m2=(float)(rand()%(max-min+1)+min);
	m2--;
	return m1+m2;
} 

void paramCallback(dynamic_test::my_cfgConfig &config)
{
	float randnum=getRandData(config.min,config.max);//产生随机数 
	ROS_INFO("Random Num from %d to %d =%f",config.min,config.max,randnum);
	if(randnum<0.5)
	    ROS_INFO("Yes");
	else
	    ROS_INFO("No");
}

int main(int argc,char **argv)
{
	ros::init(argc,argv,"dynamic_node");
	
	dynamic_reconfigure::Server<dynamic_test::my_cfgConfig> server;
    dynamic_reconfigure::Server<dynamic_test::my_cfgConfig>::CallbackType f;
	
	f=boost::bind(&paramCallback,_1);
	server.setCallback(f);
	
	ROS_INFO("Spinning node");
	ros::spin();
	return 0;
}
