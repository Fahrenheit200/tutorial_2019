#include "ros/ros.h"
#include "week3_tutorial/random_float.h"
#include <dynamic_reconfigure/server.h>
#include "week3_tutorial/dynamic_rand_floatConfig.h"

int passValue;
void callback(week3_tutorial::dynamic_rand_floatConfig &config, uint32_t level) {
            passValue = config.Range;
}

bool isRight(week3_tutorial::random_float::Request &req,
			week3_tutorial::random_float::Response &res)
{
		res.range = passValue;
		if(passValue * req.input < 0.5 )
		{
				ROS_INFO("sending back response: [%d]", 1);
				res.output =  true;
		}
		else
		{
				ROS_INFO("sending back response: [%d]", 0);
				res.output =  false;
		}
		return true;
}

int main(int argc, char **argv)
{

  		ros::init(argc, argv, "random_float");
		dynamic_reconfigure::Server<week3_tutorial::dynamic_rand_floatConfig> server;
		dynamic_reconfigure::Server<week3_tutorial::dynamic_rand_floatConfig>::CallbackType f;
		f = boost::bind(&callback, _1, _2);
		server.setCallback(f);

  		ros::NodeHandle n;
   		ros::ServiceServer service = n.advertiseService("random_float", isRight);
   		ros::spin();
        return 0;
}
