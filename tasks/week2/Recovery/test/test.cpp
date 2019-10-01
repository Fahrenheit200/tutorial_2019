#include<iostream>
#include"../include/Recovery.h"
#include<string>
//#include".../src/Recovery.cpp"


using namespace std;
using namespace cv;
int main(int argc,char** argv)
{
	Recovery r;
	string path=argv[1];
	r.readVideo(path);
	r.process();
	r.showResult();
	return 0;
}
