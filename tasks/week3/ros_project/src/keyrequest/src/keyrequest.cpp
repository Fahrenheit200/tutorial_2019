#include "ros/ros.h"
#include "keyrequest/ctrlreq.h"
#include <termio.h>
#include <stdio.h>
int scanKeyboard();
int main(int argc, char *argv[])
{
    ros::init(argc, argv, "keyrequest_node");

    ros::NodeHandle nh;
    ros::ServiceClient myclient = nh.serviceClient<keyrequest::ctrlreq>("ctrlrequest");
    keyrequest::ctrlreq srv;
    ros::Rate loop_rate(20);
    int cmd = 0;
    while (ros::ok())
    {
        cmd = scanKeyboard();
        if (cmd == int('a'))
        {
            srv.request.cmd = int('a');
            srv.request.move = "left";
        }
        else if (cmd == int('w'))
        {
            srv.request.cmd = int('w');
            srv.request.move = "up";
        }
        else if (cmd == int('s'))
        {
            srv.request.cmd = int('s');
            srv.request.move = "down";
        }
        else if (cmd == int('d'))
        {
            srv.request.cmd = int('d');
            srv.request.move = "right";
        }
        else if (cmd == int('1'))
        {
            srv.request.cmd = int('1');
            srv.request.move = "MOVE S";
        }
        else
        {
            srv.request.cmd = 0;
            srv.request.move = "stop";
        }
        ROS_INFO("send movement [%s]", srv.request.move.c_str());
        if (!myclient.call(srv))
        {
            ROS_INFO("Failed to call the service");
            break;
        }
        loop_rate.sleep();
    }
    return 0;
}
int scanKeyboard()
{
    int in;
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(0, &stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(0, &stored_settings);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_settings);

    in = getchar();

    tcsetattr(0, TCSANOW, &stored_settings);
    return in;
}