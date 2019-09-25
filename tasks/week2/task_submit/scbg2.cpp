#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;
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
double gs(int x, double miu, double sigma)
{
	return 1.0 / sqrt(2 * M_PI) * exp(-(x - miu) * (x - miu) / sigma / sigma);
}
float rate = 0.1;
int main(int argc, char* argv[])
{
	VideoCapture cap(argv[1]);
	Mat frame, gray;
	Mat mius, sigmas, tmp;
	while (1)
	{
		cap >> frame;
		if (frame.empty()) break;
		cvtColor(frame, gray, CV_BGR2GRAY);
		if (mius.empty())
		{
			gray.copyTo(mius);
			sigmas.create(gray.size(), gray.type());
			sigmas = Scalar(128);
		}
		else
		{
			addWeighted(gray, rate, mius, 1 - rate, 0, mius);
			tmp = gray - mius;
			tmp = tmp.mul(tmp);
			addWeighted(tmp, rate, sigmas, 1 - rate, 0, sigmas);
		}
		imshowv("Gray", gray);
		imshowv("Mius", mius);
		if (waitKey(33) != 255) break;
	}
	imshowv("Mius", mius);
	waitKey(0);
	return 0;
}
