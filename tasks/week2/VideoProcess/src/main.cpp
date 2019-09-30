#include "Recovery.h"
#include <chrono>
using namespace chrono;


int main(int argc, char** argv)
{
	if(argc != 2)
    {
        return -1;
    }
	Recovery r;
	r.readVideo(argv[1]);
	auto start = system_clock::now();
	r.process();
	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
cout <<  "花费了" 
     << double(duration.count()) * microseconds::period::num/microseconds::period::den 
     << "秒" << endl;
	r.showResult();
	return 0;
}


