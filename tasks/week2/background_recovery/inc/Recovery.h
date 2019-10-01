//Recovery类声明

#ifndef _Recovery_
#define _Recovery_

#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

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

private:
    int i;//帧数
    string fp;//文件
    Mat dst;//最终
};

#endif
