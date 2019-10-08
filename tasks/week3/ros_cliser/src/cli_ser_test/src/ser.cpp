#include "ros/ros.h"
#include "cli_ser_test/ser_msg.h"
#include<iostream>
#include<string>

using namespace std;

bool callback(cli_ser_test::ser_msgRequest &request,cli_ser_test::ser_msgResponse &response)
{
	if(request.rdnum<0.5)
	    response.re=true;
	else
	    response.re=false;
	return true;
}

int main(int argc,char **argv)
{
	ros::init(argc,argv,"ser_node");
	ros::NodeHandle n;
	
	ros::ServiceServer service=n.advertiseService("ser_test",callback);
	ros::spin();
	
	return 0;
}
