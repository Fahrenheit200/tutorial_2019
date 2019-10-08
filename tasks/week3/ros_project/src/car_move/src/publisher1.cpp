#include "ros/ros.h"
#include<cstdlib>
#include<iostream>
#include<ctime>
#include"car_move/command.h"
#include"car_move/speed.h"
#include <sstream>
using namespace std;

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line. For programmatic
   * remappings you can use a different version of init() which takes remappings
   * directly, but for most command-line programs, passing argc and argv is the easiest
   * way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "publisher2");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name. This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing. After this advertise() call is made, the master
   * node will notify anyone who is trying to subscribe to this topic name,
   * and they will in turn negotiate a peer-to-peer connection with this
   * node.  advertise() returns a Publisher object which allows you to
   * publish messages on that topic through a call to publish().  Once
   * all copies of the returned Publisher object are destroyed, the topic
   * will be automatically unadvertised.
   *
   * The second parameter to advertise() is the size of the message queue
   * used for publishing messages.  If messages are published more quickly
   * than we can send them, the number here specifies how many messages to
   * buffer up before throwing some away.
   */
  ros::Publisher chatter1_pub = n.advertise<car_move::command>("chatter1", 1000);
  ros::Publisher chatter2_pub = n.advertise<car_move::speed>("chatter2", 1000);

  ros::Rate loop_rate(20);

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;
  while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
	  srand(time(0));
	  car_move::command  com;
	  car_move::speed spe;
	  int num;
	  if(count<=40)
		  num=3;
	  else if(count<=120&&count>40)
		  num=1;
	  else if(count<=160&&count>120)
		  num=3;
          else 
		  num=4;
	  if(count==320)
	  { count=0;num=2;}
             
    com.direction=num;
   
    spe.speed=0.008;

    ROS_INFO("command: %d, speed: %f",com.direction,spe.speed);
    cout<<endl;
    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    chatter1_pub.publish(com);
    chatter2_pub.publish(spe);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
