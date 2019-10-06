#include <ros/ros.h>
#include "custom_srv_service/custom_srv.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "custom_srv_client");
    ros::NodeHandle n;

    ros::service::waitForService("compare");
    ros::ServiceClient client = n.serviceClient<custom_srv_service::custom_srv>("compare");
   
    custom_srv_service::custom_srv srv;
    srand(time(0));
    srv.request.m=0.5;
    for(int i=0; i<5; ++i)
    {
    	srv.request.a = rand()%1000/(double)1000;
    	if(client.call(srv))
    	{
    		ROS_INFO("random number: %f", srv.request.a);
		if(srv.response.b==1) ROS_INFO("YES");
		else ROS_INFO("NO");
	}
    
    }
    return 0;    

}
