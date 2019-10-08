ros笔记4
1.	tf
	tf包用于处理机器人仿真的坐标变换问题。可以通过为每一个部件（传感器、轮子等）建立一个坐标系，并根据坐标系之间的关系进行变换。tf使用有根树管理坐标的体系结构
	广播变换tf::TransformBroadcaster br; br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), par_frame, child_frame))
	tf::Transform 可以setOrigin, setRotation
	tf::Quaterion（用四元数表示的旋转） setRPY设置传统欧拉角表示
	tf::TransformListener的神奇之处在于使用lookupTransform得到来自别处的变换后，变换的各个点已经以listener所在坐标系为参考做了转换
2.	launch
<node pkg=”包名” type=”可执行文件名称” args=”参数” name=”节点名” output=”” />
3.	urdf
通用机器人描述语言
一个xml文件，描述了机器人模型各个部件的外形（可导入外部建模）、坐标、朝向、关节连接、材质、物理特性等。
4.	rviz
三维可视化工具
5.	Gazebo
牛逼的机器人仿真工具（炸鸡慎用），可以利用gazebo_ros包来进行ros和gazebo的交互。Gazebo内置了多种传感器的仿真。


