//#include <iostream>  
//#include<stdlib.h>
/*
#include "opencv2/opencv.hpp"  
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
*/
#include"Recovery.h"
//#include<string.h>
//using namespace cv;
//using namespace std;

unsigned int Recovery::findMode(unsigned int*p)
{
	int i = 0;	
	int MaxCount = 1;
	int index = 0; 
	while (i < current_frame - 1)//遍历	
	{		
		int count = 1;	
		int j ;	
		for (j = i; j < current_frame - 1; j++)	
		{			
			if (p[j] == p[j + 1])//存在连续两个数相等，则众数+1	
			{	
				count++;		
			}			
			else		
			{			
				break;			
			}		
		}		
		if (MaxCount < count)	
		{			
			MaxCount = count;//当前最大众数			
			index = j;//当前众数标记位置		
		}		
		j++;	
		i = j;//位置后移到下一个未出现的数字	
		}	
	return p[index];
}

void Recovery::readVideo(String filePath)
{
	capture.open(filePath);
	if (!capture.isOpened())
	{
		printf("open file fail!\n");
		exit(0);
	}
	else
		printf("open file success!\n");	
}

void Recovery::process()
{
	int nRows,nCols,total=0;
	//获取视频总帧数
	totalFrameNumber = capture.get( CV_CAP_PROP_FRAME_COUNT );
	if (totalFrameNumber<5*PNUMBER)
	{
		while(1)
		{
			if (total==totalFrameNumber)
				break;
			if (total%2==0)
				capture>>video_frame[current_frame++];
			if (current_frame==PNUMBER)
				break;
			total++;
		}		
	}
	else
	{
		int position=0;
		while (1)
		{			//均匀选帧 
			position=((int)totalFrameNumber)/PNUMBER*current_frame;
			capture.set(CAP_PROP_POS_FRAMES,position);
			capture>>video_frame[current_frame++];
			if (current_frame==PNUMBER)
				break;
		}
	}
	//cout << "total frames:" << total << endl;
	cout<<current_frame<<endl;
	
	nRows = video_frame[0].rows;	nCols = video_frame[0].cols;
 	//background=video_frame[0].clone();
	background=video_frame[0];
 	for (int i=0;i<nRows;i++)
		for (int j=0;j<nCols;j++)
		{
			for (int k=0;k<current_frame;k++)
			{
				R[k]=video_frame[k].at<Vec3b>(i,j)[0];
				G[k]=video_frame[k].at<Vec3b>(i,j)[1];
				B[k]=video_frame[k].at<Vec3b>(i,j)[2];
			}
			sort(R,R+current_frame-1);			sort(G,G+current_frame-1);		sort(B,B+current_frame-1);
			background.at<Vec3b>(i,j)[0]=findMode(R);
			background.at<Vec3b>(i,j)[1]=findMode(G);
			background.at<Vec3b>(i,j)[2]=findMode(B);
		}
}

void Recovery::showResult()
{
	//显示背景图片 
//	resize(background,background,Size(background.cols/5,background.rows/5),0,0,INTER_LINEAR);
	imshow("背景", background);
	waitKey(0);
	//保存在本地 
//	imwrite("/home/showtime/tutorial_2019/tasks/week2/result/video0.png",background);
}


