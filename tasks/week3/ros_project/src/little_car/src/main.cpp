#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include"parser.h"
#include"car_move/command.h"
#include"car_move/speed.h"
#include <random>
#include <iomanip>
using namespace std;
int com;
float spe;
void chatter1Callback(const car_move::command::ConstPtr& msg )
{
  ROS_INFO("I get command  %d", msg->direction);
 com=msg->direction;
  cout<<endl;
}
void chatter2Callback(const car_move::speed::ConstPtr& msg1)
{
  ROS_INFO("I get speed  %f", msg1->speed);
  spe=msg1->speed;
  cout<<endl;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
    ros::AsyncSpinner spinner(4);
    spinner.start();
	little_car car;//初始化控制对象  小车
    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
     ros::Subscriber sub1 = n.subscribe("chatter1", 1000 , chatter1Callback);
 ros::Subscriber sub2 = n.subscribe("chatter2", 1000, chatter2Callback);

	/*
	 *若有需要，也可以从小车处发布你所需要的信息
	 */
        ros::Rate loop_rate(60);
	car.set_noise_level(0);
	float yaw=0.0;
	SVector3 velocity={0,-0.008,0};
	spe=0.008;

	while(ros::ok()){
		if(com==1)
		     velocity.x=spe;
		else if (com==2)
			velocity.y=-spe;
		else if (com==3)
			velocity.x=-spe;
		else if(com==4)
		{velocity.y=spe;
		 velocity.x=0;
		}	
		
	  cout<<velocity.x<<velocity.y<<com<<spe; 
	//	car.set_yaw(yaw);
		

		car.set_velocity(velocity);//设置小车速度
        car.update_();//小车状态更新
		ros::spinOnce();
		loop_rate.sleep();
    }

    return 0;
}



