#ifndef _RECOVERY_H_
#define _RECOVERY_H_
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Recovery{
public:
	void readVideo(String filePath);
	void process();
	void showResult();
	Recovery(){};
private:
	VideoCapture cap;
	int nframe;
	Mat frame;
	Mat temp;
	Mat sum;
	Mat average;
	Size sz;
	String fp;
};
#endif


