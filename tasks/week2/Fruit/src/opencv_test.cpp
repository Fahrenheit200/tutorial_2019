#include <iostream>  
//#include<stdlib.h>

#include "opencv2/opencv.hpp"  
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include"Recovery.h"
#include<string>
#include<chrono>
using namespace cv;
using namespace chrono;
using namespace std;

int main()
{
	string video_path;
	cout<<"请输入视频的绝对路径:";
	cin>>video_path;
	
	Recovery re;
	re.readVideo(video_path);
	
	auto start = system_clock::now();
	re.process();
	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout <<  "Process time:" 
     << double(duration.count()) * microseconds::period::num/microseconds::period::den 
     << "s" << endl;
	re.showResult();
	
	return 0;
}
