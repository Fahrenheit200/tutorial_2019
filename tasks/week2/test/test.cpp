#include"Recovery.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<string>
using namespace std;
int main(int argc,char **argv)
{
    Recovery a;
    a.readVideo(argv[1]);
    a.process();
    a.showResult();
}


