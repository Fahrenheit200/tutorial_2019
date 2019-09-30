#ifndef _RECOVERY_H_
#define _RECOVERY_H_

#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp> 
#include <numeric>

using namespace std;
using namespace chrono;
using namespace cv;
class Recovery {
public:
	void readVideo(string filePath);
	void process();
	void showResult();
private:
	Mat background;
	vector<Mat> frames;
	int count;
	int rows;
	int cols;
	milliseconds duration;
};

#endif
