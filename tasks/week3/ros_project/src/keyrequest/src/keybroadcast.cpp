#include "ros/ros.h"
#include "keyrequest/ctrlreq.h"
#include "keyrequest/ctrl.h"
#include "keyrequest/dynamicConfig.h"
#include "dynamic_reconfigure/server.h"
keyrequest::ctrl msg;

void dynamic_callback(keyrequest::dynamicConfig &config)
{
    msg.speed = config.speed;
    msg.r = config.r;
    return;
}

bool broadcast(keyrequest::ctrlreq::Request &req,
               keyrequest::ctrlreq::Response &res);
int main(int argc, char *argv[])
{
    ros::init(argc, argv, "keybroadcast_node");
    ros::NodeHandle nh;

    dynamic_reconfigure::Server<keyrequest::dynamicConfig> server;
    dynamic_reconfigure::Server<keyrequest::dynamicConfig>::CallbackType callback;
    callback = boost::bind(&dynamic_callback, _1);
    server.setCallback(callback);

    ros::ServiceServer myservice;
    ros::Publisher pub = nh.advertise<keyrequest::ctrl>("ctrlcmd", 1);
    ros::Rate loop_rate(50);
    myservice = nh.advertiseService("ctrlrequest", broadcast);
    while (ros::ok())
    {
        //ROS_INFO("send movement [%s]", msg.move.c_str());
        pub.publish(msg);
        loop_rate.sleep();
        ros::spinOnce();
    }
    return 0;
}
bool broadcast(keyrequest::ctrlreq::Request &req,
               keyrequest::ctrlreq::Response &res)
{
    //ROS_INFO("Recieve Cmd = [%c] [%s]", char(req.cmd), req.move.c_str());
    msg.cmd = req.cmd;
    msg.move = req.move;
    res.feedback = "roger that";
    return 1;
}