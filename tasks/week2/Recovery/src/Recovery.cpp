#include "../inc/Recovery.h"
#include "opencv2/opencv.hpp"  
#include <chrono>

using namespace std;
using namespace cv;

void Recovery::readVideo(string filePath) {
	cap.open(filePath);
	n_cols=(int)cap.get(3)*3;
	n_rows=(int)cap.get(4);
}

void Recovery::process() {
	auto start = chrono::steady_clock::now();

	Mat bkg(n_rows, n_cols / 3, CV_8UC3);

	cout<<n_rows<<"\n"<<n_cols<<endl;
	uchar*** ibkg = new uchar** [n_rows];
	for (int i = 0; i < n_rows; i++) {
                ibkg[i] = new uchar* [n_cols];
		for (int j = 0; j < n_cols; j++) {
                	ibkg[i][j] = new uchar [256];
        	}
        }

	for (int i = 0; i < n_rows; i++) {
                for (int j = 0; j < n_cols; j++) {
			for(int k=0;k<256;k++){
				ibkg[i][j][k]=0;	
			}
                }
        }

	for (int a = 0; a < 190 ; a++){
		Mat frame;
		if(!cap.read(frame)) break;
		countValue(frame, ibkg);
	}

	uchar* ptr;
	for (int i = 0; i < n_rows; ++i){
		ptr = bkg.ptr<uchar>(i);
		for (int j = 0; j < n_cols; ++j)
			ptr[j] = getLargest(ibkg[i][j]);
	}

	bg = bkg;
		
	for (int i = 0; i < n_rows; i++) {
               for (int j = 0; j < n_cols; j++) {
           		delete[] ibkg[i][j];
               }
	       delete[] ibkg[i];
        }
	delete[] ibkg;
	
	imwrite("1.png",bg);
	auto end = chrono::steady_clock::now();
	auto time=chrono::duration_cast<chrono::duration<double>>(end - start);
	cout << "Process time :" << time.count() <<"s"<< endl;
}

void Recovery::showResult() {
	imshow("背景", bg);
	waitKey(0);
}

void Recovery::countValue(Mat& src, uchar*** ibgk)
{
	for (int i = 0; i < n_rows; ++i){
		uchar* p = src.ptr<uchar>(i);
		for (int j = 0; j < n_cols; ++j)
			ibgk[i][j][p[j]]++;
	}
}

int Recovery::getLargest(uchar* arr){
	char laridx=0;
	uchar lar=arr[0];
	for(int i=1;i<256;i++){
		if(arr[i]>lar) {lar=arr[i]; laridx=i;}
	}
	return laridx;
}
