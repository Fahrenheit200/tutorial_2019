## Title Here: Readme Tutorial

- Author: 黄浩东
- Revised: 黄浩东
- Date: 2019-10-04
- Version: 1.0.0
- Abstract: 完成动态参数服务器的编写 

### Functions:
	实现调整随机数生成的范围，并判断随机数是否小于0.5，
	是则输出Yes，否则输出No
	随机数上限变化范围为1~100
	随机数下限变化范围为-100~0 
### Interfaces:
    /*
    *产生min到max的随机浮点数
    */ 
    float getRandData(int min,int max)
    {
	    srand((int)time(0));//用时间做种子 
	    float m1=(float)(rand()%101)/101;
	    min++;
	    float m2=(float)(rand()%(max-min+1)+min);
	    m2--;
	    return m1+m2;
    } 
    
    /*
	*处理动态参数信息
	*/ 
    void paramCallback(dynamic_test::my_cfgConfig &config)
    {
	    float randnum=getRandData(config.min,config.max);//产生随机数 
	    ROS_INFO("Random Num from %d to %d =%f",config.min,config.max,randnum);
	    if(randnum<0.5)
	        ROS_INFO("Yes");
	    else
	        ROS_INFO("No");
    }

### Depend Libraries:
        #include "ros/ros.h"
        #include "dynamic_test/my_cfgConfig.h"
        #include<iostream>
        #include<dynamic_reconfigure/server.h>

依赖库：
        -依赖ros
编译提示：
        $ catkin_make //在ros_dynamic目录下 
        $ source devel/setup.bash
测试程序：
        $ roslaunch dynamic_test dyn.launch
	//打开另一个终端
	$ source devel/setup.bash //在ros_dynamic目录下 
	$ rosrun rqt_reconfigure rqt_reconfigure

        //每调整一次参数，便获得一次输出
