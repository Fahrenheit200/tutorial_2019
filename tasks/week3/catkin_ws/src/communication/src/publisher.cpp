#include <ros/ros.h>
#include <communication/message.h>
#include <stdlib.h>
#include <time.h>
#define random(x) (rand()%x)


int main(int argc, char** argv){
	ros::init(argc, argv, "publisher");	//解析参数，命名节点
	ros::NodeHandle nh;			//创建句柄，实例化node
	communication::message msg;			//创建msg消息
	ros::Publisher pub = nh.advertise<communication::message>("msg_info",1);	//创建publisher
	ros::Rate loop_rate(1.0);	//定义循环发布的频率
	while(ros::ok()){
		msg.x = random(100);
		msg.y = random(100);
		msg.state = "working";
		ROS_INFO("Publisher: x = %f, y = %f", msg.x, msg.y);	//输出当前msg
		pub.publish(msg);		//发布消息
		loop_rate.sleep();		//根据定义的频率，sleep
	}
	return 0;
	
}
