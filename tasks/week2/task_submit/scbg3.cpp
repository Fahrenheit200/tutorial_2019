/*
 GMM背景建模魔改版
 通过非常暴力的降权，在前期将非背景部分模型直接降权到0，有效地快速收敛，但导致前期被长期遮挡的像素成为噪点。
*/
#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <chrono>
using namespace cv;
using namespace std;
float rate = 0.1;
double prop;
Mat frame, gray;
Mat tmp, mius, sigmas, omigas, mask;
void showPoint(int x, int y);
void onMouse(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		int rx = x / prop + 0.5, ry = y / prop + 0.5;
		cout << "(" << rx << "," << ry << ")" << endl;
		showPoint(ry, rx);
	}

}
Mat toView(Mat ori)
{
	Mat res;
	resize(ori, res, Size(800, 800 * ori.rows / ori.cols));
	return res;
}
double imshowv(const char* name, Mat img)
{
	Mat res;
	double prop = 800.0 / img.cols;
	resize(img, res, Size(800, img.rows * prop));
	imshow(name, toView(img));
	return prop;
}
double gs(int x, double miu, double sigma)
{
	if (sigma < 1e-10) return 1;
	return 1.0 / sqrt(2 * M_PI) / sigma * exp(-(x - miu) * (x - miu) / sigma / sigma / 2);
}
Mat gsMat(Mat x, Mat miu, Mat sigma)
{
	x.convertTo(x, CV_32F);
	Mat diff = x - miu, sqa_sigma = sigma.mul(sigma);
	Mat tmp = -diff.mul(diff) / sqa_sigma / 2;
	exp(tmp, tmp);
	Mat tmp2 = 1.0 / sqrt(2 * M_PI) / sigma;
	return tmp2.mul(tmp);
}

void showPoint(int x, int y)
{
	cout << int(gray.at<uchar>(y, x)) << endl
	<< mius.at<Vec3f>(y, x) << endl
	<< sigmas.at<Vec3f>(y, x) << endl
	<< omigas.at<Vec3f>(y, x) << endl;
}
int main(int argc, char* argv[])
{
	VideoCapture cap(argv[1]);
	
	auto start = chrono::steady_clock::now();
	int fcnt = cap.get(CAP_PROP_FRAME_COUNT);
	rate = 0.1;
	while (1)
	{
		cap >> frame;
		if (frame.empty()) break;
		auto st = chrono::steady_clock::now();
		//if (rate > 0.01) rate *= 0.95;
		cvtColor(frame, gray, CV_BGR2GRAY);
		if (mius.empty())
		{
			prop = 800.0 / frame.cols;
			sigmas.create(gray.size(), CV_32FC3);
			omigas.create(gray.size(), CV_32FC3);
			mius.create(gray.size(), CV_32FC3);
			mask.create(gray.size(), CV_8U);
			mius = Scalar(43.5, 127.5, 213);
			sigmas = Scalar(20, 20, 20);
			omigas = Scalar(1.0 / 3, 1.0 / 3, 1.0 / 3);
			mask = 255;
			gray.convertTo(gray, CV_32F);
		}
		else
		{
			mask = 255;
			auto itg = gray.begin<uchar>();
			auto it = mius.begin<Vec3f>();
			auto ita = sigmas.begin<Vec3f>();
			auto ito = omigas.begin<Vec3f>();
			auto itm = mask.begin<uchar>();
			auto ited = gray.end<uchar>();
			for (;itg != ited; itg++, it++, ita++, ito++, itm++) // for each pixel
			{
				int bst = -1; double bstp = -1e8, p;
				for (int i = 0; i < 3; i++) //select best model
				{
					if (abs(*itg - (*it)[i]) > 2.5 * (*ita)[i]) continue;
					else
					{
						p = gs(*itg, (*it)[i], (*ita)[i]);
						if (p  > bstp)
						{
							bst = i;
							bstp = p;
						}
					}
				}
				if (bst == -1) //no matched model
				{
					int wrs = -1; float wrso = 1e5;
					for (int i = 0; i < 3; i++) //find worst model
					{
						if ((*ito)[i] < wrso)
						{
							wrs = i; wrso = (*ito)[i];
						}
					}
					float maxsig, minomi;
					if (wrs == 0)
					{
						maxsig = (*ita)[1] > (*ita)[2] ? (*ita)[1] : (*ita)[2];
						minomi = (*ito)[1] < (*ito)[2] ? (*ito)[1] : (*ito)[2];
					}
					if (wrs == 1)
					{
						maxsig = (*ita)[0] > (*ita)[2] ? (*ita)[0] : (*ita)[2];
						minomi = (*ito)[0] < (*ito)[2] ? (*ito)[0] : (*ito)[2];
					}
					else
					{
						maxsig = (*ita)[1] > (*ita)[0] ? (*ita)[1] : (*ita)[0];
						minomi = (*ito)[1] < (*ito)[0] ? (*ito)[1] : (*ito)[0];
					}
					(*it)[wrs] = (*itg);
					(*ita)[wrs] = 2 * maxsig;
					(*ito)[wrs] = 0.5 * minomi;
					float osum = (*ito)[0] + (*ito)[1] + (*ito)[2];
					*ito /= osum;
				}
				else //matched, update omiga, miu, and sigma
				{
					float ws = 0;
					for (int i = 0; i < 3; i++)
					{
						float& o = (*ito)[i];
						o = (i == bst ? 1: (1 - rate)) * o;
						ws += o;
					}
					*ito /= ws;
					float rou = (float)(rate * (*ito)[bst]);
					(*it)[bst] = (1 - rou) * (*it)[bst] + rou * (*itg);
					(*ita)[bst] = sqrt(pow((1 - rou) * (*ita)[bst], 2) + pow(rou * (*itg - (*it)[bst]), 2));
				}
				bst = -1, bstp = -1e8;
				for (int i = 0; i < 3; i++) //find foreground
				{
					if (abs(*itg - (*it)[i]) > 2.5 * (*ita)[i]) continue;
					else
					{
						p = gs(*itg, (*it)[i], (*ita)[i]);
						if (p  > bstp)
						{
							bst = i;
							bstp = p;
						}
					}
				}
				*itm = (*ito)[bst] * 255;
			}
		}
		showPoint(889, 469);
		// threshold(mask, mask, 0.05 * 255, 255, CV_THRESH_BINARY);
		// medianBlur(mask, mask, 5);
		// dilate(mask, mask, 5);
		// medianBlur(mask, mask, 5);
		imshowv("Mask", mask);
		imshowv("Gray", gray);
		auto edd = chrono::steady_clock::now();
		cout << "Time Consume: " << chrono::duration_cast<chrono::milliseconds>(edd - st).count() / 1000.0 << "s" << endl;
		if (waitKey(33) != 255) break;
	}
    auto it = mius.begin<Vec3f>();
    auto ita = sigmas.begin<Vec3f>();
    auto ito = omigas.begin<Vec3f>();
	auto ited = mius.end<Vec3f>();
	Mat res(gray.size(), gray.type()), resm(gray.size(), gray.type());
	auto itr = res.begin<uchar>();
	auto itrm = resm.begin<uchar>();
	for (; it != ited; it++, ita++, ito++, itr++, itrm++)
	{
		int bst = -1; float bstv = -1e8, v;
		for (int i = 0; i < 3; i++)
		{
			if ((*ito)[i] < 1e-5) continue;
			if ((*ita)[i] < 0.5)
			{
				bst = i;
				break;
			}
			v = (*ito)[i] / (*ita)[i];
			if (v > bstv)
			{
				bst = i; bstv = v;
			}
		}
		*itr = (uchar)((*it)[bst] + 0.5);
		*itrm = (*ito)[bst] * 255;
	}
	auto ed = chrono::steady_clock::now();
	cout << "Time Consume: " << chrono::duration_cast<chrono::milliseconds>(ed - start).count() / 1000.0 << "s" << endl;
	namedWindow("Result");
	setMouseCallback("Result", onMouse);
	setMouseCallback("Resultm", onMouse);
	imwrite("bg.jpg", res);
	imshowv("Result", res);
	imshowv("Resultm", resm);
	waitKey(0);

	return 0;
}
