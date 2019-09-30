#ifndef _RECOVERY_H
#define _RECOVERY_H
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include<vector>
#include<chrono>
using namespace cv;
using namespace std;
using namespace std::chrono;
/*
* public方法、属性不可变且必须实现
* private方法、属性可自行增添
* 主函数中必须使用public方法；
*/
class Recovery {

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

    /* showResult
    * 窗口展示背景还原后的结果
    */
   void showResult();
    /*getRect
    *@ temp frame 两帧进行边界寻找
    *@ boundRect  找出来的边界存进vector
    *@ path vector index
    */
    void getRect(Mat temp,Mat frame,vector<vector<Rect>>&boundRect,int path);
    private:
    Mat result_p;
    VideoCapture cap;
    int frame_num;
    int pho_row;
    int pho_col;

};
#endif
