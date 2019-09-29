#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include "Recovery.h"
using namespace cv;
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
void Recovery::readVideo(String filePath)
{
	cap.open(filePath);
}

void Recovery::process()
{
	startClock();

	std::cout << endClock() << "s" << std::endl;
}

void Recovery::showResult()
{
}
