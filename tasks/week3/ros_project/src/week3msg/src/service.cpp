#include "ros/ros.h"
#include "week3msg/week3srv.h"

bool judge(week3msg::week3srv::Request  &req,
        week3msg::week3srv::Response &res)
{
	if(req.req>0.5)
		res.repb=true;
	else
		res.repb=false;
	res.rep=req.req;     


	return true;




}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "servicer");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("service", judge);
  ROS_INFO("Ready to judge number.");
  ros::spin();

  return 0;
}
