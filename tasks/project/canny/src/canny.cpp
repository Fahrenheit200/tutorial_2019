#include "canny.h"

const double PI = 3.1415;

void gradient(Mat& inputImg, Mat& outputImg, double** directs)
{
	for (int i = 1; i < inputImg.rows-1; i++) {
		for (int j = 1; j < inputImg.cols-1; j++) {
			double pix00 = inputImg.at<uchar>(i - 1, j - 1);
			double pix01 = inputImg.at<uchar>(i - 1, j);
			double pix02 = inputImg.at<uchar>(i - 1, j + 1);
			double pix10 = inputImg.at<uchar>(i, j - 1);
			double pix12 = inputImg.at<uchar>(i, j + 1);
			double pix20 = inputImg.at<uchar>(i + 1, j - 1);
			double pix21 = inputImg.at<uchar>(i + 1, j);
			double pix22 = inputImg.at<uchar>(i + 1, j + 1);
			double gradX = pix02 + 2 * pix12 + pix22 - pix00 - 2 * pix10 - pix20;
			double gradY = pix00 + 2 * pix01 + pix02 - pix20 - 2 * pix21 - pix22;
			outputImg.at<uchar>(i, j) = (uchar)sqrt(gradX * gradX + gradY * gradY);
			if (gradX == 0)
				directs[i][j] = gradY > 0 ? 1 : -1 * PI / 2;
			else
				directs[i][j] = atan(gradY / gradX);
		}
	}
	convertScaleAbs(outputImg, outputImg);
}

void maxValue(Mat& inputImg, double** directs)
{	
	for (int i = 1; i < inputImg.rows - 1; i++) {
		for (int j = 1; j < inputImg.cols - 1; j++) {
			double pix00 = inputImg.at<uchar>(i - 1, j - 1);
			double pix01 = inputImg.at<uchar>(i - 1, j);
			double pix02 = inputImg.at<uchar>(i - 1, j + 1);
			double pix10 = inputImg.at<uchar>(i, j - 1);
			double pix11 = inputImg.at<uchar>(i, j);
			double pix12 = inputImg.at<uchar>(i, j + 1);
			double pix20 = inputImg.at<uchar>(i + 1, j - 1);
			double pix21 = inputImg.at<uchar>(i + 1, j);
			double pix22 = inputImg.at<uchar>(i + 1, j + 1);
			double p1 = 0;
			double p2 = 0;
			double direct;
			direct = directs[i][j];
			if (direct >= 0 && direct <= PI / 4) {
				p1 = pix12 + (pix02 - pix12) * tan(direct);
				p2 = pix10 + (pix20 - pix10) * tan(direct);
			}
			else if (direct > PI / 4 && direct <= PI / 2) {
				p1 = pix01 + (pix02 - pix01) * (1/tan(direct));
				p2 = pix21 + (pix20 - pix21) * (1/tan(direct));
			}
			else if (direct < 0 && direct >= -PI / 4) {
				p1 = pix12 + (pix22 - pix12) * tan(direct);
				p2 = pix10 + (pix00 - pix10) * tan(direct);
			}
			else if (direct < -PI / 4 && direct >= -PI / 2) {
				p1 = pix01 + (pix00 - pix01) * (1 / tan(direct));
				p2 = pix21 + (pix22 - pix21) * (1 / tan(direct));
			}

			if (pix11 < p1 || pix11 < p2) {
				inputImg.at<uchar>(i, j) = 0 ;
			}
		}
	}
}

void doubleThrehold(Mat& inputImg, double lowThrehold, double highThrehold)
{
	for (int i = 1; i < inputImg.rows - 1; i++) {
		for (int j = 1; j < inputImg.cols - 1; j++) {
			if (inputImg.at<uchar>(i, j) < lowThrehold)
				inputImg.at<uchar>(i, j) = 0;
			else if (inputImg.at<uchar>(i, j) > highThrehold)
				inputImg.at<uchar>(i, j) = 255;
		}
	}
}

void middlePixels(Mat& inputImg, double lowThrehold, double highThrehold)
{
	for (int i = 1; i < inputImg.rows - 1; i++) {
		for (int j = 1; j < inputImg.cols - 1; j++) {
			if (inputImg.at<uchar>(i, j) >= lowThrehold && inputImg.at<uchar>(i, j) <= highThrehold) {
				if (inputImg.at<uchar>(i - 1, j - 1) == 255 || inputImg.at<uchar>(i - 1, j) == 255
					|| inputImg.at<uchar>(i - 1, j + 1) == 255 || inputImg.at<uchar>(i, j - 1) == 255
					|| inputImg.at<uchar>(i, j + 1) == 255 || inputImg.at<uchar>(i + 1, j - 1) == 255
					|| inputImg.at<uchar>(i + 1, j) == 255 || inputImg.at<uchar>(i + 1, j + 1) == 255) {
					inputImg.at<uchar>(i, j) = 255;
					if (i > 1 && j > 1) {
						i--;
						j--;
					}
				}
				else {
					inputImg.at<uchar>(i, j) = 0;
				}
			}
		}
	}
}

void myCanny(Mat& inputImg, Mat& outputImg, double lowThrehold, double highThrehold)
{
	double** directs = new double* [inputImg.rows];
	for (int i = 0; i < inputImg.rows; i++)
		directs[i] = new double[inputImg.cols];
	outputImg = Mat::zeros(inputImg.size(), CV_8UC1);
	for (int i = 0; i < outputImg.rows; i++) {
		for (int j = 0; j < outputImg.cols; j++) {
			outputImg.at<uchar>(i, j) = 0;
		}
	}
	gradient(inputImg, outputImg, directs);
	maxValue(outputImg, directs);
	doubleThrehold(outputImg, lowThrehold, highThrehold);
	middlePixels(outputImg, lowThrehold, highThrehold);
}


