#include "ros/ros.h"
#include "cli_ser_test/ser_msg.h"
#include<iostream>
#include<time.h>

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

int main(int argc,char **argv)
{
	ros::init(argc,argv,"cli_node");
	ros::NodeHandle n;
	ros::ServiceClient client=n.serviceClient<cli_ser_test::ser_msg>("ser_test");
    cli_ser_test::ser_msg srv;
    
    while(ros::ok())
    {
    	float randnum=getRandData(0,1);//产生0到1的浮点数 
    	srv.request.rdnum=randnum;
    	
    	if(client.call(srv))
    	{
    		ROS_INFO("%f",randnum);
    		if(srv.response.re)//如果Service返回布尔值为True 
    		    ROS_INFO("Yes");
    		else
    		    ROS_INFO("No");
		}
	}
	return 0;
}   
