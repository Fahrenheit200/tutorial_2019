#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Recovery{

public:

    /* Get the path */
    void getPath();

    /* Load the video */
    VideoCapture readVideo(string filePath);

    /* Get the background */
    void process();

    /* Show and save the result */
    void showResult();

private:
    VideoCapture video, video1; // The video
    string filePath; // The path of the video
    Mat sum1; // The number of the frames
	Mat avg; // The avg image of all the frames
    Mat img0, img1, img2, img3; // Intermediate variable
    Mat mat1_mean, mat2_mean, mat_stddev; // The mean of all the gray pixels
    Mat avg_left, avg_right; // The left and right part of the avg image
    Mat avg_left_mean, avg_right_mean; // The mean of the pixels of the left part and right part
    Mat left_part, right_part; // The left part and right part of the result 
    Mat result; // The result
    int n = 1; // The number of the frames
    int height, width; // The height and width of the image
    int range = 80; // The width of the middle sample
    bool left_get = false, right_get = false; // If have got the left part or right part
    int thr1 = 50, thr2 = 240; // The threshold value of binaryzation
};