//ROS头文件
#include <ros/ros.h>
//自定义消息类型my_msg产生的头文件
#include <pub_sub/MyMsg.h>
//产生随机数需要的头文件
#include <ctime>
#include <cstdlib>

int main(int argc, char **argv)
{
    //第三个参数为本节点名
    ros::init(argc, argv, "publisher");

    //实例化句柄，初始化node
    ros::NodeHandle n;

    //自定义my_msg类 msg
    pub_sub::MyMsg msg;
    
    //创建publisher
    ros::Publisher pub = n.advertise<pub_sub::MyMsg>("random_number", 100);
    //定义发布的频率
    ros::Rate loop_rate(1);
    //循环发布msg
    while (ros::ok()){
        //每隔2秒更新一次随机数
        srand(static_cast<unsigned int>(time(0)));
        msg.x = rand()%10000000;
	loop_rate.sleep();
        srand(static_cast<unsigned int>(time(0)));
        msg.y = rand()%10000000;
        //以1Hz的频率发布msg
        pub.publish(msg);
        //根据前面定义的频率, sleep 1s
        loop_rate.sleep();//根据前面的定义的loop_rate,设置1s的暂停
  }

  return 0;
}

