#pragma once
#include<string>
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

class Recovery
{
public:
	/* readVideo
		* @param filePath 文件绝对路径
		* 根据绝对路径读取需要还原背景的文件
		
	

	 process
	* 进行还原过程
	
	

	 showResult
	* 窗口展示背景还原后的结果
	*/
	void readVideo(string filePath);
	void process();
	void showResult();

private:
	VideoCapture video;
	vector<Mat> store;
	int count;
	Mat output;
};


