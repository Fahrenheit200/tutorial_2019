#include "ros/ros.h"
#include "srv_cli/LessThan.h"
//产生随机数需要的头文件
#include <ctime>
#include <cstdlib>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "client");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<srv_cli::LessThan>("is_less_than");
    srv_cli::LessThan srv;

    ros::Rate loop_rate(0.5);
    while (ros::ok()){
	//产生随机数
        srand(static_cast<unsigned int>(time(0)));
        srv.request.random_num=(rand()%1000)/(float)1000;
  
        if(client.call(srv))
	    ROS_INFO("random_num: %f,is it less than 0.5: %s", srv.request.random_num,(srv.response.less_than?"Yes":"No"));
        else
            ROS_ERROR("Failed to call service is_less_than");
        loop_rate.sleep();//根据前面的定义的loop_rate,设置2s的暂停
    }
    return 0;
}
