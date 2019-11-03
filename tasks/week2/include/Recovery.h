#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#ifndef _RECOVERY_MODULE_H_
#define _RECOVERY_MODULE_H_

class Recovery
{

public:
    /* 
        readVideo
        @param filePath 文件绝对路径
        根据绝对路径读取需要还原背景的文件
    */
    void readVideo(string filePath);

    /* 
        process
        进行还原过程
    */
    void process();

    /*
        showResult
        窗口展示背景还原后的结果
    */
    void showResult();

private:
    VideoCapture video_capture;
    Mat background;
    int frame_count;
};

#endif