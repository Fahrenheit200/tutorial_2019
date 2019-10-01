#include"Recovery.h"
#include<iostream>
#include<chrono>
#include<vector>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;
using namespace std::chrono;

void Recovery::readVideo(string filePath)
{
	file_path = filePath;
}

void Recovery::process()
{
	auto start = steady_clock::now();             //开始计时
	VideoCapture capture(file_path);
	if (!capture.isOpened())				//检测是否正常打开:成功打开时，isOpened返回ture
		cout << "fail to open!" << endl;

	int div;   //用于缩小图片分辨率
	totalFrameNumber = capture.get(CAP_PROP_FRAME_COUNT);			//获取整个帧数
	if (totalFrameNumber < 40)
	{
		totalFrameNumber = 7;
		div = 3;
	}
	else if (totalFrameNumber < 300) 
	{
		totalFrameNumber = 30;
		div = 2;
	}
	else 
	{
		totalFrameNumber = 109;
		div = 3;
	}
	vector< Mat > allFrame(totalFrameNumber);

	Mat tempImg;
	int i = 0;
	for (i = 0; i < totalFrameNumber; i++)   //将视频指定数量帧保存到向量 allFrame 中
	{
		capture >> tempImg;
		resize(tempImg, allFrame[i], Size(tempImg.cols / div, tempImg.rows / div), (0, 0), (0, 0), INTER_AREA);  //缩小原图尺寸，减少像素量
	}
	tempImg.release();

	vector<uchar*> data(totalFrameNumber);      //储存指向每一帧图片的指针
	outputImage.create(allFrame[0].rows, allFrame[0].cols, allFrame[0].type());  //结果图的大小，类型与原图片相同
	int rowNumber = outputImage.rows;  //行数
	int colNumber = outputImage.cols * outputImage.channels();  //每一行元素的个数
	uchar *recoverData = 0;
	vector<uchar> Pixs;      //储存像素点

	int row = 0;
	for (row = 0; row < rowNumber; row++)
	{
		int k = 0;
		for (k = 0; k < totalFrameNumber; k++)
			data[k] = allFrame[k].ptr<uchar>(row);   //第k个指针指向第k帧图片的第j行首地址
		recoverData = outputImage.ptr<uchar>(row);  //获取输出图的第j行首地址

		int col = 0;
		for (col = 0; col < colNumber; col++)
		{
			int jj = 0;
			for (jj = 0; jj < totalFrameNumber; jj++)
				Pixs.push_back(data[jj][col]);
			recoverData[col] = getMode(Pixs);   //选取不同图片相同位置像素的众数
			Pixs.clear();
		}
	}
	auto end = steady_clock::now();
	auto tt = duration_cast<microseconds>(end - start) / 1e6;
	cout << "process time: " << tt.count() << " s" << endl;
}

void Recovery::showResult()
{
	string pictureName(file_path, file_path.size() - 10, 6);  //设置输出图片的文件名
	namedWindow("Recovery result", WINDOW_AUTOSIZE);
	imshow("Recovery result", outputImage);
	imwrite("./result/"+pictureName + ".jpg", outputImage);
	waitKey(8000);                      //图像窗口停留8秒钟
	destroyWindow("Recovery result");   //关闭图像窗口
}

uchar Recovery::getMode(vector<uchar>& A)
{
	uchar n = A.size();
	sort(A.begin(), A.end());
	uchar result;
	result = A[n / 2];
	return result;
}
