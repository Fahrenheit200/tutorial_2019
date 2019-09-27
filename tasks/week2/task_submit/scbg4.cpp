#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
using namespace cv;
using namespace std;
typedef Vec<uchar, 5> Vec5u;
void onMouse(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		cout << "(" << x * 4 << "," << y * 4 << ")" << endl;
	}
}

inline void insert(Vec5u& v, int ed)
{
	uchar k = v[ed];
	int i = ed;
	for (;i > 0 && v[i - 1] > k;i--)
	{
		v[i] = v[i - 1];
	}
	v[i] = k;
}
uchar getMid(const Vec5u& vec)
{
	Vec5u v = vec;
	for (int i = 1; i <= 4; i++) insert(v, i);
	return v[2];
}

Mat toView(Mat ori)
{
	Mat res;
	resize(ori, res, Size(800, 800 * ori.rows / ori.cols));
	return res;
}
void imshowv(const char* name, Mat img)
{
	imshow(name, toView(img));
}
float rate = 0.1;
int main(int argc, char* argv[])
{
	VideoCapture cap(argv[1]);
	Mat frame, gray, last, diff, mask, bgs, bg;
	vector<Mat> imgs;
	for (int i = 1; i <= 5; i++)
	{
		cap >> frame;
		cvtColor(frame, gray, CV_BGR2GRAY);
		imgs.push_back(gray.clone());
	}
	namedWindow("Gray");
	setMouseCallback("Gray", onMouse);
	while (1)
	{
		cap >> frame;
		if (frame.empty()) break;
		cvtColor(frame, gray, CV_BGR2GRAY);
		if (bg.empty()) bg.create(gray.size(), gray.type());
		imgs.push_back(gray.clone());
		imgs.erase(imgs.begin());
		merge(imgs, bgs);
		auto itbg = bg.begin<uchar>();
		for (auto it = bgs.begin<Vec5u>(); it != bgs.end<Vec5u>(); it++, itbg++)
		{
			uchar mid = getMid(*it);
			*itbg = (uchar)(*itbg * 0.9 + 0.1 * mid);
		}
		imshowv("Gray", gray);
		imshowv("Res", bg);
		if (waitKey(33) != 255) break;
	}
	imshowv("Res", bg);
	imwrite("bg.jpg", bg);
	waitKey(0);
	return 0;
}
