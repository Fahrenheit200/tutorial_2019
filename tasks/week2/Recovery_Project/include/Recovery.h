#ifndef _RECOVERY_H_
#define _RECOVERY_H_
#include<opencv2/opencv.hpp>
#include<iostream>
#include <chrono> 
#include<vector>

using namespace std;
using namespace cv;
using namespace chrono;
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
	void readVideo(string filePath);

	/* process
	* 进行还原过程
	*/
	void process();

	/* showResult
	* 窗口展示背景还原后的结果
	*/
	void showResult();

private:
	Mat result;
	VideoCapture test_video;
	int count;
	vector<Mat> video_shot_arr;
};
#endif


