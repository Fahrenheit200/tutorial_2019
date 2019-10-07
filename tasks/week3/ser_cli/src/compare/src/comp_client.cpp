#include "ros/ros.h"
#include "compare/pro.h"
#include <cstdlib>
#include<ctime>

int main(int argc,char **argv)
{
	ros::init(argc,argv,"comp_client");
	ros::NodeHandle n;
	ros::ServiceClient client=n.serviceClient<compare::pro>("compar");
	compare::pro srv;
	ros::Rate loop_rate(1);
	while(ros::ok()){
	srand(time(NULL));
	srv.request.a=(rand()%1000/1000.000);
	std::cout<<srv.request.a<<std::endl;
	if(client.call(srv))
	{
		if(srv.response.b==1)
		std::cout<<"YES"<<std::endl;
		else std::cout<<"No"<<std::endl;
	}
	else 
	{
		ROS_ERROR("failed");
		return 1;
	}
	ros::spinOnce();
	loop_rate.sleep();
	}
	return 0;
}
