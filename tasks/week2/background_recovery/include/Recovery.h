#ifndef A_H
#define A_H
#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
using namespace cv;
using namespace std;
typedef Vec3b Pixel;

class Recovery
{
public:
	void readVideo(string filePath);
	void process();
	void showResult();
	
private:
	int rows, cols, sumFrames;
	int read, step;
	VideoCapture cap;
	Mat frame;
	Mat result;
	vector<Mat> eachframe;
	double t, time;
};
#endif
