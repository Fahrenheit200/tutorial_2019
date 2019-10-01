#include<iostream>                                                          
#include<opencv2/opencv.hpp>
#include<chrono>
#include<ratio>
#include "../src/Recovery.cpp"
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;
using namespace cv;
using namespace std::chrono;

int main(int argc,char** argv)
{
	string filePath;
	cin>>filePath;

	auto start = steady_clock::now();  //计时开始

	Recovery back_Ground;
	back_Ground.readVideo(filePath);
	back_Ground.process();
	back_Ground.showResult();
	
	auto end = steady_clock::now();
        auto tt = duration_cast<microseconds>(end - start);
        cout<<"Process time:"<<tt.count()/1000000<<" s "<<endl;
	
        waitKey(0);
	return 0;
}
