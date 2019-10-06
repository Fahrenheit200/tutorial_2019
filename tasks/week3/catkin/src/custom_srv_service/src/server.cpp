#include <ros/ros.h>
#include <custom_srv_service/custom_srv.h>

bool compare(custom_srv_service::custom_srv::Request &req, custom_srv_service::custom_srv::Response &res)
{
    if(req.a>req.m) res.b=false;
    else if(req.a<req.m) res.b=true;
    ROS_INFO("request:%f",req.a);
    ROS_INFO("response:[%d]",res.b);
    return true;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "custom_srv_server");
    ros::NodeHandle n;
    ros::ServiceServer service = n.advertiseService("compare",compare);
    ROS_INFO("Ready to compare");
    ros::spin();
    return 0;

}
