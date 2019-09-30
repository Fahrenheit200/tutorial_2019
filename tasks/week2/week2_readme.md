# README of week2
- Author：gear0803(卢知之)
- Revised: gear0803(卢知之)
- Date：2019-09-29
- Version：1.0.0
- Abstract：项目的说明以及本周任务的完成情况

---

## 目录
 1. 本次提交的结构
 2. 还原背景的算法说明以及调用方式
 3. makefile的相关说明
 4. 完成情况的汇报
 
----
### 1. 本次提交的结构
```
.
├── addTwoNumbers.cpp
├── background_recovery.md
├── demo
│   ├── 0percent.png
│   ├── 50percent.png
│   ├── res0.jpg
│   ├── res1.JPG
│   └── res2.png
├── programming_exercise.md
├── README.md
├── Recovery
│   ├── bin
│   │   └── main
│   ├── build
│   ├── CMakeLists.txt
│   ├── include
│   │   └── Recovery.h
│   ├── resource
│   │   ├── video0.mp4
│   │   ├── video1.mp4
│   │   └── video2.mp4
│   ├── result
│   │   └── out.jpg
│   ├── src
│   │   └── Recovery.cpp
│   └── test
│       └── test.cpp
├── resource
│   ├── video0.mp4
│   ├── video1.mp4
│   └── video2.mp4
└── shell_exercise.md

10 directories, 22 files

```
----

### 2.还原背景任务的相关说明
#### 2.1 算法说明：
一句话概括太长不看版：抠图。从视频中找到两张障碍物位置不一样的帧A和帧B，找到A的障碍物区域rect，把B中的rect区域抠下来补到A上，A就是完整的背景。
 
详细说明版：
1.首先判断视频中的障碍物位置是否连续变化，并随便抽一帧作为B。
若连续变化，则找到A的障碍物位置，并判断A和B的障碍物位置有无交集，若无交集，则我们刚刚随便抽出来的B有资格作为A的补丁来源，反之，则没有资格，需要重新选B。
若不连续变化，直接判断B有无资格成为A的补丁来源，若无资格，则重新选B。
判断AB障碍物有无交集的方法：用absdiff搭配或操作把A和B的障碍物叠到同一张图上，滤波，findContour+boundingRect，再次过滤掉噪点， 通过得到的矩形数量来判断A和B的障碍物有没有重叠部分。如果重叠了则重新选B，不重叠的话往下执行。
2.找到A的障碍物区域，划定补丁范围。
3.把补丁从B里抠下来打到A上。输出图片
     

#### 2.2 调用说明：
Recovery类的声明如下： 
```

            class Recovery
            {
            public:
            	/* readVideo
            		* @param filePath 文件绝对路径
            		* 根据绝对路径读取需要还原背景的文件
     
            	 process
            	* 进行还原过程

            	 showResult
            	* 窗口展示背景还原后的结果
            	*/
            	void readVideo(string filePath);//filepath是相对路径
            	void process();
            	void showResult();
            
            private:
            	VideoCapture video;
            	vector<Mat> store;
            	int count;
            	Mat output;
};
```
##### 程序的调用示例：使用**相对路径**作为输入参数
```
$./bin/main ./resource/video0.mp4
```
(↑main是bin文件夹下的可执行文件 调用时的文件夹是bin文件夹的上一级)
#### 期望的输出结果：
命令行输出：
```
run time:x.xxxx秒  
```

除此之外还会弹出结果图片，同时图片也会被命名为out.jpg输出在result文件夹下
注：video0的图片比较大，在我的笔记本上是显示不完全的，不知道在测试的学长电脑上效果如何，请学长自行调一下窗口大小来查看，或是直接查看out.jpg。并且，每运行一次不同的视频，都只是更新out.jpg，而不会生成一个新的out.jpg。

### 依赖的库
- 依赖opencv 


----
### 3.makefile说明
Recovery项目结构如下：
```        
        ├── bin
        │   └── main
        ├── build
        ├── CMakeLists.txt
        ├── include
        │   └── Recovery.h
        ├── resource
        │   ├── video0.mp4
        │   ├── video1.mp4
        │   └── video2.mp4
        ├── result
        │   └── out.jpg
        ├── src
        │   └── Recovery.cpp
        └── test
            └── test.cpp

7 directories, 9 files
```
1.我只提交了CMakeLists.txt  如果学长想测试makefile可以跑一下cmake  
2.因为Cmake生成的makefile直接把中间生成的.o文件clean了所以build文件夹是空的

----
### 4.本周任务完成情况汇报

 - 完成了背景还原任务+makefile
 - 完成了链表加法
 - 编写了本说明文档

感想：是知识量暴涨+爆肝的一周。
感谢空队考核给了我一个入门的平台，感谢各位答疑的学长学姐为我们提供耐心的帮助。


