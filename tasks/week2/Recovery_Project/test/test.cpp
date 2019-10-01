#include<opencv2/opencv.hpp>
#include<iostream>
#include <chrono> 
#include<string>
#include"../include/Recovery.h"
using namespace std;
using namespace cv;
using namespace chrono;

int main(int argc,char**argv) {
	Recovery test;
	test.readVideo(argv[1]);
	test.process();
	test.showResult();
}
