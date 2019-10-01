#include<chrono>
#include<iostream>
#include<fstream>
#include<string>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Recovery.h"

using namespace std;
using namespace std::chrono;
using namespace cv;
int main(int argc,char *argv[]) {
	string path;
	string filename;
	ofstream fout;
	path=argv[1];
	//path = "/home/adam/tutorial_2019/tasks/week2/resource/video0.mp4";
	//filename = "/home/adam/adam-gallas/recovery/result-00.jpg";
	filename = "./result/recoveredPicture0.jpg";
	filename[25]=path[16];
	//fout.open("D:/opencv-exercise/testAgain/video2/result.txt");
	Recovery t;
	auto start = steady_clock::now();
	t.readVideo(path);
	t.process();
	//t.saveResult(filename);
	auto end = steady_clock::now();
	auto timeUsed = duration_cast<microseconds>(end - start) / 1e6;
	cout << "Process time: " << timeUsed.count() <<"s"<< endl;
	t.showResult();
	/*
	for (int i = 0; i < 100; i++) {
		filename[43] = char(i % 10 + '0');
		filename[42] = char(i / 10 + '0');
		Recovery t;
		auto start = steady_clock::now();
		t.readVideo(path);
		t.process();
		t.saveResult(filename);
		auto end = steady_clock::now();
		auto timeUsed = duration_cast<microseconds>(end - start) / 1e6;
		fout << "trial " << i << " time: " << timeUsed.count() << endl;
	}
	*/
	/*
	path = "D:/opencv-exercise/video1.mp4";
	filename = "D:/opencv-exercise/video1/trial-00.jpg";
	fout.open("D:/opencv-exercise/video1/result.txt");
	for (int i = 0; i < 100; i++) {
		filename[33] = char(i % 10 + '0');
		filename[32] = char(i / 10 + '0');
		Recovery t;
		auto start = steady_clock::now();
		t.readVideo(path);
		t.process();
		t.saveResult(filename);
		auto end = steady_clock::now();
		auto timeUsed = duration_cast<microseconds>(end - start) / 1e6;
		fout << "trial " << i << " time: " << timeUsed.count() << endl;
	}
	path = "D:/opencv-exercise/video2.mp4";
	filename = "D:/opencv-exercise/video2/trial-00.jpg";
	fout.open("D:/opencv-exercise/video2/result.txt");
	for (int i = 0; i < 100; i++) {
		filename[33] = char(i % 10 + '0');
		filename[32] = char(i / 10 + '0');
		Recovery t;
		auto start = steady_clock::now();
		t.readVideo(path);
		t.process();
		t.saveResult(filename);
		auto end = steady_clock::now();
		auto timeUsed = duration_cast<microseconds>(end - start) / 1e6;
		fout << "trial " << i << " time: " << timeUsed.count() << endl;
	}
	*/
	return 0;
}
