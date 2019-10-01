## OpenCV背景图片还原

-作者: 李泓舟

-修订: 李泓舟

-日期: 2019.9.29

-版本: v2.0.0

-摘要: 使用opencv还原短视频的背景



#### 接口示例

-void Recovery::readVideo(string filePath);

-void Recovery::process();

-void Recovery::showResult();



#### 依赖库

-include<opencv2/core/core.hpp>

-include<opencv2/highgui/highgui.hpp>

-include<numeric>

-include<vector>

-include<string>

-include <chrono>

-include <iostream>





####  编译提示

$ cd bin

$ cmake ..

$ make



#### 运行示例

(注: 依据个人理解readVideo()中将视频的所有帧都存在了私有成员vector<Mat>中。该做法在前两个视频中运行流畅，但是第三个视频较大，在虚拟机中运行似乎会因为内存不足而被中断。还请在设备状态良好时运行，实在不行就算了……依照要求resource已为空，请先将视频移入，或更改路径。)

$ ./bin/recovery ../resource/video0.mp4 





#### 运行结果:

Process time: 5.367s

(注: video0 约5秒, video1约10秒, video2约60秒,另外result中只会有一张图片background.jpg作为结果，所以请逐个视频运行。)



-----------

## 链表加法

​		对应文件为ListPlus.cpp, 该函数接受两个链表的指针，链表每个节点为0-9的数字，表示一个整数逆序的各位数字，返回一个表示上述链表加和的链表指针，同样是逆序的。本函数只适用带有头结点的链表，头结点的数据域无效。

