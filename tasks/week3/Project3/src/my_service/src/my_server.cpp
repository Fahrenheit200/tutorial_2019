#include <ros/ros.h>
#include<iostream>
#include "my_service/my.h"
#include <cstdlib>
#include <dynamic_reconfigure/server.h>
#include <my_service/TutorialsConfig.h>
using namespace std;
	double getRandData(int min,int max)
	{
     	double m1=(double)(rand()%101)/101;                        // 计算 0，1之间的随机小数,得到的值域近似为(0,1)
		min++;                                                                             //将 区间变为(min+1,max),
      	double m2=(double)((rand()%(max-min+1))+min);    //计算 min+1,max 之间的随机整数，得到的值域为[min+1,max]
     	m2=m2-1;                                                                        //令值域为[min,max-1]
     	return m1+m2;                                                                //返回值域为(min,max),为所求随机浮点数
	}


// service回调函数，输入参数req，输出参数res

bool myCallback(dynamic_reconfigure::Tutorials::Request  &req,

         			dynamic_reconfigure::Tutorials::Response &res)

{

    // 显示请求数据
    req.num  = getRandData(req.min,req.max);
    ROS_INFO("min:%d max:%d num:%lf  ", req.min,req.max,req.name.c_str(), req.num);
    

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
    dynamic_reconfigure::Server<my_service::TutorialsConfig> server;
    dynamic_reconfigure::Server<my_service::TutorialsConfig>::CallbackType f;

    f = boost::bind(&myCallback, _1, _2);
    server.setCallback(f);


    // 循环等待回调函数

    ROS_INFO("Ready to show my informtion.");

    ros::spin();



    return 0;

}




