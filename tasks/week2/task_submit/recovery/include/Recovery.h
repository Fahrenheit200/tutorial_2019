#ifndef _RECOVERY_RECOVERY_H
#define _RECOVERY_RECOVERY_H
#include  <chrono>
#include <opencv2/opencv.hpp>
using namespace cv;
class Recovery
{
public:
	void readVideo(String filePath);
	void process();
	void showResult();
private:
	void startClock();
	float endClock();
	VideoCapture cap;
	Mat frame;
	std::chrono::steady_clock::time_point start_tp;
};
#endif
