#include <ros/ros.h>
#include <service_demo/float_0to1.h>

bool handle_function(service_demo::float_0to1::Request &req, service_demo::float_0to1::Response &res){
    /* 判断接受到的浮点数是否小于0.5，是则响应为true，否则响应为false */
    if(req.float_0to1 >= 0.5 && req.float_0to1 <= 1)
        res.is_smaller = false;
    else if(req.float_0to1 < 0.5 && req.float_0to1 > 0)
        res.is_smaller = true;
    else 
        ROS_INFO("error in float_0to1");
    return true;
}

int main(int argc, char** argv){
    ros::init(argc, argv, "server");
    ros::NodeHandle nh;
    ros::ServiceServer ser = nh.advertiseService("service_demo_info", handle_function);
    ros::spin();
    return 0;
}