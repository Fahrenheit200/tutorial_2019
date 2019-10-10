#include <ros/ros.h>
#include<iostream>
#include "my_service/my.h"
#include <cstdlib>
using namespace std;


// service回调函数，输入参数req，输出参数res

bool myCallback(my_service::my::Request  &req,

         			my_service::my::Response &res)

{

    // 显示请求数据

    ROS_INFO("my: name:%s  num:%lf  ", req.name.c_str(), req.num);
    

	// 设置反馈数据
	if(req.num<0.5) res.result = "Yes";
	else res.result = "No";



    return true;

}



int main(int argc, char **argv)

{

    // ROS节点初始化

    ros::init(argc, argv, "my_server");



    // 创建节点句柄

    ros::NodeHandle n;



    // 创建一个名为/show_person的server，注册回调函数personCallback

    ros::ServiceServer my_service = n.advertiseService("/show_my", myCallback);



    // 循环等待回调函数

    ROS_INFO("Ready to show my informtion.");

    ros::spin();



    return 0;

}




