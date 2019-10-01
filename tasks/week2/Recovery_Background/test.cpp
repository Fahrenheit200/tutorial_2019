#include "include/Recovery.h"
#include<iostream>

int main(int argc,char* argv[])
{  
	Recovery re;
	re.readVideo(argv[1]);
	auto start=system_clock::now();        //计时开始
	re.process();
	auto end=system_clock::now();          //计时结束 
	auto duration=duration_cast<microseconds>(end-start);
	cout<<"Process time: "<<double(duration.count())*microseconds::period::num/microseconds::period::den<<"s"<<endl;
	re.showResult();	
    return 0;
} 
