/**
 * 该例程将发布turtle/cmd_vel话题，消息类型geometry_msgs::Twist
 */
#include<ros/ros.h>
#include<data_pkg/data.h>//自己定义的msg
#define random(x) rand()%(x)

int main(int argc,char **argv)
{
	//节点初始化
	ros::init(argc,argv,"dataPub");

	//创建节点句柄
	ros::NodeHandle n;

	//创建一个Publisher,发布名为/turtlr1/cmd_vel的topic,消息类型为geometry_msgs::Twist，队列长度10
	ros::Publisher data_info_pub=n.advertise<data_pkg::data>("/data_info",10);

	//设置循环的频率
	ros::Rate loop_rate(10);

	srand((int)time(0));  // 产生随机种子

	int count=0;
	while(ros::ok())
	{
		//初始化geometry_msgs::Twist类型的消息
		data_pkg::data data_msg;
		data_msg.fig=random(999999999);

		//发布消息
		data_info_pub.publish(data_msg);
		ROS_INFO("Publish data info: fig:%d",data_msg.fig);
		//按照循环频率延时
		loop_rate.sleep();
	}
	return 0;
}
