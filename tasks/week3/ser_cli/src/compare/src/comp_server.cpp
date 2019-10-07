#include "ros/ros.h"
#include "compare/pro.h"

bool com(compare::pro::Request &req,compare::pro::Response &res)
{
	std::cout<<req.a<<std::endl;
	res.b=bool(req.a>0.5);
	return true;
}

int main(int argc,char **argv)
{
	ros::init(argc,argv,"comp_server");
	ros::NodeHandle n;
	ros::ServiceServer service=n.advertiseService("compar",com);
//	std::cout<<"The number is ";
	ros::spin();
	return 0;
}
