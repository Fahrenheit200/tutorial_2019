#include <iostream>
#include <ros/ros.h>
#include "test_pkg/JudgeServiceMsg.h"

using namespace std;

bool judge(test_pkg::JudgeServiceMsgRequest& request, test_pkg::JudgeServiceMsgResponse& response)
{
    if(request.num < 0.5)
	response.ans = true;
    else
	response.ans = false;
    return true;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "judge_service");
    ros::NodeHandle n;
    ros::ServiceServer service = n.advertiseService("number_judge", judge);
    ros::spin();
    return 0;
}
