#include "ros/ros.h"
#include "std_msgs/String.h"
#include "test_pkg/Num.h"

void chatterCallback(const test_pkg::Num n)
{
  ROS_INFO("I heard: [%d]", n.num);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
  ros::spin();
  return 0;
}
