
#include "../include/Recovery.h"
#include<iostream>
//#include <opencv2\highgui\highgui.hpp> 
//#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <chrono> 
#include<sys/stat.h>

using namespace std;
using namespace cv;
using namespace chrono;

void Recovery::readVideo(string filePath)
{
	Mat temp, image, imageSource;
	count = 0;
	video.open(filePath);

	while (1)
	{
		video >> temp;
		if (temp.empty())
			break;
		count++;
		//cout << count << endl;
		image = temp.clone();
		store.push_back(image);
	}
}

void Recovery::process()
{
	auto start = system_clock::now();
	vector<Rect> ROIrect;

	Mat xl1, xl2, xl1_copy;
	xl1 = store[count / 2].clone();
	xl1_copy = xl1.clone();

	xl2 = store[count / 2 - 1].clone();

	cvtColor(xl1, xl1, COLOR_BGR2GRAY);
	cvtColor(xl2, xl2, COLOR_BGR2GRAY);

	Mat diff;
	absdiff(xl1, xl2, diff);

	int seed = 0; 
	if (count < 300) seed = 175;
	 
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	erode(diff, diff, element);

	vector<vector<Point>> xlcontours;
	vector<Vec4i>hierarchy;
	findContours(diff, xlcontours, hierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_NONE);
	vector<Rect> bounds(xlcontours.size());
	if (count < 200) seed = 4;


	int ai, mythreshold = 5000, counter = 0;
	for (ai = 0; ai < xlcontours.size(); ai++)
	{
		bounds[ai] = boundingRect(xlcontours[ai]);
		if (bounds[ai].area() > mythreshold)
		{
			ROIrect.push_back(bounds[ai]);
		}
	}
	Mat patch_pic = store[seed].clone();
	Mat patch_pic_copy = patch_pic;
	cvtColor(patch_pic, patch_pic, COLOR_BGR2GRAY);

	for (; seed < count; seed++)
	{
		if (ROIrect.size() == 1 )
		{
			Mat temp_diff1, temp_diff2;

			absdiff(patch_pic, xl1, temp_diff1);
			threshold(temp_diff1, temp_diff1, 20, 255, THRESH_BINARY);
			medianBlur(temp_diff1, temp_diff1, 5);

			absdiff(patch_pic, xl2, temp_diff2);
			threshold(temp_diff2, temp_diff2, 20, 255, THRESH_BINARY);
			medianBlur(temp_diff2, temp_diff2, 5);

			patch_pic = temp_diff1 | temp_diff2;

			threshold(patch_pic, patch_pic, 50, 255, THRESH_BINARY);
	
			vector<vector<Point>> pic_contours;
			vector<Vec4i>pic_hierarchy;
			findContours(patch_pic, pic_contours, pic_hierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_NONE);
			vector<Rect> blocks;
			int index, amax = 0, imax = -1;
			Rect temp;

			for (index = 0; index < pic_contours.size(); index++)
			{
				temp = boundingRect(pic_contours[index]);

				if (temp.area() > mythreshold)
				{
					blocks.push_back(temp);
				}
			}

			if (blocks.size() > 1)
			{
				break;
			}

		}


		else if (ROIrect.size() == 2 && mythreshold < 300)
		{

			Mat temp_diff1, temp_diff2;

			absdiff(patch_pic, xl1, temp_diff1);
			threshold(temp_diff1, temp_diff1, 10, 255, THRESH_BINARY);
			medianBlur(temp_diff1, temp_diff1, 9);

			absdiff(patch_pic, xl2, temp_diff2);
			threshold(temp_diff2, temp_diff2, 10, 255, THRESH_BINARY);
			medianBlur(temp_diff2, temp_diff2, 9);

			patch_pic = temp_diff1 | temp_diff2;

			vector<vector<Point>> pic_contours;
			vector<Vec4i>pic_hierarchy;
			findContours(patch_pic, pic_contours, pic_hierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_NONE);
			vector<Rect> blocks;
			int index, amax = 0, imax = -1;
			Rect temp;

			for (index = 0; index < pic_contours.size(); index++)
			{
				temp = boundingRect(pic_contours[index]);

				if (temp.area() > mythreshold)
				{
					blocks.push_back(temp);
				}
			}
			if (blocks.size() == 3)
			{
				break;
			}
		}

	}

	for (int i = 0; i < ROIrect.size(); i++)
	{
		patch_pic_copy(ROIrect[i]).copyTo(xl1_copy(ROIrect[i]));
	}

	output = xl1_copy.clone();

	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "run time:"
		<< double(duration.count()) * microseconds::period::num / microseconds::period::den << "秒" << endl;

}

void Recovery::showResult()
{
	imwrite("./result/out.jpg", output);
	namedWindow("result", WINDOW_NORMAL);
	imshow("result", output);
	waitKey(0);
}
