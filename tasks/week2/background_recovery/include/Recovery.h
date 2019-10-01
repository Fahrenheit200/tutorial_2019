#ifndef RECOVERY_H
#define RECOVERY_H

#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <ctime>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
using namespace std::chrono;

/*
* @brief  实现视频背景的提取
*/
class Recovery{
public:
    /* readVideo
    * @param filePath 文件绝对路径
    * 根据绝对路径读取需要还原背景的文件
    */
    void readVideo(String filePath);

    /* process
    * 进行还原过程
    */
    void process();
    void process2();

    /* showResult
    * 窗口展示背景还原后的结果
    */
    void showResult();

private:
    VideoCapture capture;   ///< 视频流
    Mat result;             ///< 还原背景结果
    String file_path;       ///< 视频文件路径
};

#endif
