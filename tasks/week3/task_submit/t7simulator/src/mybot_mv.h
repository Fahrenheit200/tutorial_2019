#include "ros/ros.h"
#include <tf/transform_broadcaster.h>
#include "geometry_msgs/Point.h"

class MybotMv
{
public:
	struct Vector3 { float x; float y; float z; };
	void update_();
	void update_position();
	MybotMv(float x=0, float y=0, float z=0);
private:
	ros::NodeHandle nh;
	ros::Publisher pos_pub;
	Vector3 _velocity;
	Vector3 _position;
	tf::TransformBroadcaster broadcaster;
	geometry_msgs::TransformStamped odom_trans;
	geometry_msgs::Point _pub_position;
};
