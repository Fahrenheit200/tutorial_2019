#ifndef _PROJECT_MODULE_H_
#define _PROJECT_MODULE_H_

#include<iostream> 
#include<chrono>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std; 
using namespace cv;
using namespace chrono;

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

    /* showResult
    * 窗口展示背景还原后的结果
    */
    void showResult();
    
private:
    Mat frame,bkg;         ///frame用来存储视频的每一帧
                           ///bkg为提取的背景图 
    VideoCapture cap;            
}; 

#endif 

