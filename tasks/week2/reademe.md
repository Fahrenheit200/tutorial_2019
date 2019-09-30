## Recovery  Listnode 
-author : leelho
-revised:leelho
-date: 2019-9-30
-version 2.0.0
-abstract:介绍recovery实现的方法

### Recovery: 

#### Function
     基本在源码中都有介绍
#### algorithom
     首先根据帧数的不同，找出视频的动态轮廓，用一个大矩阵将其包裹。然后找出这些矩阵中的最小值。以那一帧为原点开始操作。将其他帧不在这个矩阵的所有点像素复制过去。就可以清除掉这个矩阵中的非背景像素。
#### 依赖库
      opencv
#### test
     在week2目录下
     bin/main.out resource/video0.mp4
     
     makefile
     
    直接在week2/下 make即可

###  listnode
    源文件在week2/目录下
###  shell
   在week2/目录下
   /bin/sh shell_exercise/test1.sh
   /bin/sh shell_exercise/test2.sh
   重复运行要先删除文件
 
