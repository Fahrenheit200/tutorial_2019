#include <ros/ros.h>
#include <topic_demo/rand_int.h>
#include <ctime>
#include <dynamic_reconfigure/server.h>
#include <topic_demo/set_maxConfig.h>

int random_int_max;

void dynamic_callback(topic_demo::set_maxConfig &config){
    ROS_INFO("Reconfigure request: change random_int_max to %d", config.random_int_max);
    random_int_max = config.random_int_max;
}

int main(int argc, char** argv){
    ros::init(argc, argv, "talker");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<topic_demo::rand_int>("topic_demo_info", 1);
    topic_demo::rand_int msg;
    srand((int)time(NULL));
    
    /* 配置动态参数服务器 */
    dynamic_reconfigure::Server<topic_demo::set_maxConfig> dr_server;
    dynamic_reconfigure::Server<topic_demo::set_maxConfig>::CallbackType callback;
    callback = boost::bind(&dynamic_callback, _1);
    dr_server.setCallback(callback);

    /* 设置产生并publish随机数的频率为1Hz */
    ros::Rate loop_rate(1.0);
    
    while (ros::ok()){
        /* 产生并发送在0-random_int_max范围之间的正整数 */
        msg.rand_int = rand() % (random_int_max + 1);
        pub.publish(msg);
        ros::spinOnce();    //要加spinOnce等待rqt的信息
        loop_rate.sleep();
    }
    
    return 0;
}

