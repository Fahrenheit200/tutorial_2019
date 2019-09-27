#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <chrono>
using namespace cv;
using namespace std;
void onMouse(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		cout << "(" << x << "," << y << ")" << endl;
	}
}
Mat toView(Mat ori)
{
	Mat res;
	resize(ori, res, Size(800, 800 * ori.rows / ori.cols));
	return res;
}
void imshowv(const char* name, Mat img)
{
	imshow(name, toView(img));
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

float rate = 0.1;
int main(int argc, char* argv[])
{
	VideoCapture cap(argv[1]);
	Mat frame, gray;
	Mat tmp, mius, sigmas, omigas, mask;
	auto start = chrono::steady_clock::now();
	int fcnt = cap.get(CAP_PROP_FRAME_COUNT);
	rate = 0.1;
	while (1)
	{
		cap >> frame;
		if (frame.empty()) break;
		auto st = chrono::steady_clock::now();
		if (rate > 0.01) rate *= 0.95;
		cvtColor(frame, gray, CV_BGR2GRAY);
		// cout << frame.rows() << ' ' << frame.cols() << endl;
		if (mius.empty())
		{
			sigmas.create(gray.size(), CV_32FC3);
			omigas.create(gray.size(), CV_32FC3);
			mius.create(gray.size(), CV_32FC3);
			mask.create(gray.size(), CV_8U);
			mius = Scalar(43.5, 127.5, 213);
			sigmas = Scalar(1, 1, 1);
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
						o = (i == bst ? (1 - rate) : rate) * o;
						//if (o < 1e-15) o = 1e-15;
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
				if ((*ito)[bst] < 0.2)
				{
					*itm = 0;
				}
				else *itm = 255;
			}

		}
		cout << (int)gray.at<uchar>(220, 462) << endl 
		<< mius.at<Vec3f>(220, 462) << endl << sigmas.at<Vec3f>(220, 462) << endl
		<< omigas.at<Vec3f>(220, 462) << endl << endl;
		//imshowv("Gray", gray);
		//imshowv("Mask", mask);
		auto edd = chrono::steady_clock::now();
		cout << "Time Consume: " << chrono::duration_cast<chrono::milliseconds>(edd - st).count() / 1000.0 << "s" << endl;
		//waitKey(0);
		//if (waitKey(33) != 255) break;
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
