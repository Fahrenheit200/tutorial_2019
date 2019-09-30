#include "../include/Recovery.h"

int iBkg[10000][10000]={0};///iBkg存储像素的叠加值

/* readPixel
* 读取每一帧的像素值并累加
*/ 
void readPixel(Mat &src,int iBgk[10000][10000],int rows,int cols)
{
	uchar *p;                     //p指向每一个像素 
	for(int i=0;i<rows;++i)
	{
		p=src.ptr<uchar>(i);      //p指向当前行 
		for(int j=0;j<cols*3;++j)  //p移动至当前行每一列的像素 
		{
			iBgk[i][j]+=p[j];     //将src的像素值存入iBkg中 
		}
	}
}

/* readVideo
* @param filePath 文件绝对路径
* 根据绝对路径读取需要还原背景的文件	
*/
void Recovery::readVideo(String filePath)
{
	cap.open(filePath);
	if(!cap.isOpened())
	{
		cout<<"Failed to open file"<<endl;
	}
}

 /* process
* 进行还原过程
*/
void Recovery::process()
{                   
	int total=0;                 //total标志着总共读取了多少帧 
	cap.read(frame);
	int rows=frame.rows;
	int cols=frame.cols;
	while(1)
	{
		if(!cap.read(frame)||total==240)    //如果读取当前帧为空，则退出循环 
			break;
		readPixel(frame,iBkg,rows,cols);  //将当前帧的像素值加入iBkg中 
		total++;                           //帧数+1 
	}
	cap.release();                        //关闭视频 
	uchar *p;                             //p提取iBkg的每一个像素值放入bkg中 
	Mat src(rows,cols,CV_8UC3);           
	resize(src,bkg,Size(cols,rows));      //改变bkg的大小与视频的大小相同 
	for(int i=0;i<rows;++i)
	{
		p=bkg.ptr<uchar>(i);             //p指向bkg最终背景图 
		for(int j=0;j<cols*3;++j)
		{
			p[j]=iBkg[i][j]/total;       //取像素平均值并存入背景图
		}
	}
} 

/* showResult
* 窗口展示背景还原后的结果
*/
void Recovery::showResult()
{
	namedWindow("Background",WINDOW_AUTOSIZE); 
	imshow("Background",bkg);
	waitKey(0);
} 
