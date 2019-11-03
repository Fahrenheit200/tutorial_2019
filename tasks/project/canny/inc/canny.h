#ifndef _CANNY_H_
#define _CANNY_H_

#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void gradient(Mat& inputImg, Mat& outputImg, double** directs);
void maxValue(Mat& inputImg, double** directs);
void doubleThrehold(Mat& inputImg, double lowThrehold, double highThrehold);
void middlePixels(Mat& inputImg, double lowThrehold, double highThrehold);
void myCanny(Mat& inputImg, Mat& outputImg, double lowThrehold, double highThrehold);

#endif

