#include <cmath>
#include <sstream>
#include <thread>
#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#define INF 0x7ffffff
class vec
{
private:
	double yaw;
public:
	void cal_yaw(){yaw = atan(y/x);}
	double x; double y;
	vec():x(0), y(0), yaw(0) {}
	vec(const vec& other) {x = other.x; y = other.y; yaw = other.yaw;}
	vec(double _x, double _y):x(_x), y(_y) { yaw = atan(y / x);}
	vec operator+(const vec& other) const{ vec r; r.x = x + other.x; r.y = y + other.y; r.cal_yaw(); return r;}
	vec& operator+=(const vec& other) { x += other.x; y += other.y; cal_yaw(); return *this;}
	void rotate(double dyaw)
	{
		yaw += dyaw;
		double dist = sqrt(x * x + y * y);
		x = dist * cos(yaw);
		y = dist * sin(yaw);
	}
};
class PIDControl
{
private:
	double ierr;
	double pre_err;
	double kp, ki, kd;
	double pid;
public:
	PIDControl(double _kp=0.5, double _ki=0.1, double _kd=0.05):
		pre_err(0), ierr(0), kp(_kp), ki(_ki), kd(_kd), pid(0){}
	double getPID() const { return pid; }
	void set(double _kp, double _ki, double _kd) { kp = _kp; ki = _ki; kd = _kd; }
	double handle(double err)
	{
		ierr += err;
		pid = kp * err + ki * ierr - kd * (err - pre_err);
		pre_err = err;
		return pid;
	}
} pid_x(1.1, 0, 0.01), pid_y(1.1, 0, 0.01);
vec v(0, 0.008), pos, expected_pos, pid_vec;
double ix = 0, iy = 0;
bool init_position = false;
double yaw = 0, dyaw = 0.02;
ros::Publisher pub, pub_pid;
int cnt = 0;
vec pid()
{
	double erry = expected_pos.y - pos.y;
	double errx = expected_pos.x - pos.x;
	ix += errx * errx; iy += erry * erry; cnt++;
	geometry_msgs::Point err; err.x = errx; err.y = erry;
	pub_pid.publish(err);
	ROS_INFO("ErrorX: %lf, AverageStd: %lf", err.x, sqrt(ix / cnt));
	pid_x.handle(errx); pid_y.handle(erry);
	vec res; res.x = pid_x.getPID(); res.y = pid_y.getPID();
	expected_pos = expected_pos + v;
	return res;

}
void publishVelocity(geometry_msgs::Point v)
{
	//std::stringstream ss;
	//ss << "Thread " << std::this_thread::get_id() << "publish a msg (" << v.x << "," << v.y << ")";
	//ROS_INFO("%s", ss.str().c_str());
	pub.publish(v);
}
void getPositionCallback(const geometry_msgs::Point::ConstPtr& msgs)
{
	pos.x = msgs->x; pos.y = msgs->y;
	ROS_DEBUG("Car position:(%lf, %lf)", pos.x, pos.y);
	if (!init_position) {init_position = true; expected_pos.x = pos.x; expected_pos.y = pos.y; ROS_INFO("initial position got: (%lf, %lf), all work start", pos.x, pos.y);}
	else{
		ROS_DEBUG("Expected Position: (%lf, %lf)", expected_pos.x, expected_pos.y);
		if (yaw > 3.14 || yaw < 0) dyaw = -dyaw;
		v.rotate(dyaw);
		yaw += dyaw;
		pid_vec = pid();
		geometry_msgs::Point msg;
		msg.x = v.x;
		msg.y = v.y;
		msg.z = 0;
		std::thread t1(publishVelocity, msg);
		msg.x = pid_vec.x;
		msg.y = pid_vec.y;
		std::thread t2(publishVelocity, msg);
		t1.join();
		t2.join();
		ROS_DEBUG("Velocity instruction:(%lf, %lf)", msg.x, msg.y);
		ROS_DEBUG("PID vector: (%lf, %lf)", pid_vec.x, pid_vec.y);
	}
}
int main(int argc, char** argv)
{
	ros::init(argc, argv, "car_controller");
	ros::NodeHandle nh;
	pub = nh.advertise<geometry_msgs::Point>("car_control", 1);
	pub_pid = nh.advertise<geometry_msgs::Point>("error", 1);
	ros::Rate loop_rate(20);
	ros::Subscriber sub = nh.subscribe<geometry_msgs::Point>("car_position", 1, getPositionCallback);
	while (ros::ok())
	{
		//if (!init_position) continue;
		ros::spinOnce();
		//if (!init_position) { ROS_INFO("No car initial position, not prepare to work"); continue;}
		//if (!init_position) { geometry_msgs::Point msg; msg.x = v.x; msg.y = v.y; pub.publish(msg); continue;}
		//ROS_INFO("Car position:(%lf, %lf)", pos.x, pos.y);
		
		loop_rate.sleep();
	}
	return 0;
}
