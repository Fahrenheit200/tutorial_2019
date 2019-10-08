#include <ros/ros.h>
#include <service_demo/float_0to1.h>
#include <ctime>
#include <dynamic_reconfigure/server.h>
#include <service_demo/set_timeConfig.h>

float interval_time;

void dynamic_callback(service_demo::set_timeConfig &config){
    ROS_INFO("Reconfigure request: change interval_time to %d", config.interval_time);
    interval_time = config.interval_time;
}

int main(int argc, char** argv){
    ros::init(argc, argv, "client");
    ros::NodeHandle nh;
    ros::ServiceClient cli = nh.serviceClient<service_demo::float_0to1>("service_demo_info");

    srand((int)time(NULL));
    service_demo::float_0to1 srv;

    /* 配置动态参数服务器 */
    dynamic_reconfigure::Server<service_demo::set_timeConfig> dr_server;
    dynamic_reconfigure::Server<service_demo::set_timeConfig>::CallbackType callback;
    callback = boost::bind(&dynamic_callback, _1);
    dr_server.setCallback(callback);
    
    while(ros::ok())
    {
        /* 修改发送时间间隔 */
        ros::Rate loop_rate(1.0/interval_time);

        /* 产生随机浮点数 */
        srv.request.float_0to1 = rand()%100000*1.0/100000;

        /* 通过service通信 */
        if(cli.call(srv)){
            ROS_INFO("Client: send random float %f", srv.request.float_0to1);
            if(srv.response.is_smaller)
                ROS_INFO("Client: accept response Yes");
            else
                ROS_INFO("Client: accept response No");
        }else
            ROS_ERROR("Failed to call service Service_demo");
        
        ros::spinOnce();    //要加spinOnce等待rqt的信息
        loop_rate.sleep();
    }
    
    return 0;
}