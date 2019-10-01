#include "Recovery.h"

void Recovery::readVideo(string filePath){
	VideoCapture capture(filePath);
	count = capture.get(CV_CAP_PROP_FRAME_COUNT);
	rows = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	cols = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	while (1) {
		Mat frame;
		capture >> frame;
		if (frame.empty()) break;
		frames.push_back(frame);	
	}
}

void Recovery::process() {
	auto start = system_clock::now();
	Mat frame0 = frames[count/2];

	int** pixels = new int*[rows];
	for (int i = 0; i < rows; i++) 
		pixels[i] = new int[3 * cols];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < 3 * cols; j++)
			pixels[i][j] = 0;
	for(auto f : frames) 
		for (int i = 0; i < rows; i++) {
			uchar *data0 = frame0.ptr<uchar>(i);
			uchar *data = f.ptr<uchar>(i);
			for (int j = 0; j < 3 * cols; j++) {
				if (abs(data0[j] - data[j]) < 15)
					pixels[i][j]++;
			}
		}

	vector<pair<int, int>> points;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < 3 * cols; j++)
			if (pixels[i][j] < count - pixels[i][j])
				points.push_back(pair<int, int>(i, j));

	for (int i = 0; i < rows; i++)
		delete[] pixels[i];
	delete pixels;

	int seek = 10  < frames.size() ? 10 : frames.size();
	int size = points.size();
	int *diffs = new int[seek];
	for (int p = 0; p < seek; p++) {
		int diff = 0;
		for (int i = 0; i < size; i++) {
			uchar *data = frames[p].ptr<uchar>(points[i].first);
			uchar *data0 = frame0.ptr<uchar>(points[i].first);
			diff += abs(data[points[i].second]- data[points[i].second]);
		}
		diffs[p] = diff;
	}	

	int index = max_element(diffs, diffs + seek) - diffs;
	delete[] diffs;

	for (int i = 0; i < size; i++) {
		uchar *data0 = frame0.ptr<uchar>(points[i].first);
		uchar *data = frames[index].ptr<uchar>(points[i].first);
		data0[points[i].second] = data[points[i].second];
	}
	frame0.copyTo(background);
	imwrite("../result/background.jpg", background);
	auto stop = system_clock::now();
	duration = duration_cast<milliseconds>(stop - start);
}

void Recovery::showResult() {
	cout << "Process time: " << double(duration.count()) / 1000.0 << 's' << endl;
	namedWindow("background", 0);
	imshow("background", background);
	waitKey(2000);
}
