#include<ros_basic/my_srv.h>
#include<ros/ros.h>
#include<stdlib.h>
#include<time.h>
using namespace std;

int main(int argc,char** argv)
{
	ros::init(argc,argv,"random_num_client");
	ros::NodeHandle node;

	//ros::Rate loop_rate(0.8);
	//while(1)
	//{
		ros::service::waitForService("/check_random_num");
		ros::ServiceClient my_client=node.serviceClient<ros_basic::my_srv>("/check_random_num");

		ros_basic::my_srv srv;
		
		srand(time(0));
		srv.request.data=(rand()%1000)/1000.0;//产生0-1的随机数 精度为3位小数

		ROS_INFO("the random number:%0.3f",srv.request.data);

		my_client.call(srv);

		ROS_INFO("smaller than 0.5? %s ",srv.response.result?"Yes":"No");
		
		//loop_rate.sleep();
	//}
	return 0;
}
