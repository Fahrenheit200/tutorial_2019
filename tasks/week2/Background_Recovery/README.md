## README of Background Recovery Programme
- Author:林嘉鸿
- Revised:林嘉鸿
- Date:2019-09-28
- Version:1.0.0
- Abstract:这篇README说明了如何运行本程序以提取视频文件的背景

### 算法原理:掩模法
在视频中找出符合要求的两帧图像（要求两张图像中的前景图像不重叠且相隔较远）,然后挖去一张图中的前景图像，用另一张图中相同位置的图像来填充，构成一张完整的背景图。具体步骤如下：
- 以视频的第一帧（便于说明，此处设为frame1）作为基准，逐帧读入视频画面并且与frame1作差分计算；
- 将差分计算得出的图像转换为灰度图并进行二值化，然后对其进行轻度的腐蚀以消除部分噪声；
- 在处理后的差分图中查找轮廓，并通过对轮廓的大小进行判定，小于一定阈值的判定为噪声，大于一定阈值的判定为前景图像；
- 当前景图像的数量判定为2时，记录两个图像中前景的位置(轮廓),开始对这两张图进行掩模处理；
- 将某一张图片的前景部分涂黑；
- 另一张图片的对应部分圈选出来，其余部分涂黑；
- 两张图片相加，得到完整背景图。

### 对文件夹内容的说明
- bin:存放可执行文件Recovery
- build:存放编译的目标文件Recovery.o
- include:存放函数声明文件Recovery.hpp
- resource:存放需要被处理的视频文件
- result:存放从视频文件中提取出的视频背景图
- src:存放主程序Recovery.cpp

### 依赖库
- include <iostream>
- include <string>
- include "opencv2/opencv.hpp"
- include "opencv2/features2d/features2d.hpp"
- include "opencv2/highgui.hpp"
- include "opencv2/imgproc/imgproc.hpp"
- using namespace std;
- using namespace cv;

### 编译提示
$ cd Background_Recovery   
$ make   
$ ./bin/Recovery ./resource/video0.mp4   
$ ./bin/Recovery ./resource/video1.mp4   
$ ./bin/Recovery ./resource/video2.mp4   

### 输出示例
Open file success   
Start   
Foreground target have been detected    
Finish   
Total time:0.58913s   

