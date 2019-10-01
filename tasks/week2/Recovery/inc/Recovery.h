#pragma once
#include <iostream>  
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"  
using namespace std;
using namespace cv;

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
	int n_rows,n_cols;
	void countValue(Mat& src, uchar*** ibgk);
	int getLargest(uchar* arr);
	Mat bg;
	VideoCapture cap;
};
