#include "ros/ros.h"
#include "service/judge.h"
#include <dynamic_reconfigure/server.h>
#include "service/set_judgeConfig.h"
int count = 0;
int range = 0.5;
void callback(service::set_judgeConfig &config, uint32_t level){
    range = config.judgeNum;
    ROS_INFO("Reconfigure Request: %f", config.judgeNum);
}
bool test(service::judge::Request& req, service::judge::Response& res)
{
    count++;
    if(req.num < range)   res.result = 1;
    else                res.result = 0;
    ROS_INFO("Get the random number. %d", count);
    return true;
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "service_server");
    ros::NodeHandle n;
    ros::ServiceServer service = n.advertiseService("service1", test);
    dynamic_reconfigure::Server<service::set_judgeConfig > server;
    dynamic_reconfigure::Server<service::set_judgeConfig >::CallbackType f;
    f = boost::bind(&callback, _1, _2);
    server.setCallback(f);
    ROS_INFO("Service Ready");
    ros::spin();
    return 0;
}

