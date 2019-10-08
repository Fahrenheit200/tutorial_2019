#include "ros/ros.h"
#include "std_msgs/String.h"
#include "test_pkg/Num.h"
#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<test_pkg::Num>("chatter", 1000);
  ros::Rate loop_rate(10);
  int count = 0;
  while (ros::ok())
  {
    test_pkg::Num n;
    n.num = count;
    count++;
    chatter_pub.publish(n);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
