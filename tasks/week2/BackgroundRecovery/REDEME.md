
## 第三周项目：背景还原——说明文档

- Author: Tifinity
- Revised: Tifinity
- Date: 2019-9-29
- Version: 1.0.0
- Abstract: 空队考核第二周，视频背景还原。

### 函数:

```c++
/*读取要处理的视频*/
void readVideo(String filePath);
/*进行背景还原处理过程*/
void process();
/*显示结果图片*/
void showResult();
```

### 依赖库:

- opencv

### 编译方法：

~~~s
cd BackgroundRecovery
make
~~~

### 测试方法：

~~~
# how to run:
./bin/test <视频路径>
~~~

应要求没有提交视频文件
结果为result中的result.jpg。

### 算法简述

1. 从视频中随机抽取两帧，相减取绝对值，转灰度，转二值，画出轮廓，删去小轮廓，当且仅当剩两个轮廓时执行步骤2，否则继续循环。
2. 仅剩两个轮廓时表明两帧的前景在不同位置，此时将经过步骤1处理得到的图像轮廓外画矩形并填充为白色，将得到的图像保存于vector backs中。
3. 执行n次步骤1，2。
4. 结果result = backs[0]，遍历vector，将result与每一张back比较，若两张都不为黑色的点取其平均值，result中为黑色的点取back的值。
