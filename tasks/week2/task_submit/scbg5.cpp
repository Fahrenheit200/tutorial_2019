/*
 GMM背景建模魔改版
 通过获取帧数适当调整学习率以减少长视频的噪点的同时加快短视频的收敛
 彩色版
*/
#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <chrono>
#include <map>
#include "recovery/include/timer.h"
using namespace cv;
using namespace std;
Timer timer;
typedef Vec3f Color;
float rate, mrate;
double prop;
Mat frame, gray;
Mat tmp, mask, ori;
vector<Mat> mius, sigmas, omigas;
void onMouse(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		int rx = x / prop, ry = y / prop;
		cout << "(" << rx << "," << ry << ")" << endl;
	}
}
void showPoint(int x, int y)
{
	int px = x * prop, py = y * prop;
	circle(frame, Point2i(px, py), 8, Scalar(255, 255, 255), 1);
	cout << endl;
	cout << "Color: " << frame.at<Vec3b>(y, x) << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "Miu" << char('1' + i) << ": " << mius[i].at<Vec3f>(y, x) << endl
		<< "Sigma" << char('1' + i) << ": " << sigmas[i].at<float>(y, x) << endl
		<< "Omiga" << char('1' + i) << ": " << omigas[i].at<float>(y, x) << endl;
	}
	cout << endl;
}
double imshowv(const char* name, Mat img)
{
	Mat res;
	double prop = 800.0 / img.cols;
	resize(img, res, Size(800, img.rows * prop));
	imshow(name, res);
	return prop;
}
float marDis(Vec3b x, Vec3f miu, float sga)
{
	Vec3f diff = Vec3f(x) - miu;
	Matx33f binv(1 / sga, 0, 0, 0, 1 / sga, 0, 0, 0, 1 / sga);
	return (diff.t() * binv * diff)[0];
}
inline double gsVec(const Vec3b& x, Vec3f miu, float sga)
{
	Vec3f diff = Vec3f(x) - miu; 
	float tmp2 = exp(-0.5 * (diff[0] * diff[0] + diff[1] * diff[1] + diff[2] * diff[2]));
	double res = 1 / pow(2 * M_PI, 1.5) * 1 / (sga * sga * sga) * tmp2;
	return res;
}
Mat gsMat(Mat x, Mat miu, Mat sga)
{
	Mat diff, tmp2;
	absdiff(x, miu, diff);
	exp(-0.5 * diff.mul(diff), tmp2);
	Mat detb = sga.mul(sga); detb = detb.mul(sga);
	return tmp2 / detb;
}
int main(int argc, char* argv[])
{
	VideoCapture cap(argv[1]);
	
	auto start = chrono::steady_clock::now();
	int fcnt = cap.get(CAP_PROP_FRAME_COUNT), fid = 0;
	rate = 0.4;
	if (fcnt <= 150) mrate = 1;
	else mrate = 0.98;
	while (1)
	{
		cap >> frame;
		if (frame.empty()) break;
		if (rate > 0.04) rate *= mrate;
		fid++;
		// pyrDown(frame, frame); pyrDown(frame, frame);
		auto st = chrono::steady_clock::now();
		if (mius.empty()) //Initialize
		{
			for (int i = 0; i < 3; i++)
			{
				mius.push_back(Mat(frame.size(), CV_32FC3));
				sigmas.push_back(Mat(frame.size(), CV_32F));
				sigmas[i] = 8;
				omigas.push_back(Mat(frame.size(), CV_32F));
				omigas[i] = 1.0 / 3;
			}
			mius[0] = Scalar::all(128); mius[1] = Scalar::all(128); mius[2] = Scalar::all(128);
			mask.create(frame.size(), CV_8U);
			mask = 255;
		}
		else if (fid <= 100)
		{
			
			auto it = frame.begin<Vec3b>();
			vector<MatIterator_<Vec3f>> itus; //a[n][p]
			vector<MatIterator_<float>> itos, itas;
			for (int i = 0; i < 3; i++)
			{
				itus.push_back(mius[i].begin<Vec3f>());
				itas.push_back(sigmas[i].begin<float>());
				itos.push_back(omigas[i].begin<float>());
			}
			auto itm = mask.begin<uchar>();
			auto ited = frame.end<Vec3b>();
			
			
			for (;it != ited; it++) // for each pixel
			{

				int bst = -1; double bstp = -1e8, p;
				for (int i = 0; i < 3; i++) //for each model
				{
					
					Vec3f x = *it, miu = *itus[i]; float sigma = *itas[i];
					Vec3f diff; absdiff(x, miu, diff); bool ok = true;
					if (diff[0] > 2.5 * sigma || diff[1] > 2.5 * sigma || diff[2] > 2.5 * sigma) continue;
					p = gsVec(x, miu, sigma);
					if (p  > bstp)
					{
						bst = i;
						bstp = p;
					}

				}
				
				if (bst == -1) //no matched model
				{
					int wrs = -1; float wrso = 1e5;
					for (int i = 0; i < 3; i++) //find worst model
					{
						if (*itos[i] < wrso)
						{
							wrs = i; wrso = *itos[i];
						}
					}
					float maxsig, minomi;
					if (wrs == 0)
					{
						maxsig = *itas[1] > *itas[2] ? *itas[1] : *itas[2];
						minomi = *itos[1] < *itos[2] ? *itos[1] : *itos[2];
					}
					if (wrs == 1)
					{
						maxsig = *itas[0] > *itas[2] ? *itas[0] : *itas[2];
						minomi = *itos[0] < *itos[2] ? *itos[0] : *itos[2];
					}
					else
					{
						maxsig = *itas[1] > *itas[0] ? *itas[1] : *itas[0];
						minomi = *itos[1] < *itos[0] ? *itos[1] : *itos[0];
					}
					*itus[wrs] = *it;
					*itas[wrs] = 2 * maxsig;
					*itos[wrs] = 0.5 * minomi;
					float osum = *itos[0] + *itos[1] + *itos[2];
					*itos[0] /= osum; *itos[1] /= osum; *itos[2] /= osum;
				}
				else //matched, update omiga, miu, and sigma
				{
					float ws = 0;
					for (int i = 0; i < 3; i++) //for each model
					{
						float& o = *itos[i];
						o = ((i == bst) ? 1 : (1 - rate)) * o;
						ws += o;
					}

					for (int i = 0; i < 3; i++)
					{
						*itos[i] /= ws;
					}
					float rou = (float)(rate * *itos[bst]);
					*itus[bst] = *itus[bst] * (1 - rou) + Vec3f(*it) * rou;
					Vec3f diff = Vec3f(*it) - *itus[bst];
					float sq = (diff.t() * diff)[0];
					*itas[bst] = sqrt(*itas[bst] * *itas[bst] * (1 - rou) + rou * sq);
				}
				
				for (int i = 0; i < 3; i++)
				{
					itus[i]++; itas[i]++; itos[i]++;
				}
				// MOVE ITERATORS!!!
			}
		}
		else
		{
			break;
			// mask = 255;
			// auto it = frame.begin<Vec3b>();
			// vector<MatIterator_<Vec3f>> itus; //a[n][p]
			// vector<MatIterator_<float>> itos, itas;
			// for (int i = 0; i < 3; i++)
			// {
			// 	itus.push_back(mius[i].begin<Vec3f>());
			// 	itas.push_back(sigmas[i].begin<float>());
			// 	itos.push_back(omigas[i].begin<float>());
			// }
			// auto itm = mask.begin<uchar>();
			// auto ited = frame.end<Vec3b>();
			// for (;it != ited; it++, itm++) // for each pixel
			// {
			// 	int bst = -1; double bstp = -1e10, dist;
			// 	for (int i = 0; i < 3; i++) //for each model
			// 	{
			// 		if (marDis(*it, *itus[i], *itas[i]) > 200) continue;
			// 		dist = gsVec(*it, *itus[i], *itas[i]);
			// 		if (dist  > bstp)
			// 		{
			// 			bst = i;
			// 			bstp = dist;
			// 		}
			// 	}
			// 	if (bst == -1 || *itos[bst] < 0.7) *itm = 0;
			// 	for (int i = 0; i < 3; i++)
			// 	{
			// 		itus[i]++; itas[i]++; itos[i]++;
			// 	}
			// }
			// dilate(mask, mask, 10);
			// dilate(mask, mask, 10);
			// imshowv("Mask", mask);
		}
		for (int i = 0; i < 3; i++)
		{
			char s[] = "Model1"; s[5] += i;
			prop = imshowv(s, omigas[i]);
			s[5] -= i;
		}
		// showPoint(440, 212);
		// imshowv("Video View", frame);
		auto edd = chrono::steady_clock::now();
		cout << "Time Consume: " << chrono::duration_cast<chrono::milliseconds>(edd - st).count() / 1000.0 << "s" << endl;
		if (waitKey(33) != 255) break;
	}
	auto ed = chrono::steady_clock::now();
	cout << "Time Consume: " << chrono::duration_cast<chrono::milliseconds>(ed - start).count() / 1000.0 << "s" << endl;
	Mat res(mask.size(), CV_8UC3);
	vector<MatIterator_<Vec3f>> itus; //a[n][p]
	vector<MatIterator_<float>> itos, itas;
	auto itr = res.begin<Vec3b>();
	for (int i = 0; i < 3; i++)
	{
		itus.push_back(mius[i].begin<Vec3f>());
		itas.push_back(sigmas[i].begin<float>());
		itos.push_back(omigas[i].begin<float>());
	}
	auto itm = mask.begin<uchar>();
	auto ited = res.end<Vec3b>();
	for (; itr != ited; itr++)
	{
		int bst = -1; float bstv = -1e8, v;
		for (int i = 0; i < 3; i++)
		{
			if (*itos[i] < 1e-5) continue;
			if (*itas[i] < 0.5)
			{
				bst = i;
				break;
			}
			v = *itos[i] / *itas[i];
			if (v > bstv)
			{
				bst = i; bstv = v;
			}
		}
		for (int i = 0; i < 3; i++)
		{
			(*itr)[i] = uchar((*itus[bst])[i] + 0.5);
		}
		for (int i = 0; i < 3; i++)
		{
			itus[i]++; itas[i]++; itos[i]++;
		}
	}
	namedWindow("Result");
	setMouseCallback("Result", onMouse);
	imwrite("bg.jpg", res);
	imshowv("Result", res);
	waitKey(0);

	return 0;
}
