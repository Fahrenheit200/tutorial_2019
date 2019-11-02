#include "canny.h"

int main(int argc, char* argv[]) {
	Mat img = imread(argv[1]);
	Mat grey;
	cvtColor(img, grey, CV_BGR2GRAY);
	Mat blur;
	GaussianBlur(grey, blur, Size(5, 5), 1, 1);
	Mat outputImg;
	myCanny(blur, outputImg, 60, 120);
	namedWindow("myCanny");
	imshow("myCanny", outputImg);
	waitKey(1000);

	//findContours & drawContours
	Mat binary;
	threshold(blur, binary, 128, 255, CV_THRESH_BINARY);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	Mat edge = Mat::zeros(binary.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++) {
		drawContours(edge, contours, i, Scalar(255, 255, 255), 1, 8, hierarchy);
	}
	namedWindow("findContours");
	imshow("findContours", edge);
	waitKey(1000);
	return 0;
}
