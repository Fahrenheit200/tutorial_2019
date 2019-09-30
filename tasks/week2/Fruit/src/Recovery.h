/*
* public:
* private??????????
* 
*/
#pragma once
#include <iostream>  
#include<stdlib.h>
#include<algorithm>
#include<vector>
#include<string>
#include "opencv2/opencv.hpp"  
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

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
    * 使用平均背景法对video进行还原 
    */
    void process();

    /* showResult 
    * 窗口展示背景还原后的结果，并将其保存在 result文件夹中 
    */
    void showResult();
    
private:
	unsigned int findMode(unsigned int*p);
	unsigned int R[PNUMBER],G[PNUMBER],B[PNUMBER];
	VideoCapture capture; 
	Mat video_frame[PNUMBER];
	Mat background;
	int current_frame=0;
	long totalFrameNumber; 
	
};
