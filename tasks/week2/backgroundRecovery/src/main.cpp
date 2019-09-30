#include <iostream>
#include <chrono>		//计时工具库
#include "Recovery.cpp"

using namespace chrono;

int main(int argc, char** argv) {
	Recovery rec;			//实例化
	rec.readVideo(argv[1]);		//读入视频
	auto startTime = system_clock::now();		//计时开始
	rec.process();					//处理过程
	auto endTime = system_clock::now();		//计时结束
	auto duration = duration_cast<microseconds>(endTime - startTime);
	cout << "processing time: " << double(duration.count()) * microseconds::period::num/microseconds::period::den << "s" << endl;	//输出处理时间
	rec.showResult();		//输出处理后的图像
	waitKey(0);
	return 0;
}
