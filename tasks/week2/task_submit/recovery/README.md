## Recovery
- Author: PumpkinJimmy
- Revised: PumpkinJimmy
- Date: 2019-09-29
- Version: 1.0.0
- Abstract: Substract the background image of a video using Gaussian Mixture Model
### Functions:
	NULL
### Interfaces:
	void Recovery::readVideo(String filePath);
	void Recovery::process();
	void Recovery::showResult();
## Depend LIbraries:
	OpenCV

使用高斯混合模型（GMM）实现的背景提取器。
1.编译方法
在Makefile所在目录下使用命令make
2.测试方法
使用一个主程序调用Recovery接口，调用示例：
```bin/recovery resource/video0.mp4```
3.算法实现流程
1) 初始化三个高斯模型的均值、标准差和权重
2) 对每一帧扫描每一个像素，找出与当前像素最匹配的一个模型，并拒绝在2.5倍方差以外的模型
3) a.若找到一个匹配的模型，按照学习率更新权重并执行归一化，根据权重和学习率采用加权平均的方式更新匹配的模型的均值和标准差
   b.若找不到匹配模型，则丢弃权值最小的模型，以当前值作为新模型的均值，采用余下模型中最小的权值的一半作为新模型的权值，采用2.5 * 最大标准差作为新标准差。
4) 处理完毕后，对每个位置以(权值/标准差)为标准找出最优模型，该模型匹配的是即为背景，取其均值为该位置像素值
5）最终得到整幅背景
4.本周学习
尝试了三种方法提取模型
- Averge Method 取图像均值，并用差分图像均值充当标准差。先训练背景模型再测试得Foreground Mask。优势是处理快，实现简单。缺点是区分不出影子。
- Median Method 取图像中位数。优点是对video0这种短视频不必等待收敛，缺点是对video2这种缓慢移动甚至静止的大块物体无效。
- GMM Method 高斯混合模型。优点是鲁棒性好，可以虑掉背景轻微的变化，可以自适应调整，对video2这种大块缓慢物体可以发挥多模型的优势。缺点是逐像素运算**非常**耗时。
了解了：
- Mat通道的含义
- 滤波：blur, medianBlur
- 形态学运算：dilate, erode
- Hightgui: imread, imwrite, imshow, waitKey, setMouseCallback
- Videoio: VideoCapture, cap >> frame, cap.isOpened
- 基本矩阵操作：Mat::clone, Mat::copyTo, Mat::convertTo, Mat::copyTo
- 矩阵运算: absdiff, exp, sqrt, min, max, addWeighted, inRange
- 访问图像像素：at<>, ptr<>, MatIterator<>
- 二值化：threshold
- 轮廓：Canny, findContours
- 其他： accumulateWeighted
了解了chrono库

