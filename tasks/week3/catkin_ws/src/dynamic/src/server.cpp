/******************************************************************
 * @file        sever.cpp
 * @brief       This file define a dynamic parameter server.
 * Details.
 *
 * @version     1.0.0
 * @author      林嘉鸿
 * @email       1073097404@qq.com
 *
 * -----------------------------------------------------------------
 *  Change History:
 *  <Date>      |<Version>      |<Author>       |<Description>
 *  ----------------------------------------------------------------
 *  2019/10/07  |1.0.0          |林嘉鸿         |Create file
 *
 *  ****************************************************************/

#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <dynamic/dyConfig.h>

//用于设置服务器响应的回调函数
void callback(dynamic::dyConfig &config, uint32_t level){
    ROS_INFO("Receive:%f",config.double_param);
    if(config.double_param<0.5)
		ROS_INFO("Yes");
	else
		ROS_INFO("No");
}

int main(int argc, char **argv) 
{
    //初始化，声明节点dynamic
    ros::init(argc, argv, "dynamic");
    //创建动态参数实例server，使用dy.cfg配置
    dynamic_reconfigure::Server<dynamic::dyConfig> server;
    dynamic_reconfigure::Server<dynamic::dyConfig>::CallbackType f;
    //服务器被请求时，跳到回调函数
    f = boost::bind(&callback, _1, _2);
    server.setCallback(f);
    ROS_INFO("Waiting for a request");
    ros::spin();
    return 0;
}
