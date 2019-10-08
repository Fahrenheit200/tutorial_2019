#include "ros/ros.h"
#include "srv_cli/LessThan.h"

bool lessThan(srv_cli::LessThan::Request& req,srv_cli::LessThan::Response &res)
{
    if(req.random_num<0.5) res.less_than=true;
    else res.less_than=false;
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "server");
    ros::NodeHandle n;

    //服务名字为：is_less_than，若收到该请求则调用函数lessThan()
    ros::ServiceServer service = n.advertiseService("is_less_than", lessThan);

    ROS_INFO("Ready to compare.");
    ros::spin();

    return 0;
}
