//----------------------------------------
// 引入头文件，对recovery.h的函数进行定义
//---------------------------------------
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include "recovery.h"

using namespace std;
using namespace cv;
/**
 *从固定路径读取视频
 * filePath  需要读取的视频的固定路径
 */
void Recovery::readVideo(string filePath)
{
	video.open(filePath);
	if(!video.isOpened())
	{
		cout<<"failed to open"<<endl;
	}
}	
/**
 *对读取的视频进行处理，还原出背景
 */
void Recovery::process()	
{
	framecount = video.get(CAP_PROP_FRAME_COUNT);   //获得视频总帧数
	rows = video.get(4);    //视频一帧的行数
	cols = video.get(3);    //列数
	result.create(rows,cols,CV_8UC3);        //初始化result，最后将作为结果图，大小和视频一帧相同，为RGB三通道
	result=Mat::zeros(rows,cols,CV_8UC3);
	//出于对内存的考虑，均匀选取样本帧
	int num;   //选取的帧数
	if(framecount<100) num=20;   //总帧数不足50，均匀选20帧
	else num=80;                //大于100则选取80
	Mat frame[num];    //图像数组，用于存储样本帧
	int d=framecount/num; //每次选取帧的距离
	for(int i=0, j=0; i<framecount && j<num; i+=d, ++j)
	{
		video.set(CAP_PROP_POS_FRAMES,i);
		video.read(frame[j]);
	}
	//接下来找出样本帧相同位置像素点的众数作为背景像素
	for(int i=0; i<rows; ++i)
	{
		for(int j=0; j<cols; ++j)
		{
			int maj[3]={0};  //分别存储三个通道的众数
			int blue=0, green=0, red=0;   //用于存储结果图三个通道的像素值
			int a[255]={0}, b[255]={0}, c[255]={0}; //桶排序 找出众数
			for(int m=0; m<num; ++m)
			{
				a[frame[m].at<Vec3b>(i,j)[0]]++;
				b[frame[m].at<Vec3b>(i,j)[1]]++;
				c[frame[m].at<Vec3b>(i,j)[2]]++;
			}
			for(int n=0; n<255; ++n)
			{
				if(maj[0]<a[n]) {maj[0]=a[n]; blue=n;}
				if(maj[1]<b[n]) {maj[1]=b[n]; green=n;}
				if(maj[2]<c[n]) {maj[2]=c[n]; red=n;}
			}
			result.at<Vec3b>(i,j)[0]=blue;
			result.at<Vec3b>(i,j)[1]=green;
			result.at<Vec3b>(i,j)[2]=red;
		}
	}
}
/**
 *输入处理后的图像，即视频的背景
 */
void Recovery::showResult()
{
	namedWindow	("result",WINDOW_NORMAL);
	resizeWindow("result",600,600);
	imshow("result",result);
	waitKey(0);
}
