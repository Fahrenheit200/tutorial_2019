/*****************************************************************************
* 
*  @file	Recovery.cpp
*  @brief	Recovery类实现
* 
*  @author	PumpkinJimmy
*  @email	996344439@qq.com
*  @version	v1.0.0
*  @date	2019-09-30
* 
*****************************************************************************/
#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include "Recovery.h"
using namespace cv;

double Recovery::gsVec(const Vec3b& x, Vec3f miu, float sga)
{
	Vec3f diff = Vec3f(x) - miu; 
	float tmp2 = exp(-0.5 * (diff[0] * diff[0] + diff[1] * diff[1] + diff[2] * diff[2]));
	double res = 1 / pow(2 * M_PI, 1.5) * 1 / (sga * sga * sga) * tmp2;
	return res;
}

void Recovery::startClock()
{
	start_tp = std::chrono::steady_clock::now();
}

float Recovery::endClock()
{
	using namespace std::chrono;
	auto tp = steady_clock::now();
	return duration_cast<milliseconds>(tp - start_tp).count() / 1000.0;
}

void Recovery::init()
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
	result.create(frame.size(), frame.type());
}

void Recovery::initIterators()
{
	itus.clear(); itas.clear(); itos.clear();
	for (int i = 0; i < 3; i++)
	{
		itus.push_back(mius[i].begin<Vec3f>());
		itas.push_back(sigmas[i].begin<float>());
		itos.push_back(omigas[i].begin<float>());
	}
}

void Recovery::moveIterators()
{
	for (int i = 0; i < 3; i++)
	{
		itus[i]++; itas[i]++; itos[i]++;
	}
}

int Recovery::getMatchModel(MatIterator_<Vec3b> it)
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
	return bst;
}

void Recovery::resetModel(MatIterator_<Vec3b> it)
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

void Recovery::updateModel(MatIterator_<Vec3b> it, int bst)
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

int Recovery::getBestModel()
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
	return bst;
}
void Recovery::readVideo(String filePath)
{
	cap.open(filePath);
}
void Recovery::process()
{
	startClock();
	fcnt = cap.get(CAP_PROP_FRAME_COUNT);
	int fid = 0;
	rate = 0.4;
	float mrate;
	if (fcnt <= 150) mrate = 1;
	else mrate = 0.98;
	while (1)
	{
		cap >> frame;
		if (frame.empty()) break;
		if (rate > 0.04) rate *= mrate;
		fid++;
		if (mius.empty()) //Initialize
		{
			init();
		}
		else if (fid <= 150)
		{
			MatIterator_<Vec3b> it = frame.begin<Vec3b>(), ited = frame.end<Vec3b>();
			initIterators();
			for (;it != ited; it++) // for each pixel
			{
				int bst = getMatchModel(it);
				if (bst == -1) //no matched model
				{
					resetModel(it);
				}
				else //matched, update omiga, miu, and sigma
				{
					updateModel(it, bst);
				}
				moveIterators();

			}
		}
		else break;
	}
	MatIterator_<Vec3b> itr = result.begin<Vec3b>(), ited = result.end<Vec3b>();
	initIterators();
	for (; itr != ited; itr++)
	{
		int bst = getBestModel();
		for (int i = 0; i < 3; i++)
		{
			(*itr)[i] = uchar((*itus[bst])[i] + 0.5);
		}
		moveIterators();
	}
	std::cout << "Process time: " << endClock() << "s" << std::endl;
	saveResult();
}

void Recovery::saveResult()
{
	imwrite("result/result.jpg", result);
}

void Recovery::showResult()
{
	imshow("Result", result);
	waitKey(0);
}

