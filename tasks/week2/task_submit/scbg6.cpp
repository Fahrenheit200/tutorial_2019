/*
 A very simple version which work well to make fun of my stupid effort on gmm implementations
*/
#include <timer.h>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
double imshowv(const char* name, Mat img)
{
	Mat res;
	double prop = 800.0 / img.cols;
	resize(img, res, Size(800, img.rows * prop));
	imshow(name, res);
	return prop;
}
float ht = 2.5, lt = 2.5, rate = 0;
Mat frame, pre, avg, avgdiff, avgsqu, diff, bg, avg2, variance;
vector<Mat> grays;
Timer timer;
int main(int argc, char* argv[])
{
	VideoCapture cap(argv[1]);
	int fcnt = cap.get(CAP_PROP_FRAME_COUNT);
	rate = 0.8 / fcnt;
	int t = 0;
	timer.start(1);
	while (1)
	{
		cout << ++t << endl;
		cap >> frame;
		if (frame.empty()) break;
		timer.start();
		frame.convertTo(frame, CV_32FC3);
		if (pre.empty())
		{
			frame.copyTo(pre);
			avg.create(frame.size(), frame.type());
			avgdiff.create(frame.size(), frame.type());
			avgsqu.create(frame.size(), frame.type());
		}
		avg += frame;
		absdiff(frame, pre, diff);
		avgdiff += diff;
		accumulateSquare(frame, avgsqu);
		frame.copyTo(pre);
		timer.update();
	}
	variance = avgsqu / fcnt - avg.mul(avg) / (fcnt * fcnt);
	sqrt(variance, variance);
	avg /= fcnt;
	avgdiff /= fcnt;
	avgdiff += Scalar(1.0, 1.0, 1.0);
	Mat highThresh, lowThresh, mask;

	highThresh = avg + variance * ht;
	lowThresh = avg - variance * lt;
	avg2.create(avg.size(), avg.type());
	cout << "Modeling OK, start, testing" << endl;
	cap.open(argv[1]);
	avg.copyTo(bg);
	while (1)
	{
		cap >> frame;
		if (frame.empty()) break;
		timer.start(2);
		frame.convertTo(frame, CV_32FC3);
		inRange(frame, lowThresh, highThresh, mask);
		accumulateWeighted(frame, bg, rate, mask);
		imshowv("Mask", mask);
		timer.update(2);
		waitKey(33);
	}
	cout << "Whole time cost: " << timer.stop(1) << "s" << endl;
	cout << "Average time cost for a frame accumulating op: " << timer.get_average_t() << "ms" << endl;
	cout << "Average time cost for a frame testing op: " << timer.get_average_t(2) << "ms" << endl;
	imshowv("Res", bg / 255.0);
	// imshowv("avg", avg / 255.0);
	// imshowv("avgdiff", avgdiff /255.0);
	waitKey(0);
	return 0;
}