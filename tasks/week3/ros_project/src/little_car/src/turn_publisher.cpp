#include "ros/ros.h"
#include "little_car/myfloat32.h"

int main(int argc, char **argv)
{
		 ros::init(argc, argv, "Publisher");
		 ros::NodeHandle n;
	     ros::Publisher chatter_pub = n.advertise<little_car::myfloat32>("v", 100);
		 ros::Rate loop_rate(20);   //发送数据的频率设置为20Hz
		 while(ros::ok())
		 {
				 little_car::myfloat32 msg;
				 float x = 0;
				 if(x < 0.007)
						 x += 0.0002;
				 else
						 x = 0.0069;
				 msg.x = x;
				 chatter_pub.publish(msg);   //持续发布消息
				 ros::spinOnce();
				 loop_rate.sleep();  //以20Hz的频率挂起
		 }
		 return 0;
}
