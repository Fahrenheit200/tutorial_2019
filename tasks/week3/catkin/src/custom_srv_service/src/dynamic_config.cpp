#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include "custom_srv_service/custom_srv.h"
#include "custom_srv_service/dynamic_srvConfig.h"

void callback(custom_srv_service::dynamic_srvConfig &Config, uint32_t level,custom_srv_service::custom_srv::Request &req)
{
    req.m = Config.n;
}
int main(int argc, char** argv)
{
    ros::init(argc, argv, "dynamic_config");
    dynamic_reconfigure::Server<custom_srv_service::dynamic_srvConfig> server;
    dynamic_reconfigure::Server<custom_srv_service::dynamic_srvConfig>::CallbackType f;
    f = boost::bind(&callback, _1, _2);
    server.setCallback(f);
    ros::spin();
    return 0;
}