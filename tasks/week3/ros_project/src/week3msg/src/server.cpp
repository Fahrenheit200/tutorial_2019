#include <ros/ros.h>

#include <dynamic_reconfigure/server.h>
#include <week3msg/dynamicConfig.h>

void callback(week3msg::dynamicConfig &config, uint32_t level) {
  ROS_INFO("Reconfigure Request:%d,%f", 
            config.bool_param,
	    config.float_param);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "dynamic_par");

  dynamic_reconfigure::Server<week3msg::dynamicConfig> server;
  dynamic_reconfigure::Server<week3msg::dynamicConfig>::CallbackType f;

  f = boost::bind(&callback, _1, _2);
  server.setCallback(f);

  ROS_INFO("Spinning node");
  ros::spin();
  return 0;
}
