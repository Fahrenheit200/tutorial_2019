#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include"car_move/command.h"
#include"car_move/speed.h"
#include <random>
#include <iomanip>
using namespace std;
int com=0;
int spe=0;
void chatter1Callback(const car_move::command::ConstPtr& msg )
{
  ROS_INFO("I get command  %d", msg->direction);
  com=msg->direction;
  cout<<endl;
}
void chatter2Callback(const car_move::speed::ConstPtr& msg )
{
  ROS_INFO("I get speed  %f", msg->speed);
  spe=msg->speed;
  cout<<endl;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
	little_car car;//初始化控制对象  小车
    //car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
//	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
	   ros::Subscriber sub1 = n.subscribe("chatter1", 1000, chatterCallback1);
        ros::Subscriber sub2 = n.subscribe("chatter2", 1000, chatterCallback2);

	/*
	 *若有需要，也可以从小车处发布你所需要的信息
	 */
        ros::Rate loop_rate(20);
	car.set_noise_level(0);
	float yaw=0.0;
    while (ros::ok()) {
		/*if(com==1)
		     SVector3	velocity={spe,0,0};
		else if (com==2)
		     SVector3 velocity={0,-spe,0};
		else if (com==3)
		     SVector3 velocity={-spe,0,0};
		else
	
	*/ spe=0.008;
	    Svector3 velocity={0,spe,0};
	//	car.set_yaw(yaw);
		cout<<yaw;

		car.set_velocity(velocity);//设置小车速度
        car.update_();//小车状态更新
		loop_rate.sleep();
    }

    return 0;
}



