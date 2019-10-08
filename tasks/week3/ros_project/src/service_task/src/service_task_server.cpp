#include "service_task/random_srv.h"
#include "ros/ros.h"
#include "service_task/dynamicConfig.h"
#include "dynamic_reconfigure/server.h"
#include <random>
using namespace std;

double threshold = 0.5;
string randomType = "uniform";
double theta = 0.2;

void dynamic_callback(service_task::dynamicConfig &config);
bool randSend(service_task::random_srv::Request &req,
              service_task::random_srv::Response &res);

int main(int argc, char *argv[])
{
    srand((unsigned)time(0));
    ros::init(argc, argv, "service_task_send_node");
    ros::NodeHandle nh;

    dynamic_reconfigure::Server<service_task::dynamicConfig> server;
    dynamic_reconfigure::Server<service_task::dynamicConfig>::CallbackType callback;
    callback = boost::bind(&dynamic_callback, _1);
    server.setCallback(callback);

    ros::ServiceServer ser = nh.advertiseService("callme", randSend);
    ROS_INFO("Ready to send random number");
    ros::spin();
    return 0;
}
bool randSend(service_task::random_srv::Request &req,
              service_task::random_srv::Response &res)
{
    uniform_real_distribution<double> u;
    normal_distribution<double> n(0.5, theta);
    default_random_engine e((unsigned)time(NULL));

    if (randomType == "gaussian")
    {
        res.num = n(e);
        if (res.num >= 1)
            res.num = 1;
        if (res.num <= 0)
            res.num = 0;
    }
    else
        res.num = u(e);
    ROS_INFO("request:[%s]", req.note.c_str());
    ROS_INFO("sending back randNum: [%f]", res.num);
    return 1;
}
void dynamic_callback(service_task::dynamicConfig &config)
{
    ROS_INFO("Reconfigure Request: %f %s %f", config.threshold, config.randomType.c_str(), config.theta);
    threshold = config.threshold;
    randomType = config.randomType;
    theta = config.theta;
    return;
}