# 第二周考核任务代码说明

------

- Author: 刘佳豪
- Revised: 刘佳豪
- Date: 2019-09-30
- Version: 2.2.0
- Abstract: 关于第二周图像处理任务的提交说明

------


## Recovery类说明
```

//PNUMBER为读取视频帧数的最大值
const int PNUMBER=60;

class Recovery 
{
public:
    /* readVideo
    * 绝对路径:/home/showtime/tutorial_2019/tasks/week2/resource
    * 根据绝对路径读取需要还原背景的文件 
    */
    void readVideo(String filePath);

    /* process
    * 使用均匀取帧法对video进行还原 
    */
    void process();

    /* showResult 
    * 窗口展示背景还原后的结果，并将其保存在 result文件夹中 
    */
    void showResult();
    
private:
    /* findMode
    * 寻找R，G，B中的众数
    */
	unsigned int findMode(unsigned int*p);
	
	//分别存储所取的不同的帧各自对应像素点的RGB像素值
    unsigned int R[PNUMBER],G[PNUMBER],B[PNUMBER];
	VideoCapture capture; 
	
	Mat video_frame[PNUMBER];   //均匀存取帧
	Mat background;         //背景
	int current_frame=0;    //已存取帧数
	long totalFrameNumber;  /读取视频的总帧数
};
```
### 1. 核心函数process简要说明

```
void Recovery::process()
{
    
    int nRows,nCols,total=0;    //帧数的行和列
	uchar* p;
	//获取视频总帧数
	totalFrameNumber =              
	   capture.get(CV_CAP_PROP_FRAME_COUNT );
	if (totalFrameNumber<5*PNUMBER)
	    ...    //对于帧数小的视频，以步长为2进行读取
	else
	{   //对于帧数较大的视频，设置步长为
	    //spaceing=totalFrameNumber/PNUMBER；
	    //然后以此步长存储视频帧
	}
    //将视频帧的大小赋给backgrund
    ...
    //将存储的视频帧对应像素的RGB值分别存在数组中
 	R[k]=video_frame[k].at<Vec3b>(i,j)[0];	
 	G[k]=video_frame[k].at<Vec3b>(i,j)[1];	
 	B[k]=video_frame[k].at<Vec3b>(i,j)[2];
	
	...
//找出RGB数组中的众数，然后赋给background对应像素
	findMode（RorGorB）；
}
```

### 依赖库及头文件
```
#include <iostream>  
//#include<stdlib.h>
#include<algorithm>
//#include<vector>
#include<string>
#include<chrono>
#include "opencv2/opencv.hpp"  
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<chrono>
using namespace chrono; 
using namespace std;
using namespace cv;
```

### 4. 项目结构
项目名：opencv_test
bin/（opencv_test（即主函数）的可执行文件）
build/      （Makefile执行文件夹）
src/(opencv_test.cpp Recovery1.cpp Recovery1.h)
CMakeLists.txt (编译文件)


### 5. 编译
/build$ cmake ..

/build$ make

### 6.  测试样例
/bin$ ./opencv_test
请输入视频的绝对路径:
...
Process time： ...

### 7. 一点题外话
1 三个视频中最慢的需要50s左右，最快的10s左右。
2 希望明年的考核指南能出一份关于cmake的。动态库静态链接啥的晕了。。。
3 处理这周视频问题的依据是：作为背景点，一般情况下它的像素在整个视频中所占帧数应该是最多的。分别处理低帧数视频和高帧数视频是想缩短运行时间。
4 依据3，均匀取帧的条件下帧数越多意味着取帧的间隔越短，效果应该不会很好。但不知道为什么处理video2的时候帧数越多会越好，而在video1这里帧数越多噪点越多...

