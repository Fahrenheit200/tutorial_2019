# 第三周任务
- **作者**：李金东
- **修订**：李金东
- **日期**：2019-10-7
- **版本**：3.1.0
- **摘要**：第三周任务说明

这周没能完成所有任务。115分的模拟器没时间做了，不同噪声下实现s型轨迹不太会做，虽然懂得pid原理但不知道怎么应用，所以只实现了在无噪声下的s型转弯

## 第一个任务
实现Publisher和Subscriber之间的通信  
该任务的package为topic_task  

### 运行方法
```shell
roslaunch topic_task topic_tasks.launch
```
打开之后Publisher就会不断地发在[b,a)之间的随机数  
Subscriber就会不断接收在screen上显示ROS_INFO打印出来的消息  
b a这两个参数可以通过动态参数来调整 可以在rqt_reconfigure_param窗口里面拉动条条来改变b a

### 自己实现的msg
```msg
string name
int32 num
```
### 动态参数cfg
```cfg
gen.add("randomMin",int_t,0,"the smallest random number", 0,0,100)
gen.add("randomMax",int_t,0,"the biggest random number",10,0,100)
```
## 第二个任务
实现client和service之间的通信  
我做完之后才发现审错题了本来是client发送随机数让service判断是否大于0.5  
我写成让client发送请求，让service来产生随机数传回给client然后client再判断是否大于0.5了  
写完之后就不太想改也没有时间改了了/捂脸 毕竟还是掌握了client和server的写法 就请求考核的学长发发慈悲吧/捂脸  
### 运行方法
```shell
roslaunch service_task service_task.launch
```
打开之后server就等待client的请求了  
并且可以再rqt_reconfigure_param窗口里面修改 server产生的随机数的类型，是高斯分布还是均匀分布，如果是高斯分布可以修改高斯分布的方差  
题目要求判断是否大于0.5，我自己修改了一下，这个阈值可以通过动态参数进行修改  
然后再单独开一个终端打开client  
```shell
rosrun service_task service_task_client
```
### 自己实现的srv
```srv
string note
---
float32 num
```
### 动态参数cfg
```py
gen.add("threshold",double_t,0,"threshold", 0.5,0,1)
gen.add("randomType",str_t,0,"uniform or gaussian","uniform")
gen.add("theta",double_t,0,"mean", 0.2,0,10)
```

## 第三个任务
实现小车的方向速度控制和s型走动  
我对小车的控制方式是用按下键盘wsad键来控制上下左右运动  
用动态参数的方法rqt_reconfigure_param窗口来控制小车速度

另外，当键盘按下1时，触发s型走动，s型走动用两个半圆来模拟，半圆的半径也可以用rqt_reconfigure_param窗口来控制  
按除了wsad和1键之外，其它键都会中断小车的当前运动使其停止  
小车在走s型时，按其他键可以当即终止当前的s型运动  
同样在进行上下左右平行坐标轴移动时按1键即可马上触发s型走动  

但是以上的操作都只能在无噪声的情况下操作  
试了一下，使用noise[1]的时候已经走得很乱了。不太会用pid进行控制

实现键盘的监控和发送我混合使用了client server publisher subscriber的概念  
键盘的监控我使用了比较笨的办法  
就是一直在等待键盘，当有按键按下之后就可以得到按下的那个键的ascii码。  
虽然不用按下回车键，但是需要一直等待，只要没有键按下，就不会返回任何值。  
在这个等待的过程时阻塞的，没法一直publish当前按键状态。  

所以我把监控按键的代码写成一个client  
client一直在等待键盘被按下，一旦被按下，就向server发出要publish这个按键的请求。  
server接受到请求之后就把message发布出去。  
所以server既提供了service又充当了publisher，把接收到的srv.request转成msg  
在client等待的空闲时间内以20Hz的频率把之前接受到的信息不断发送出去  

### 具体实现
这段代码是在判断cmd是wsad还是1还是其它按键 不同按键代表不同功能  
不太喜欢用switch就直接用if了哈哈  
keyrequest.cpp作为client
```cpp
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
        if (!myclient.call(srv))
        {
            ROS_INFO("Failed to call the service");
            break;
        }
```
具体实现键盘监控的函数参考了网络 但自己做了些改动
```cpp
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
```
keybroadcast.cpp作为server又作为publisher具体代码还是搬上来吧
```cpp
    ros::ServiceServer myservice;
    ros::Publisher pub = nh.advertise<keyrequest::ctrl>("ctrlcmd", 1);
    ros::Rate loop_rate(20);
    myservice = nh.advertiseService("ctrlrequest", broadcast);
    while (ros::ok())
    {
        //ROS_INFO("send movement [%s]", msg.move.c_str());
        pub.publish(msg);
        loop_rate.sleep();
        ros::spinOnce();
    }
```
myservice通过spinOnce()接受来自keyrequest的消息，但是不阻塞，在等待来自keyrequest的消息的循环体里面不断地通过pub进行publish消息  
callback函数如下
```cpp
bool broadcast(keyrequest::ctrlreq::Request &req,
               keyrequest::ctrlreq::Response &res)
{
    //ROS_INFO("Recieve Cmd = [%c] [%s]", char(req.cmd), req.move.c_str());
    msg.cmd = req.cmd;
    msg.move = req.move;
    res.feedback = "roger that";
    return 1;
}
```
对request信息进行转换转成要发送出去的msg

另外我写了一个keyrecieve.cpp来模拟接收 但不太重要就不放上来了  
### 运行方法
```shell
roslaunch keyrequest ctrlstart.launch
```
用launch的方式既打开了keyrequest又打开了keybroadcast同时打开了rqt_reconfigure进行控制

接下来就是在little_car里面对main函数进行修改了  
修改的部分不多  
首先是声明了几个全局变量 把原本在main函数里是局部变量的velocity搬到了函数体外面
```cpp
/*mycode-----------------------------------------------------------------*/
int MOVE_MODE = 0;
double RADIUS = 1.5;
SVector3 velocity = {0, 0.004, 0};
void sMovement();
void ctrlCallback(const keyrequest::ctrl::ConstPtr &msg);
/*mycode-----------------------------------------------------------------*/
```
其中MOVE_MODE是来判断是要走简单的上下左右控制还是走s型的  
RADIUS是走s型的圆半径  
velocity就是当前运动的速度 记录单位时间内前进的delta值  
sMovement()是专门来走s型的 MOVE_MODE就是为了来判断这个函数是否要被启用  
ctrlCallback作为回调函数接收keybroadcast来的消息  

在main函数内
```cpp
	/*mycode-----------------------------------------------------------------*/
	ros::Subscriber sub = n.subscribe("ctrlcmd", 1, ctrlCallback);
	ros::Rate ctrl_loop_rate(60);
	ros::Rate moveS_loop_rate(500);
	/*mycode-----------------------------------------------------------------*/
```
sub是为了subscribe来自keybroadcast的消息  
两种loop_rate是为了分别控制走上下左右和S型的速度  
走s型要分很多步，但是如果单位时间设置地太小走得就会很慢，于是开了两个loop_rate，ctrl_loop_rate是走上下左右地单位时间  
moveS_loop_rate是走s型的单位时间

while循环内
```cpp
	while (ros::ok())
	{
		/*mycode-----------------------------------------------------------------*/
		sMovement();
		ros::spinOnce();
		/*mycode-----------------------------------------------------------------*/

		car.set_velocity(velocity);
		car.update_();

		/*mycode-----------------------------------------------------------------*/
		if (MOVE_MODE == 1)
			moveS_loop_rate.sleep();
		else
			ctrl_loop_rate.sleep();
		/*mycode-----------------------------------------------------------------*/
	}
```
sMovement和ctrlCallback怎么实现就不说了原理比较简单  
好了整个工作就到这里

## 最终运行的方法
```shell
cd ros_project
catkin_make
source devel/.bashrc
roslaunch keyrequest ctrlstart.launch
```
在另一个窗口
```shell
cd ros_project
roslaunch ./launch/little_car.launch
就可以在keyrequest那个终端里面进行控制 在rviz里面进行观看效果了
```
