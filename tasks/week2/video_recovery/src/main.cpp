#include <iostream>
#include "recovery.h"
#include <ctime>
using namespace std;
int main(int argc, char *argv[])
{
	clock_t start = clock();
	Recovery video;
	video.readVideo(argv[1]);
	video.process();
	video.showResult();
	clock_t end = clock();
	cout<<"time:"<<double(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
	return 0;
}

