# 第三周任务

- 作者：蓝钰乔
- 修订：蓝钰乔
- 日期：2019年10月07日
- 版本：1.0.1
- 摘要：publisher - subscriber的通信和server - client的通信、小车的转弯。解决了CMakeList的BUG



# 编译方法

- 先将`catkin_ws`这一文件夹下载到本地，并进入`catkin_ws`目录下

  ```shell
  $ cd catkin_ws
  ```

- 编译

  ```shell
  $ catkin_make
  ```



# 测试方法

- 测试`publisher`与`subscriber`的通信

  ```shell
  $ source devel/setup.bash
  $ roslaunch src/communication/launch/pub_sub.launch
  ```

  即可看到结果

- 测试`server`与`client`的通信

  ```shell
  $ roslaunch src/communication/launch/srv_clt.launch
  ```

  即可看到结果

- 测试小车走S型

  - 先将`ros_project`这一文件夹下载到本地的`catkin_ws`中
  
  ```shell
$ cd catkin_ws/ros_project
  $ catkin_make
  $ roslaunch launch/little_car.launch
  ```
  
  将镜头拉近即可看到结果




