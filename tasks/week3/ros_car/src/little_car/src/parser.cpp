#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
geometry_msgs::Point position; //小车的位置信息
geometry_msgs::Point velocity; //小车的速度控制


//示例函数  使小车前进
//我们希望你能通过这个函数，模仿实现控制小车的速度，运动方向，转弯等动作
int move_forward(geometry_msgs::TransformStamped &odom_trans)
{

        odom_trans.header.stamp = ros::Time::now();
        odom_trans.transform.translation.x += velocity.x;			//小车 x 方向的移动 每次加上velocity.x的距离
        odom_trans.transform.translation.y += velocity.y;
        odom_trans.transform.translation.z += velocity.z;
		position.x += velocity.x;	//更新小车的位置信息
		position.y += velocity.y;
		position.z += velocity.z;
        odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(0); //小车的角度设置
		return 0;
}
int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
    ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
	ros::Publisher pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
	/* 
	 *请添加一个Subscriber，从你自己编写的Publisher处订阅指令
	 */
    tf::TransformBroadcaster broadcaster;
    ros::Rate loop_rate(30);
    // message declarations
    geometry_msgs::TransformStamped odom_trans;
    sensor_msgs::JointState joint_state;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";
	velocity.x=0.0;    //速度设置，修改该参数可改变小车不同方向的速度
	velocity.y=0.005;
	velocity.z=0.0;
    while (ros::ok()) {
        /***********不重要的部分*********************/
		joint_state.header.stamp = ros::Time::now();
        joint_state.name.resize(4);
        joint_state.position.resize(4);
        joint_state.name[0] ="base_to_wheel_1";
        joint_state.position[0] = 0;
        joint_state.name[1] ="base_to_wheel_2";
        joint_state.position[1] = 0;
        joint_state.name[2] ="base_to_wheel_3";
        joint_state.position[2] = 0;
		joint_state.name[3] ="base_to_wheel_4";
		joint_state.position[3] = 0;
        /********************************************/
		
		//此处调用move_forward函数，使小车一直匀速前进
		move_forward(odom_trans);
		
		pos_pub.publish(position);
        joint_pub.publish(joint_state);
        broadcaster.sendTransform(odom_trans);
        loop_rate.sleep();
    }


    return 0;
}

