#ifndef _QRCODE_H_
#define _QRCODE_H_

#include <opencv2/opencv.hpp>
#include <algorithm>
using namespace std;
using namespace cv;

class Qrcode {
public:
	Qrcode(string filePath);
	void show();
	vector<Mat> images;
	vector<Mat> setions;
	Mat qrcode;
private:
	void recognition(Mat &img);
};

#endif

