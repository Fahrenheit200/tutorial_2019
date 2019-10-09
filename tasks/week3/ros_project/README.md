## yyava(吴孟霖) 第三周任务 ROS基本操作
- 作者：吴孟霖
- 时间：19/10/9
- 版本：3.0.1
### 依赖库
- ros
- xterm
安装方法：在终端中输入`xterm`，如提示未安装，安装即可
---
### Topic通信
源码在 src/topic 包中，包含信息发布节点 Publisher 和信息订阅节点 Subscriber，msg文件夹中自定义通信 myMsg.msg， launch文件夹中用于启动节点的topic.launch文件。
**测试方法** 
编译后运行`roslaunch topic topic.launch`

### Service通信
源码在 src/service 中，包含服务端节点Servernode和客户端节点Clientnode,以及自定义的cfg文件set_judge.cfg 。
**测试方法** 编译后运行`roslaunch service service.launch`
启动后client将每隔2s向server发送一条信息
如果只启动了server，请ctrl+C退出并重新运行`roslaunch service service.launch`命令
或另开新端口运行`rosrun service Clientnode`
**动态调节参数方法**
开启服务器后，运行`rosrun rqt_reconfigure rqt_reconfigure`，在service节点中有一个可调参数`rangeNum`,调节范围为0到1，调节效果为，原程序输出随机数小于0.5则输出Yes，调整后，当随机数小于`rangeNum`时才会输出Yes

### 控制小车运动
编写的car_control 包用于控制小车s型运动，使用多线程接受信息。
**测试方法** 编译后运行`roslaunch launch/little_car.launch`即可在rviz看到小车s型运动

