#include<iostream>
#include"Recovery.h"
using namespace std;

int main(int argc, char **argv)
{
	Recovery myRecovery;
	cout << "正在处理中，请耐心等待..." << endl;
	myRecovery.readVideo(argv[1]);
	myRecovery.process();
	myRecovery.showResult();
	return 0;
}
