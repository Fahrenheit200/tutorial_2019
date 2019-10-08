#include "ros/ros.h"
#include "week3_tutorial/random_float.h"
// #include <dynamic_reconfigure/server.h>
// #include "week3_tutorial/dynamic_rand_floatConfig.h"
#include <cstdlib>
#include <ctime>

//返回一个0-1间的随机浮点数
float get_rand()
{
    int i;
    const int N =  9999;  //4位小数。
    srand(time(NULL));//设置随机数种子，使每次获取的随机序列不同。
    return (rand()%(N+1)/(float)(N+1));//生成0-1间的随机数。
}

int main(int argc, char **argv)
{
		ros::init(argc, argv, "random_float_client");

//		dynamic_reconfigure::Server<week3_tutorial::dynamic_rand_floatConfig> server;
 //	    dynamic_reconfigure::Server<week3_tutorial::dynamic_rand_floatConfig>::CallbackType f;

 // 		f = boost::bind(&callback, _1, _2);
 // 		server.setCallback(f);

		ros::NodeHandle n;
		ros::ServiceClient client = n.serviceClient<week3_tutorial::random_float>("random_float");
		week3_tutorial::random_float srv;
		srv.request.input = get_rand();
		if(client.call(srv)) {
				 double num = srv.response.range * srv.request.input;
				if(srv.response.output) {
						ROS_INFO("Range of random float numbers: 0 to %d",srv.response.range);
						ROS_INFO("random float number: %lf", num);
						ROS_INFO("YES");
				}
				else {
						ROS_INFO("Range of random float numbers: 0 to %d",srv.response.range);
						ROS_INFO("random float number: %lf", num);
						ROS_INFO("NO");
				}
		}
		else {
				ROS_ERROR("Failed to judge");
				return 1;
		}
		return 0;
}
