#include "service_task/random_srv.h"
#include "ros/ros.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "service_task_client_node");

    ros::NodeHandle nh;
    ros::ServiceClient myclient =
        nh.serviceClient<service_task::random_srv>("callme");
    service_task::random_srv srv;
    srv.request.note = "give me a random number!";
    if (myclient.call(srv))
    {
        ROS_INFO("Feedback from the server %f", srv.response.num);
        if (srv.response.num >= 0.5)
            ROS_INFO("Bigger than 0.5");
        else
            ROS_INFO("Smaller than 0.5");
    }
    else
    {
        ROS_INFO("Failed to call the service greetings");
    }
    return 0;
}