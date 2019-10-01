#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include"Recovery.h"
#include<vector>
#include<chrono>
using namespace cv;
using namespace std;
using namespace std::chrono;
void Recovery::readVideo(String filePath)
{
    cap.open(filePath);
   if (!cap.isOpened())
    {
        printf("open file fail!\n");
        return ;
    }
    printf("open file success!\n");
    pho_row=cap.get(CAP_PROP_FRAME_HEIGHT);
    pho_col=cap.get(CAP_PROP_FRAME_WIDTH);
    frame_num=cap.get(CV_CAP_PROP_FRAME_COUNT);
}
void Recovery::showResult()
{

    namedWindow("result",0);
    cvResizeWindow("result",1000,1000);
    imshow("result",result_p);
    imwrite("re2.png",result_p);
    waitKey(0);
}
void Recovery::process()
{
        //初始化各类需要的变量


        Mat frame,frame2;
        int i=0;
        Mat result;
        vector<vector<Rect>>boundRect;  ///每一帧的矩阵
        vector<Rect>rect(frame_num+1);  ///每一帧的矩阵并集
        vector<vector<unsigned int>> xy(pho_row,vector<unsigned int>(pho_col,0));   ///判断result中的画面是否已经覆盖过
        boundRect.resize(frame_num+1);
        Rect temp,src;



        auto start=steady_clock::now();
        while(++i)
        {
		if(!cap.read(frame))
			break;

		if(i==1)
		{frame2=frame.clone();continue;}

		if(i%10!=5&&frame_num>200)
			continue;
		if(i>frame_num*0.8)
			break;
		getRect(frame2,frame,boundRect,i);


		Rect temp=boundRect[i][0];

		for(int jj=0;jj<boundRect[i].size();jj++)   //得到一帧里面所有边缘矩阵的并集
			temp=temp|boundRect[i][jj];

        rect[i]=temp;

		frame2=frame.clone();
        }
    int flag,flag1,tem;         //根据帧数的不同 进行差异性计算
	if(frame_num<200)
	{flag=2;flag1=2;tem=1;}
	else
	{ flag=15;flag1=15;tem=10;}

    long long num=rect[flag].area();

    for (int ii=flag1;ii<frame_num*0.8;ii+=tem){        //找出并集矩阵中的最小
            if(num>rect[ii].area())
                {num=rect[ii].area(); flag=ii;}
	  }

	 cap.set(CV_CAP_PROP_POS_FRAMES,0);
	 i=0;

	while (++i)
	{
		 if(!cap.read(frame))
                        break;
		 if(i==flag)
		  result=frame.clone(); //仅仅是为了找到最小矩阵的那一帧，对其进行操作


	}


	cap.set(CV_CAP_PROP_POS_FRAMES,0);
	i=0;
    while(++i)
        {

            if (!cap.read(frame))
                        break;
            if((i%10!=5||i<=15)&&frame_num>200||i==1)
                continue;

		    Rect temp=rect[flag];
            Rect src(temp.tl().x-100,0,temp.width+100,pho_row);     //把将要进行赋值操作的范围找出来

            for (int kk=src.tl().x;kk<src.br().x;kk++)
                for(int gg=src.tl().y;gg<src.br().y;gg++)
                    {
                        Point p(kk,gg);
                        if((!rect[i].contains(p))&&xy[gg][kk]==0)
                        {
                            result.ptr<Vec3b>(gg)[kk][0]=frame.ptr<Vec3b>(gg)[kk][0];
                            result.ptr<Vec3b>(gg)[kk][1]=frame.ptr<Vec3b>(gg)[kk][1];
                            result.ptr<Vec3b>(gg)[kk][2]=frame.ptr<Vec3b>(gg)[kk][2];
                            xy[gg][kk]=1;
                        }

                    }
        }


    auto end=steady_clock::now();
    auto tt=duration_cast<microseconds>(end-start);
    cout<<"消耗时间为:"<<tt.count()/1000000<<"s";
    result_p=result.clone();
}
void Recovery::getRect(Mat temp,Mat frame,vector<vector<Rect>>&boundRect,int path)
{
    // 转为灰图
     Mat mat_gray1,mat_gray2;
    cvtColor(temp, mat_gray1, CV_BGR2GRAY);
    cvtColor(frame, mat_gray2, CV_BGR2GRAY);
    // 得到差值图
    Mat mat_diff;
    absdiff(mat_gray1, mat_gray2, mat_diff);
    //3.对差值图diff_thresh进行阈值化处理
    Mat mat_thresh;
    threshold(mat_diff, mat_thresh, 50, 255, CV_THRESH_BINARY);
    //4.腐蚀
    Mat kernel_erode = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat kernel_dilate = getStructuringElement(MORPH_RECT, Size(18, 18));
    erode(mat_thresh, mat_thresh, kernel_erode);
    //5.膨胀
    dilate(mat_thresh, mat_thresh, kernel_dilate);
    //6.查找轮廓并绘制轮廓
    vector<vector<Point> > bound;
    findContours(mat_thresh, bound, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    boundRect[path].resize(bound.size());
    for (int i = 0; i < bound.size(); i++)
        boundRect[path][i] = boundingRect(bound[i]);



}







