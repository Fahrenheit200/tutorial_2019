#include "../include/Recovery.h"

//成员函数readVideo的实现
void Recovery:: readVideo(String filePath){
	cap.open(filePath);
	if(!cap.isOpened()){		//判断是否输入成功
		cout << "Fail!" << endl;
	}
	cap >> frame;			//用第一帧图像的信息来初始化
	nframe = cap.get(CV_CAP_PROP_FRAME_COUNT);	//初始化
	sz = frame.size();
	frame = Mat::zeros(sz,CV_32FC3);
	temp = Mat::zeros(sz,CV_32FC3);
	sum = Mat::zeros(sz,CV_32FC3);
	average = Mat::zeros(sz,CV_32FC3);
	fp = filePath;
}
//成员函数process的实现
void Recovery::process(){
	string resultName(fp,fp.size() - 10, 6);
	if (nframe >= 250)		//如果视频的帧数足够多，那么取250帧足够，再多的效果也没有明显变化
		nframe = 250;
	for(int i = 0;i < nframe-1;i++){		//累加每一帧
		accumulate(temp,sum);
		cap >> frame;
		frame.convertTo(temp,CV_32FC3);		//保证输入的每一帧与sum的图像类型是一致的，这样才能累加
		Mat temp = Mat::zeros(sz,CV_32FC3);	//累加一次后temp置0
	}
	sum.convertTo(average,CV_8U,1.0/nframe);	//累加结束后取平均帧，并转化成CV_8U图像以供imshow()输出
	imwrite("../result/"+resultName+".jpg",average);
}
//成员函数showResult的实现
void Recovery::showResult(){
	namedWindow("result",CV_WINDOW_NORMAL);		//更改窗户大小是为了看得方便
	resizeWindow("result",500,500);
	imshow("result",average);
}
