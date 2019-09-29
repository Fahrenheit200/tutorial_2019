#pragma once
#include<iostream>
#include<string>
#include<map>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define P_IDX 0
#define Q_IDX 1
#define R_IDX 2

#define PQ_CNT 0
#define QR_CNT 1
#define PR_CNT 2

using namespace std;
using namespace cv;
struct pairIdx {
	int q;
	int r;
};
class Recovery {
public:
	void readVideo(string filePath);
	void process();
	void showResult();
private:
	void saveResult(string filePath);
	void subprocess();
	void diff(int, int, int);
	void chooseRect(int);
	void expandRect(Rect&);
	void patcha(Rect, int, int);
	bool indexTheSame(int, int, int);
	bool rectOverclapOrVoid();
	bool tooSmalltooClose();
	bool expandNotOverClap(int);
	bool qualityIsGood();
	int chooseTheBestOne();
	Rect findSimilar(int);
	Point getCenterPoint(Rect rect);
	VideoCapture cap;
	vector<Mat> store;
	vector<vector<Point>> cont[3];
	Rect whole;
	Rect areaRect[6];
	Rect singleRect[3];
	Mat finalpic;
	Mat prefinal;
	Mat finaldiff;
	Mat base;
	Mat diffStore[3];
	map<pairIdx, int> findIdx;
	string path;
	double ratio;
	int scale;
};
