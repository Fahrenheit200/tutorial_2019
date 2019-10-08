#include <iostream>
#include <ros/ros.h>
#include "test_pkg/JudgeServiceMsg.h"
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "judge_client");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<test_pkg::JudgeServiceMsg>("number_judge");
    test_pkg::JudgeServiceMsg srv;
    
    srand(time(NULL));
    int N = 999;
    while (ros::ok()) 
    {
	srv.request.num = rand() % (N + 1) / (float)(N + 1);
	cout << srv.request.num << endl;
	if(client.call(srv))
	{
	    if(srv.response.ans)
	    	cout << "Yes" << endl;
	    else
		cout << "No" << endl;
	}
	else
	{  
	    ROS_ERROR("Failed to call service number_judge");
            return 1;
	}
    }
    return 0;
}

