#include"recovery.h"
/*#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>*/
using namespace std;
using namespace cv;
Recovery re;
int main(int argc,char** argv)
{
 re.readVideo(argv[1]);
 re. process();
 return 0;
}
