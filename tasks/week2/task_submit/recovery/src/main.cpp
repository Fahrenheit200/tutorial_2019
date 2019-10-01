#include "Recovery.h"
#include <opencv2/opencv.hpp>

using namespace cv;
Recovery rec;
int main(int argc, char* argv[])
{
	rec.readVideo(argv[1]);
	rec.process();
	rec.showResult();
	waitKey(0);
	return 0;
}
