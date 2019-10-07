## ROS笔记1
1.	ROS以包package为基本单位，包里有至少CMakeList.txt和package.xml
2.	指令
catkin_make 编译包
source setup.bash 将环境切换到工作空间
rospack
rospack find packname 查看包路径
rospack depends1 packname 查看第一级依赖
rospack depends packname 递归查看依赖包
roscd packname 进入包文件夹
	roscd log 进入日志文件夹
rosls packname ls包文件夹
catkin-create-pkg packname 创建包（注意：要catkin_make过catkin才任这个包）
roscore
rosnode
	rosnode list 显示节点列表
	rosnode cleanup 清理死的节点
	rosnode ping nodename 检验节点联不联系的上
rosrun packname executable启动节点
3.	概念
节点Node：一类可以订阅Subscribers某一主题或是发布Publish某一主题的可执行程序。特点是利用观察者模式解耦，并且不同节点间的通信与节点所用的变成语言无关（C++节点可以和Python节点通信）。
消息Msg：发布或订阅收到的数据的类型。
服务Srv：提供某一功能。
Master：提供节点命名服务（以节点名相互引用、通信）
rosout：一个节点，ROS的stdout/stderr
roscore：主服务？

