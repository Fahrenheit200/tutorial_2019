#第二周作业说明
- Author: 郭印林
- Revised: 郭印林
- Date: 2019-09-30
- Version: 1.0.0
- Abstract: 关于第二周作业的提交说明

---
## 视频背景提取
###1. 代码用途及调用规则
    代码实现了对输入视频背景的提取，运行时间取决于视频大小。

函数
```
//读取视频
Recovery::readVideo(string filepath)
//处理视频
Recovery::process()
//显示并保存图像
Recovery::showResult()
//类私有函数，用来求vector的中值
Recovery::majorityElement(vector<int> nums)
```
依赖库及头文件,命名空间
```
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
using namespace chrono;
using namespace cv;
using namespace std;
```

测试
>进入 VideoProcess 目录下直接执行以下命令（为测试方便，bin里面已经存放了三个video）
```
# how to run
$ cd bin
$ ./opencv_test videox.mp4

# runing time
>>>花费了xxxx秒
```
###2. 实现思路
1. 最开始是想通过求出所有视频帧的像素和再取平均值，但是代码实现之后发现鬼影严重（尤其第一张图）。
2. 所以最后选择的方法是读取视频的部分帧图像，通过遍历每个像素，找出像素出现次数最多的值，根据这些值生成一张新的图片。

---

## 链表加法
    实现两个链表相加
### 调用
```
# Input Node l1,l2 , output a new node point
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);
```
### 实现思路
1. 在链表不为空时，先将短的链表的其他元素取0，再从链表第一个节点（最低位）开始相加，保留进位信息，逐个生成新的链表。
