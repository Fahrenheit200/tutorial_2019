#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace cv;
using namespace std;
const int M=15;// max frame numbers
class Recovery
{
public:
    void readVideo(string);
    void process();
    void showResult();
public:
	int majorityElement(vector<int>);
    Mat images[M];// some of the frame in the video
    Mat ans;// result image
    int frame_num;// total frame
	int N;// the number of the frame being read
	vector<int> b,g,r;// b,g,r channels of Mat ans 
};
