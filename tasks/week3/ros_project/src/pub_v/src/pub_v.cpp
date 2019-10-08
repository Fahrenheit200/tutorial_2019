#include <ros/ros.h>
#include <geometry_msgs/Point.h>

int main(int argc, char **argv)
{
    //第三个参数为本节点名
    ros::init(argc, argv, "pub_v");

    //实例化句柄，初始化node
    ros::NodeHandle n;

    geometry_msgs::Point v;
    //创建publisher
    ros::Publisher pub = n.advertise<geometry_msgs::Point>("v_little_car", 100);
    //定义发布的频率
    ros::Rate loop_rate(20);
    //循环发布v
    while (ros::ok()){
	v.x=0.004;
	v.y=0.004;
	v.z=0.000;
        //以20Hz的频率发布v
        pub.publish(v);
        //根据前面定义的频率, sleep 
        loop_rate.sleep();
    }

  return 0;
}

