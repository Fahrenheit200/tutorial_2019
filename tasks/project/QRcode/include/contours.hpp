#ifndef CONTOURS_H
#define CONTOURS_H

#include <iostream>
#include <string>

#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;
const string result_window = "result";
const string result_filename = ".\\result.jpg";
const int max_threshold = 255;
extern int lower, upper;

Mat std_contours(Mat src, int lower_threshold, int upper_threshold);
Mat custom_contours(Mat src, int lower_threshold, int upper_threshold);
void threshold_callback(int, void*);
void contour_compare(string filename);
#endif