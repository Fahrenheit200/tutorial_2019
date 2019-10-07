## yyava(吴孟霖) Service通信and动态参数服务器
本文件夹是一个package
### 测试方法
#### 启动服务器方法
编译package后，在命令行运行`roslaunch service service.launch`即可
启动后client将每隔2s向server发送一条信息
如果只启动了server，请ctrl+C退出并重新运行`roslaunch service service.launch`命令
或另开新端口运行`rosrun service Clientnode`
#### 动态调整参数方法

开启服务器后，运行`rosrun rqt_reconfigure rqt_reconfigure`，在service节点中有一个可调参数`rangeNum`,调节范围为0到1，调节效果为，原程序输出随机数小于0.5则输出Yes，调整后，当随机数小于`rangeNum`时才会输出Yes
