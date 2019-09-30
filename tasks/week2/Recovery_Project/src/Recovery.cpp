#include<iostream>
#include "../include/Recovery.h"
#include<chrono>
#include<sys/stat.h>

using namespace std;
using namespace cv;
using namespace chrono;

void Recovery::readVideo(string filePath) {
	test_video.open(filePath);
	if (!test_video.isOpened())
	{
		cout << "can't open video" << endl;
	}
	count = 0;
	Mat temp, image;
	while (1) {
		test_video >> temp;
		if (temp.empty()) {
			break;
		}
		image = temp.clone();
		video_shot_arr.push_back(image);
		count++;
	}
}


void  Recovery::process() {
	auto start = system_clock::now();
	Mat temp, paste_photo, paste_grey , image;
	int random_num = 0;
	int tempc = count;


	Mat near1 = video_shot_arr[count / 2].clone(), near2 = video_shot_arr[count / 2 - 1].clone();
	Mat near1_grey, near2_grey;
	Mat neardiff;
	cvtColor(near1, near1_grey, COLOR_BGR2GRAY);
	cvtColor(near2, near2_grey, COLOR_BGR2GRAY);
	absdiff(near1_grey, near2_grey, neardiff);

	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	erode(neardiff, neardiff, element);
	vector<vector<Point>> nearco;
	vector<Vec4i>hierarchy;
	findContours(neardiff, nearco, hierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_NONE);
	if (tempc < 100) random_num = 4;
	vector<Rect> bounds(nearco.size());
	vector<Rect> my_rect;
	if (tempc > 200 && tempc < 300) random_num = 210;
	for (int i = 0; i < nearco.size(); i++) {
		if (boundingRect(nearco[i]).area() > 2000)
		{
			my_rect.push_back(boundingRect(nearco[i]));
		}
	}

	paste_photo = video_shot_arr[random_num].clone();
	cvtColor(paste_photo, paste_grey, COLOR_BGR2GRAY);

	while (random_num < count) {
		if (my_rect.size() > 1 )
		{
			break;
		}
		else if (my_rect.size() == 1 && tempc < 300)
		{
			Mat temp_diff1, temp_diff2;
			absdiff(paste_grey, near1_grey, temp_diff1);
			absdiff(paste_grey, near2_grey, temp_diff2);

			vector<vector<Point>> temp_co;
			vector<Vec4i>temp_hi;
			vector<Rect> temp_rect;
			findContours(paste_grey, temp_co, temp_hi, CV_RETR_EXTERNAL, CHAIN_APPROX_NONE);
			int index, amax = 0, imax = -1;
			for (index = 0; index < temp_co.size(); index++)
			{
				if (boundingRect(temp_co[index]).area() > 2000)
				{
					temp_rect.push_back(boundingRect(temp_co[index]));
				}
			}
			if (temp_rect.size() == 2 )
			{
				break;
			}
		}
		random_num++;
	}	
	if (my_rect.size() == 3) {
		paste_photo(my_rect[0]).copyTo(near2(my_rect[0]));
	}
	for (int i = 0; i < my_rect.size(); i++)
	{
		paste_photo(my_rect[i]).copyTo(near2(my_rect[i]));
	}
	
	result = near2;
	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "花费了"
		<< double(duration.count()) * 
			microseconds::period::num / microseconds::period::den
		<< "秒" << endl;
	waitKey(0);
	return ;
}

void  Recovery::showResult() {
	imwrite("./result/out.jpg",result);
	namedWindow("result", 0);
	imshow("result", result);
	waitKey(0);
	return;
}
