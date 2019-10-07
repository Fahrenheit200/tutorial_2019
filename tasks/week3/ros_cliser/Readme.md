## Title Here: Readme Tutorial

- Author: 黄浩东
- Revised: 黄浩东
- Date: 2019-10-04
- Version: 1.0.0
- Abstract: 完成Service和Client的编写 

### Functions:
	Client 产生一个 0 到 1 内的随机浮点数，然后发给 Service，
	Service 接受到请求后，判断随机数是否小于 0.5，
	若是则回应布尔值 1，否则回应 0。
	Client 接收到回应后，先输出产生的随机数，然后输出 Yes 或 No 到终端。
### Interfaces:
	Package名称为cli_ser_test
	节点名称为cli和ser
	 
    in Clients:
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
	
	in Service:
    bool callback(cli_ser_test::ser_msgRequest &request,cli_ser_test::ser_msgResponse &response)
    {
    	if(request.rdnum<0.5) 
	    response.re=true;
    	else
   	    response.re=false;
    	return true;
    }
    
    其中srv/ser_msg.srv内容为：
	float32 rdnum
    ---
    bool re
    
### Depend Libraries:
    #include "ros/ros.h"
    #include "cli_ser_test/ser_msg.h"
    #include<iostream>
    #include<time.h>

依赖库：
        -依赖ros 
编译提示：
        $ catkin_make //ros_cliser目录下 
        $ source devel/setup.bash
测试程序：
        $ roslaunch cli_ser_test node.launch

