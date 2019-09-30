#include <string>
#include <iostream>
#include <boost/timer.hpp>
#include <opencv2/opencv.hpp>
#include "../include/Recovery.hpp"

using namespace std;
using namespace cv;

/* test */
int main()
{
    Recovery recovery;
    recovery.getPath();
    boost::timer t;
    recovery.process();
    cout << "Time of process: " << t.elapsed() << "s" << endl;
    recovery.showResult();

    return 0;
}

/* Get the path */
void Recovery::getPath(){
    cout << "Please enter the path of the video: ";
    cin >> filePath;
}

/* Load the video */
VideoCapture Recovery::readVideo(string filePath){
    VideoCapture video = VideoCapture(filePath);
    if (!video.isOpened()) {
        cout << "could not load video file ..." << endl;
        return -1;
    }
    else
        return video;
}

/* Get the background */
void Recovery::process(){
    video = readVideo(filePath);

     // Get the avr image
     while(video.read(img0))
    {
        if(n == 1)
        {            
            img0.convertTo(sum1, CV_32FC3);
            height = img0.rows;
            width = img0.cols;
        }
        else
        {
            img0.convertTo(img0, CV_32FC3);          
            sum1 = sum1 + img0;
        }    

        n++;    
    }  

    avg = sum1 / n;
    avg.convertTo(avg, CV_8UC3);

    // Get the avr mid sample
    Rect rect1(width/2-range*2, 0, range*2, height); 
    img1 = avg(rect1);
    cvtColor(img1, img1, COLOR_BGR2GRAY);
    threshold(img1, img1, thr1, thr2, CV_THRESH_BINARY);//thr1-10
    meanStdDev(img1, mat1_mean, mat_stddev); 

    // Rect to get the left part and right peat
    Rect rect_left(0, 0, width/2, height);
    avg_left = avg(rect_left);  
    Rect rect_right(width/2, 0, width/2, height);
    avg_right = avg(rect_right);

    video1 = readVideo(filePath);

    while(video1.read(img0))
    {
        // Get the diff of the now and avg middle sample
        img2 = img0(rect1);
        cvtColor(img2, img2, COLOR_BGR2GRAY);
        threshold(img2, img2, thr1, thr2, CV_THRESH_BINARY);
        bitwise_xor(img1, img2, img3);
        meanStdDev(img3, mat2_mean, mat_stddev);

        if(mat2_mean.at<double>(0, 0) > 40) // If the cover is in the middle, abandon this frame
        {
            continue;
        }
        else // Estimate the cover is on the left side or on the right side
        {
            Mat now_left_mean;
            Mat now_right_mean;

            Mat now_left_diff_abs;
            Mat now_right_diff_abs;

            Mat now_left_gray;
            Mat now_right_gray;
            
            Mat now_left = img0(rect_left);
            Mat now_right = img0(rect_right);

            bitwise_xor(avg_left, now_left, now_left_gray);
            bitwise_xor(avg_right, now_right, now_right_gray);

            cvtColor(now_left_gray, now_left_gray, COLOR_BGR2GRAY);
            meanStdDev(now_left_gray, now_left_mean, mat_stddev);

            cvtColor(now_right_gray, now_right_gray, COLOR_BGR2GRAY);
            meanStdDev(now_right_gray, now_right_mean, mat_stddev);

            if(left_get && right_get)
            {
                break;
            }
            
            // Get the left part of the result
            if((now_left_mean.at<double>(0, 0) < 80) && (!left_get))//vdo1 2:40
            {                    
                left_part = now_left.clone();
                left_get = true;
            }                          
            
            // Get the right part of the result
            if((now_right_mean.at<double>(0, 0) > 60) && (!right_get))
            {
                if(now_right_mean.at<double>(0, 0) < 80) //vdo1 2 :40
                { 
                    right_part = now_right.clone();
                    right_get = true;
                }
            }
            else if((now_right_mean.at<double>(0, 0) < 40) && (!right_get))
            { 
                right_part = now_right.clone();
                right_get = true;
            }                          
        }    
    }

    hconcat(left_part, right_part, result); // Combine the left side and right side
  
    video.release();
    video1.release();
}

/* Show and save the result */
void Recovery::showResult(){
    imwrite("./result/New_Result.jpg" , result); 
    imshow("Result", result);
    waitKey(0);    
}