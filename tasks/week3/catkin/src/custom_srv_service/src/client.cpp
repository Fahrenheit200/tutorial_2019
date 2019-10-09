#include <ros/ros.h>
#include "custom_srv_service/custom_srv.h"
#include <dynamic_reconfigure/server.h>
#include <custom_srv_service/dynamic_srvConfig.h>

class Client
{
    public:
        explicit Client(ros::NodeHandle nh_);
    private:
        void configCallback(custom_srv_service::dynamic_srvConfig &config, uint32_t level);
        ros::ServiceClient client;
        ros::NodeHandle nh_;
        custom_srv_service::custom_srv srv;
        dynamic_reconfigure::Server<custom_srv_service::dynamic_srvConfig> dr_srv_;

};
Client::Client(ros::NodeHandle nh_):nh_(nh_)
{
    dynamic_reconfigure::Server<custom_srv_service::dynamic_srvConfig>::CallbackType cb;
    cb = boost::bind(&Client::configCallback, this, _1, _2);
    dr_srv_.setCallback(cb);
    client = nh_.serviceClient<custom_srv_service::custom_srv>("compare");
}
void Client::configCallback(custom_srv_service::dynamic_srvConfig &config, uint32_t level)
{
    ROS_INFO("%f", config.m);
    srand(time(0));
    srv.request.m=config.m;
   // reference = config.m;
   // ROS_INFO("%f", reference);
    for(int i=0; i<5; ++i)
    {
    	srv.request.a = rand()%1000/(double)1000;
    	if(client.call(srv))
    	{
    		ROS_INFO("random number: %f", srv.request.a);
		    if(srv.response.b==1) ROS_INFO("YES");
		    else ROS_INFO("NO");
	    }
    }
}
int main(int argc, char** argv)
{
     ros::init(argc, argv, "custom_srv_client");
     ros::NodeHandle nh;
     ros::service::waitForService("compare");
     Client node(nh);
     ros::spin();
     return 0;
}