#include<ros_basic/my_srv.h>
#include<ros/ros.h>


bool CallBack(ros_basic::my_srv::Request &req,
	      ros_basic::my_srv::Response &res)
{
	//res.result=true;

	ROS_INFO("the random number:%0.3f",req.data);
	if(req.data<0.5)
	{res.result=true;}
	else
	{res.result=false;}
	
	return true;

}




int main(int argc,char** argv)
{
	ros::init(argc,argv,"random_num_server");
	ros::NodeHandle n;
	
	ros::Rate loop_rate(0.8);

	//while(ros::ok())
	//{

		ros::ServiceServer my_service=n.advertiseService("/check_random_num",CallBack);

		ROS_INFO("Ready to show the result.");

		loop_rate.sleep();
	//}
	
	ros::spin();

	return 0;
}
