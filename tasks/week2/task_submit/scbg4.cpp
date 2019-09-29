/*
 median method
 */
#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
using namespace cv;
using namespace std;
typedef Vec<uchar, 5> Vec5u;
Mat frame, gray, last, diff, mask, bgs, bg, bgtmp;
void onMouse(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		float prop = 800.0 / gray.cols;
		cout << "(" << int(x / prop + 0.5) << "," << int(y / prop + 0.5) << ")" << endl;
	}
}
void showPoint(int x, int y)
{
	float prop = 800.0 / gray.cols;
	int px = x * prop, py = y * prop;
	circle(gray, Point2i(px, py), 8, Scalar(255, 255, 255), 1);
}
inline void insert(Vec<uchar, 6>& v, int ed)
{
	uchar k = v[ed];
	int i = ed;
	for (;i > 0 && v[i - 1] > k;i--)
	{
		v[i] = v[i - 1];
	}
	v[i] = k;
}
uchar getMid(const Vec<uchar, 6>& vec)
{
	Vec<uchar, 6> v = vec;
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
float rate;
Mat avg, avgdiff;
struct PM
{
	Vec3f x;
	Vec3f mius[3];
	float sigs[3];
	float omis[3];
	PM(){ x = 2;for (int i = 0; i < 3; i++) {mius[i] = 0; sigs[i] = 1; omis[i] = 1.0 / 3;}}
};
Mat_<PM> m;
int main(int argc, char* argv[])
{
	VideoCapture cap(argv[1]);
	vector<Mat> imgs;
	int fcnt = cap.get(CAP_PROP_FRAME_COUNT);
	rate = 8.0 / fcnt;
	for (int i = 1; i <= 5; i++)
	{
		cap >> frame;
		cvtColor(frame, gray, CV_BGR2GRAY);
		imgs.push_back(gray.clone());
	}
	namedWindow("Gray");
	while (1)
	{
		cap >> frame;
		if (frame.empty()) break;
		if (bgtmp.empty())
		{
			bgtmp.create(gray.size(), gray.type());
			avg.create(gray.size(), CV_32F);
			avg = 0;
			m.create(gray.size());
			cout << m(1, 1).x[1] << endl;
			m(1, 1).x[2] = 3;
			cout << m(1, 1).x[2] << endl;
		}
		cvtColor(frame, gray, CV_BGR2GRAY);
		imgs.push_back(gray.clone());
		imgs.erase(imgs.begin());
		imgs.push_back(Mat(gray.size(), gray.type()));
		merge(imgs, bgs);
		bgs.forEach<Vec<uchar, 6>>([](Vec<uchar, 6>& item, const int position[]) -> void{
			item[5] = getMid(item);
		});
		split(bgs, imgs);
		imgs[5].copyTo(bgtmp);
		imgs.pop_back();
		if (bg.empty()) bg = bgtmp.clone();
		else addWeighted(bg, (1 - rate), bgtmp, rate, 0, bg);
		// bgtmp.convertTo(bgtmp, CV_32F);
		// avg += bgtmp;
		showPoint(1655, 2325);
		imshowv("Gray", gray);
		imshowv("Res", bg);
		imshowv("Median", bgtmp);
		if (waitKey(33) != 255) break;
	}
	setMouseCallback("Median", onMouse);
	imshowv("Res", bg);
	// imshowv("Res2", avg / (fcnt * 255.0));
	imwrite("bg_gray.jpg", bg);
	waitKey(0);
	return 0;
}
