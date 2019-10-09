#include <ros/ros.h>
#include <communication/random_float.h>

bool handle_function(communication::random_float::Request &req, communication::random_float::Response &res){
	if(req.num < 0.5)
		res.judge = true;
	else res.judge = false;
	ROS_INFO("Server: sending back response: %d", res.judge);
	return true;
}

int main(int argc, char** argv) {
	ros::init(argc,argv, "judgement_server");
	ros::NodeHandle n;
	
	ros::ServiceServer service = n.advertiseService("judge",handle_function);
	ROS_INFO("Server: Ready to judge");
	ros::spin();
	
	return 0;
}

