# 第二周任务完成说明
- 作者：方至钰
- 修订：方至钰
- 日期：2019-9-30
- 版本：1.0.0 
- 摘要：这是方至钰完成的空队考核第二周任务的说明，主要包括用opencv库编写程序还原背景图和链表加法。

***
## 一、使用opencv库编写程序还原视频背景
### PS:由于虚拟机内存问题，只能还原出video1的背景图，所以还考核学长们编译后测试一下另外两个，谢谢！
### 1. 模块功能
+ 还原出视频中静止不动的背景图
### 2. 接口
+ //filePath: 文件绝对路径,根据绝对路径读取需要还原背景的文件
+ `void Recovery::readVideo(String filePath);`
+ //进行还原过程
+ `void Recovery::process();`
+ //窗口展示背景还原后的结果
+ `void Recovery::showResult();`
### 3. 依赖库
+ -依赖opencv
### 4. 编译提示
+ `$ cd tutorial_2019/tasks/week2/Recovery`
+ `$ make`
### 5. 测试程序
+ `$ cd tutorial_2019/tasks/week2/Recovery`
+ `$ ./bin/demo ../resource/video0.mp4`
+ `$ ./bin/demo ../resource/video1.mp4`
+ `$ ./bin/demo ../resource/video2.mp4`
### 6. 算法实现流程
+ 通过读取每一帧像素值，并统计出出现最多次的值，即众数，作为背景图对应点的值。

***
## 二、程序设计能力练习题：链表加法
### 1. 模块功能
+ 实现两个链表的加法
### 2. 接口
+ `ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);`
### 3. 算法实现流程
 1. 将链表中的每个数组合生成一个数
 2. 将两个链表生成的数相加
 3. 将相加得到的数分开成每一位数
 4. 创建新链表并将分开的每一位数填入新链表中
