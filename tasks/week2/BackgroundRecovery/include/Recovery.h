#ifndef _PROJECT_MODULE_H_
#define _PROJECT_MODULE_H_

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <chrono>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

class Recovery {
public:
    /* readVideo
    * @brief 根据绝对路径读取需要还原背景的文件
	* @param filePath 文件绝对路径
    */
    void readVideo(String filePath);
    /* process
    * @brief 进行还原过程
    */
    void process();
    /* showResult
    * @brief 窗口展示背景还原后的结果,按任意键退出
    */
    void showResult();
private:
	VideoCapture video;
	Mat result;
};

#endif
