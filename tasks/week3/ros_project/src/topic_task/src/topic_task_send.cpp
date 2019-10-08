#include "ros/ros.h"
#include "topic_task/random_msg.h"
#include "topic_task/dynamicConfig.h"
#include "dynamic_reconfigure/server.h"
int b = 0;
int a = 10;
int log_level = 0;
void dynamic_callback(topic_task::dynamicConfig &config)
{
    ROS_INFO("Reconfigure Request: %d %d", config.randomMin, config.randomMax);
    b = config.randomMax;
    a = config.randomMin;
    log_level = config.log_level;
    return;
}
int main(int argc, char *argv[])
{
    srand((unsigned)time(0));
    ros::init(argc, argv, "topic_task_send_node");
    ros::NodeHandle nh;

    dynamic_reconfigure::Server<topic_task::dynamicConfig> server;
    dynamic_reconfigure::Server<topic_task::dynamicConfig>::CallbackType callback;
    callback = boost::bind(&dynamic_callback, _1);
    server.setCallback(callback);

    ros::Publisher pub = nh.advertise<topic_task::random_msg>("chatter", 1000);
    ros::Rate loop_rate(1);
    topic_task::random_msg msg;
    msg.name = "ADAM_GALLAS";

    while (ros::ok())
    {
        if (b > a)
        {
            msg.num = (rand() % (b - a)) + a;
            ROS_INFO("send MSG: randomNum=%d range=%d:%d", msg.num, a, b);
        }
        else
        {
            msg.num=0;
            ROS_WARN("randomMax is smaller than randomMin, return 0");
        }
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}