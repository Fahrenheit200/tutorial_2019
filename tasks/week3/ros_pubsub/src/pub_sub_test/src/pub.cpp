#include "ros/ros.h"
#include "pub_sub_test/my_msg.h"

int main(int argc,char *argv[])
{
    ros::init(argc,argv,"pub_node");
    ros::NodeHandle n;
    ros::Publisher num_pub=n.advertise<pub_sub_test::my_msg>("add_num_msg", 10);

    pub_sub_test::my_msg num;
    ros::Rate loop_rate(10);
    while(ros::ok())
    {
        static int i;
        i++;
        num.A=i;
        num.B=i;
        num.C=i;
        ROS_INFO("A=%d,B=%d,C=%d",num.A,num.B,num.C);
        num_pub.publish(num);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
