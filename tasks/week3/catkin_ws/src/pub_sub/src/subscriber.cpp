//ROS头文件
#include <ros/ros.h>
//包含自定义msg产生的头文件
#include <pub_sub/MyMsg.h>

void randomNumberCallback(const pub_sub::MyMsg::ConstPtr& msg)
{  
    ROS_INFO("subscriber: random number x= %d, y= %d",msg->x,msg->y);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "subscriber");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("random_number", 100, randomNumberCallback);
  //ros::spin()用于调用所有可触发的回调函数,将进入循环
  ros::spin(); 
  return 0;
}
