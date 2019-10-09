#include "ros/ros.h"
#include "service/judge.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "service_client");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<service::judge>("service1");
    service::judge srv;
    srand(time(NULL));
    ros::Rate loop_rate(0.5);
    while(ros::ok()){
    srv.request.num = rand()/(float)(RAND_MAX);
    if(client.call(srv))
    {
        ROS_INFO("the Random Number is %f", srv.request.num);
        if(srv.response.result == 1)    ROS_INFO("Yes");
        else                            ROS_INFO("No");
    }
    else{
    ROS_INFO("service failed!");
    return 1;
    }
    loop_rate.sleep();
    }
    return 0;
}
