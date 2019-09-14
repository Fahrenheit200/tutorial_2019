## 基础考核 - 第三周（9.30-10.6）

必学内容：

- 1、熟悉ROS的基本操作，包括文件架构，通信机制(Publisher, Subscriber, Service, Client，msgs)，功能包的创建，节点，服务器等。  
- 2、熟练使用检索工具，善于查看官方文档获取资料  
- 3、熟练使用cmake。  
- 4、推荐教程[bilibili ros 教程](https://www.bilibili.com/video/av24585414?from=search&seid=8886024381809662153)

选修内容：

- 1、了解ros的可视化工具，包括二维的rosplot，三维的rviz。

本周任务：
- 1、 编写一个package，其中包含一个信息发布节点Publisher，和一个信息订阅节点Subscriber。信息发布节点产生随机数据并发布，消息类型要求使用自己创建的，信息订阅节点订阅并将数据输出到终端。
- 2、编写launch文件并用roslaunch启动节点
- 3、编写Service和Client，Client产生一个0到1内的随机数，然后发给Service，Service接受到请求后，判断随机数是否小于0.5，若是则回应 1，否则回应0。Client接收到回应后，先输出产生的随机数，然后输出Yes或No到终端。
- 4、 编写一个动态参数服务器
- 5、 利用提供的小车模型和源码，模仿源码并在源码的基础上修改，试着实现小车的转弯、停止，并尝试使用Publisher来发布指令来控制小车的方向和速度。
- 6、 让小车走一个S形（注意，我们在小车的行走中将加上噪声，这意味着你需要位置信息来做调整）


评分标准：  

|评分项       				  	|分值           |
|-------------------------------|---------------|
|完成Publisher与Subscriber通信	|30				|
|在通信中使用自己的msgs			|20				|
|编写launch文件来启动节点		|20				|
|完成Service与Client通信		|10				|
|完成动态参数服务器				|10				|
|实现小车的转弯动作				|50				|
|实现通过Publisher控制小车运动	|55				|
|让小车走S形					|55				|

怎么运行？  
```
cd little_car
catkin_make
source devel/setup.bash
roslaunch launch/little_car.launch
```
Tips:
- 1、 多看ROS wiki以及使用搜索引擎将有助于你解决大部分问题
- 2、 对于源码有疑问，可以在群里发问，我们会在合适的范围内给予解答