#include <ros/ros.h>
#include <topic_demo/rand_int.h>

void infoCallback(const topic_demo::rand_int::ConstPtr &msg){
    /* 显示接受到的正整数 */
    ROS_INFO("Listener: get a num %d", msg->rand_int);
}


int main(int argc, char** argv){
    ros::init(argc, argv, "listener");
    ros::NodeHandle nh;
    ros::Subscriber pub = nh.subscribe("topic_demo_info", 1, infoCallback);
    ros::spin();
    
    return 0;
}
