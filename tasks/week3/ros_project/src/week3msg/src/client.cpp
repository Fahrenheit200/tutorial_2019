#include "ros/ros.h"
#include "week3msg/week3srv.h"
#include"dynamic_reconfigure/client.h"
#include"Client.h"
#include <cstdlib>
#include"week3msg/dynamicConfig.h"
#include<iostream>
#include<ctime>
using namespace std;
void CallBack(const week3msg::dynamicConfig &data)
{
    ROS_INFO(" double: %f, bool: %d",data.float_param,
             data.bool_param);
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "client");

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<week3msg::week3srv>("service");
 dynamic_reconfigure::Client<week3msg::dynamicConfig> Client("dynamic_par",CallBack);
  week3msg::week3srv srv;
  week3msg::dynamicConfig config;
  float num;
  srand(time(0));
  num=rand()%(1000)/(float)(1000);
  srv.request.req=num;
  if (client.call(srv))
  {
     cout<<"The num is "<<num<<endl;
     if(srv.response.repb)
   	cout<<"Yse"<<endl;
     else
	cout<<"No"<<endl;
    config.bool_param=srv.response.repb;
    config.float_param=num;
    Client.setConfiguration(config);    
    
  }
  else
  {
    ROS_ERROR("Failed to call service add_two_ints");
    return 1;
  }

  return 0;
}
