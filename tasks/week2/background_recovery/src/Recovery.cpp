//Recovery类实现


#include<iostream>                                                          
#include<opencv2/opencv.hpp>
#include<algorithm>
#include "../inc/Recovery.h"
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;
using namespace cv;


void Recovery::readVideo(String filePath)
{
	fp=filePath;
	VideoCapture capture(filePath);
	i=0;
	Mat frame;
	while(1)
	{
		capture>>frame;
		i++;
		if(frame.empty())
			break;
	}
	i--;

}


void Recovery::process()
{
	VideoCapture cap(fp);
	
	int step,jump;//步长和跳过数
	if(i<100){step=3;jump=0;}
	else if(i>100&&i<300){step=2;jump=1; }
	else if(i>300)  {step=5;jump=1; }

	Mat *fr=new Mat[i];//获取每幅图片的数据
	int n=0;
/*	while(1)
	{
		if(n%step==0){
		cap>>fr[n];
		if(fr[n].empty())
			break;}
		n++;
	}
*/
	for(int n=0;n<i;n++)
	{
		if(n%step==0)
		cap>>fr[n];
	}

	//处理数据
	int cols=(fr[0].cols)*fr[0].channels();
	int offsetx=fr[0].channels();
	int rows=fr[0].rows;
	
	dst=Mat::zeros(fr[0].size(),fr[0].type());

	int * b=new int[i]; 

	for(int row=0;row<rows;row++)
	{
		uchar* output=dst.ptr<uchar>(row);
		for(int col=0;col<cols;col++)
		{
			int *a=new int[i]; 
			for(int j=0;j<i-jump;j=j+step)
			{a[j]=fr[j].ptr<uchar>(row)[col];}
			

			//求众数
			int *b=new int[i];
			for(int j=0;j<i;j++)
				b[j]=0;
			for(int j=0;j<i-jump;j=j+step)
			for(int k=j+step;k<i-jump;k=k+step)
			{
				if(a[j]==a[k])
				{b[j]++;
				b[k]++;}
			}
			int maxim,index;
			maxim=*max_element(b,b+i);
			for(int j=0;j<i-jump;j=j+step)
			{if(maxim==b[j])
				{index=j;break;}
			}
			delete[] b;
			delete[] a;
			output[col]=fr[index].ptr<uchar>(row)[col];
		}
	}
	delete[] fr;
}


void Recovery::showResult()
{
	namedWindow("final",WINDOW_AUTOSIZE);
	imshow("final",dst);
        mkdir("../result",S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	imwrite("../result/final.jpg",dst);
}
