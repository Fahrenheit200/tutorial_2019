## Title Here: Readme Tutorial

- Author: 黄浩东
- Revised: 黄浩东
- Date: 2019-09-29
- Version: 1.0.0
- Abstract: 实现视频背景还原

### Functions:
	读取视频并还原背景，当帧数较低时还原效果差
### Interfaces:
        /* readPixel
        * 读取每一帧的像素值并累加
        */ 
        void readPixel(Mat &src,int iBgk[10000][10000],int rows,int cols);

        /* readVideo
        * @param filePath 文件绝对路径
        * 根据绝对路径读取需要还原背景的文件	
        */
        void Recovery::readVideo(String filePath);
	
        /* process
        * 进行还原过程
        */
        void Recovery::process();

        /* showResult
        * 窗口展示背景还原后的结果
        */
        void Recovery::showResult();
### Depend Libraries:
        #include<iostream> 
        #include<chrono>
        #include<opencv2/core/core.hpp>
        #include<opencv2/highgui/highgui.hpp>
        #include <opencv2/imgproc/imgproc.hpp>

依赖库：
        -依赖opencv
        -依赖chrono
编译提示：
        $ cd build
        $ cmake ..
        $ make
测试程序：
        $ ./test ../../resource/video1.mp4     //在build目录下
        $ ./bin/demo ../resource/video1.mp4    //直接在Recovery_Background目录下编译
算法实现：
        多帧叠加求平均值

运行结果存放在week2/result中
创建了bin文件夹存放编译好的demo
