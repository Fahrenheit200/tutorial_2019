#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <srv_cli/dynamic_paramConfig.h>
//产生随机数需要的头文件
#include <ctime>
#include <cstdlib>
#include <math.h>

void callback(srv_cli::dynamic_paramConfig &config, uint32_t level) {
  //产生随机数
  srand(static_cast<unsigned int>(time(0)));
  int digit_control=pow(10,config.digit);
  double random_num_fraction=(rand()%digit_control)/(double)digit_control;
  double random_num_int=rand()%(config.range_max-config.range_min)+config.range_min;
  double random_num=random_num_fraction+random_num_int;
  ROS_INFO("dynamic_param_server,random number:%lf",random_num);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "srv_cli");

  dynamic_reconfigure::Server<srv_cli::dynamic_paramConfig> server;
  dynamic_reconfigure::Server<srv_cli::dynamic_paramConfig>::CallbackType f;

  f = boost::bind(&callback, _1, _2);
  server.setCallback(f);

  ros::spin();
  return 0;
}
