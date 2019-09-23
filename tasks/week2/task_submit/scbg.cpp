#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
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
int main(int argc, char* argv[])
{
	VideoCapture cap(argv[1]);
	Mat frame, frame_gray, frame_last, frame_diff, frame_diff2, frame_m;
	float rate = 0.7;
	while (1)
	{
		cap >> frame;
		if (frame.empty()) break;
		//imshow("Origin", frame);
		imshowv("View", frame);
		cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
		//imshowv("Gray", frame_gray);
		if (frame_last.empty()) frame_gray.copyTo(frame_last);
		absdiff(frame_gray, frame_last, frame_diff2);
		frame_gray.copyTo(frame_last);
		frame.convertTo(frame, CV_32FC3, 1.0/255);
		if (frame_m.empty())
		{
			frame.copyTo(frame_m);
		}
		medianBlur(frame_diff2, frame_diff2, 11);
		threshold(frame_diff2, frame_diff2, 10, 255, THRESH_BINARY);
		dilate(frame_diff2, frame_diff2, Mat());
		dilate(frame_diff2, frame_diff2, Mat());
		imshowv("Diff", frame_diff2);
		std::vector<std::vector<Point>> contours;
		findContours(frame_diff2, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
		Mat mask(frame_diff2.size(), CV_8U, Scalar(255));
		Mat con = mask.clone();
		for (auto it = contours.begin(); it != contours.end();)
		{
			if (it->size() < 400)
			{
				it = contours.erase(it);
			}
			else it++;
		}
		//std::cout << contours.size() << std::endl;
		drawContours(mask, contours, -1, 0, -1);
		drawContours(con, contours, -1, 0, 2);
		imshowv("Contours", con);
		imshowv("Mask", mask);
		bitwise_not(frame_diff2, frame_diff2);
		if (contours.size() > 0) accumulateWeighted(frame, frame_m, rate, mask);
		if (rate > 0.2) rate *= 0.9;
		imshowv("Masked", frame_m);
		if (contours.size() > 3) waitKey(0);
		if (waitKey(33) >= 0) break;
	}

	imshowv("Result", frame_m);
	waitKey(0);
	frame_m.convertTo(frame_m, CV_8UC3, 255);
	imwrite("bg.jpg", frame_m);
	return 0;
}
