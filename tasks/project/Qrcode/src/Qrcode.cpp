#include "Qrcode.h"

Qrcode::Qrcode(string filePath)
{
	images.push_back(imread(filePath + "\\img_a.jpg"));
	images.push_back(imread(filePath + "\\img_b.jpg"));
	images.push_back(imread(filePath + "\\img_c.jpg"));
	images.push_back(imread(filePath + "\\img_d.jpg"));
	for (auto i : images)
		recognition(i);
}

void Qrcode::show()
{
	for (auto s : setions) {
		namedWindow("setions", 0);
		imshow("setions", s);
		waitKey(1000);
	}
}

void Qrcode::recognition(Mat& img)
{
	Mat cut = img(Rect(1000, 1000, 2000, 1200));
	Mat processed;
	cut.copyTo(processed);
	cvtColor(processed, processed, CV_BGR2GRAY);
	GaussianBlur(processed, processed, Size(5, 5), 1, 1);
	threshold(processed, processed, 180, 255, CV_THRESH_BINARY);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(processed, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

	sort(contours.begin(), contours.end(), [](const vector<Point> a, const vector<Point> b) { return a.size() > b.size(); });

 	int largestIndex = 0;
	int largestSize = 0;
	double borderX1 = 0;
	double borderX2 = 0;
	double borderY1 = 0;
	double borderY2 = 0;
	for (int i = 0; i < contours.size(); i++) {
		if (contours[i].size() < largestSize) continue;
		
		double x1 = (*min_element(contours[i].begin(), contours[i].end(), [](const Point& a, const Point& b) { return a.x < b.x; })).x;
		double x2 = (*max_element(contours[i].begin(), contours[i].end(), [](const Point& a, const Point& b) { return a.x < b.x; })).x;
		double y1 = (*min_element(contours[i].begin(), contours[i].end(), [](const Point& a, const Point& b) { return a.y < b.y; })).y;
		double y2 = (*max_element(contours[i].begin(), contours[i].end(), [](const Point& a, const Point& b) { return a.y < b.y; })).y;
		double rate = (x2 - x1) / (y2 - y1);   //长宽比
		if (rate > 1.2 || rate < 0.8) continue;	
		
		int black = 0;
		for (int m = y1; m < y2; m++)
			for (int n = x1; n < x2; n++)
				if (processed.at<uchar>(m, n) == 0)
					black++;

		int size = (x2 - x1) * (y2 - y1);
		if (black > 0.75 * size || black < 0.25 * size) continue;  //黑白比

		borderX1 = x1;
		borderX2 = x2;
		borderY1 = y1;
		borderY2 = y2;
		largestSize = contours[i].size();
		largestIndex = i;
		break;		
	}

	vector<vector<Point>> contours2;
	for (auto c : contours) {
		if (c.size() < 10) continue;
		RotatedRect r = minAreaRect(c);
		if (r.center.x > borderX1&& r.center.x < borderX2 && r.center.y > borderY1 && r.center.y < borderY2)
			contours2.push_back(c);
	}

	vector<Point> points;
	for (auto c : contours2)
		for (auto p : c)
			points.push_back(p);

	RotatedRect bigRect = minAreaRect(points);
	Mat setion = cut(Rect(bigRect.center.x - 0.5 * bigRect.size.height, bigRect.center.y - 0.5 * bigRect.size.width,
		bigRect.size.height, bigRect.size.width));
	setions.push_back(setion);
}
