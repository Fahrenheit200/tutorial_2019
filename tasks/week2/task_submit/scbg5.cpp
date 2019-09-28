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
using namespace cv;
using namespace std;
typedef Vec3f Color;
float rate = 0.1;
double prop;
Mat frame, gray;
Mat tmp, mask, ori;
vector<Mat> mius, sigmas, omigas;
void showPoint(int x, int y);
double imshowv(const char* name, Mat img)
{
	Mat res;
	double prop = 800.0 / img.cols;
	resize(img, res, Size(800, img.rows * prop));
	imshow(name, res);
	return prop;
}
double gsVec(const Vec3b& x, Vec3f miu, float sga)
{
	static double c1 = 1 / pow(2 * M_PI, 1.5);
	float detb = 1 / (sga * sga * sga);
	Vec3f diff = Vec3f(x) - miu;
	Matx33f binv(1 / sga, 0, 0, 0, 1 / sga, 0, 0, 0, 1 / sga);
	float tmp1 = (diff.t() * binv * diff)[0];
	float tmp2 = exp(-0.5 * tmp1);
	double res = c1 * detb * tmp2;
	return res;
}
int main(int argc, char* argv[])
{
	VideoCapture cap(argv[1]);
	
	auto start = chrono::steady_clock::now();
	int fcnt = cap.get(CAP_PROP_FRAME_COUNT);
	rate = 8.0 / fcnt;
	while (1)
	{
		cap >> frame;
		if (frame.empty()) break;
		auto st = chrono::steady_clock::now();
		if (mius.empty()) //Initialize
		{
			for (int i = 0; i < 3; i++)
			{
				mius.push_back(Mat(frame.size(), CV_32FC3));
				sigmas.push_back(Mat(frame.size(), CV_32F));
				sigmas[i] = 20;
				omigas.push_back(Mat(frame.size(), CV_32F));
				omigas[i] = 1.0 / 3;
			}
			mius[0] = Scalar::all(43.5); mius[1] = Scalar::all(127.5); mius[2] = Scalar::all(213);
			mask.create(frame.size(), CV_8U);
			mask = 255;
		}
		else
		{
			mask = 255;
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
			for (;it != ited; it++, itm++) // for each pixel
			{
				int bst = -1; double bstp = -1e8, p;
				for (int i = 0; i < 3; i++) //for each model
				{
					Vec3f diff; absdiff(*it, *itus[i], diff); bool ok = true;
					for (int j = 0; j < 3; j++) // for each component
					{
						if (isnan(*itas[i]) || isinf(*itas[i])) cout << "ahaha" << endl;
						if (diff[j] > *itas[i] * 2.5) { ok = false; break; }
					}
					if (!ok) continue;
					else
					{
						p = gsVec(*it, *itus[i], *itas[i]);
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
		//imshowv("Video View", frame);
		auto edd = chrono::steady_clock::now();
		cout << "Time Consume: " << chrono::duration_cast<chrono::milliseconds>(edd - st).count() / 1000.0 << "s" << endl;
		if (waitKey(33) != 255) break;
	}
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
	auto ed = chrono::steady_clock::now();
	cout << "Time Consume: " << chrono::duration_cast<chrono::milliseconds>(ed - start).count() / 1000.0 << "s" << endl;
	namedWindow("Result");
	imwrite("bg.jpg", res);
	imshowv("Result", res);
	waitKey(0);

	return 0;
}
