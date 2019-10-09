#include <ros/ros.h>
#include <communication/random_float.h>
#include <cstdlib>
#include <ctime>

int main(int argc, char** argv){
	ros::init(argc,argv, "jugdement_client");
	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<communication::random_float>("judge");
	communication::random_float srv;
	srand(time(NULL));
	ros::Rate loop_rate(1.0);
	while(ros::ok()){
		srv.request.num = rand()/double(RAND_MAX);
		if(client.call(srv)){
			ROS_INFO("Client: random_float=%f",srv.request.num);
			if(srv.response.judge == true)
				ROS_INFO("Client: Yes");
			else ROS_INFO("Client: No");
		}
		else{
			return 1;
		}
		loop_rate.sleep();
	}
	return 0;
}
