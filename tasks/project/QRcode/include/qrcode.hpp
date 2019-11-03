#ifndef QRCODE_H
#define QRCODE_H

#include "opencv2/opencv.hpp"
#include <vector>
#include <string>

using namespace std;
using namespace cv;

void QRcode_section_detect(Mat &input, Mat output[]);
Mat QRcode_section_splice(Mat input[]);

#endif
