#include "Recovery.h"

void Recovery::readVideo(string filePath)
{
	cap.open(filePath);
	rows = (int)cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	cols = (int)cap.get(CV_CAP_PROP_FRAME_WIDTH);
	sumFrames = (int)cap.get(CV_CAP_PROP_FRAME_COUNT);
    //根据图像总帧数设置采集率
	if (sumFrames >= 100) {
		if (rows < 2000) {
			read = 100;
			step = (int)(sumFrames / 100);
		}
		else {
			read = 50;
			step = (int)(sumFrames / 50);
		}
	}
	else { read = sumFrames; step = 1; }
}

void Recovery::process()
{
    //
	t = (double)getTickCount();
    //采集图像
	eachframe = vector<Mat>(read);
	for (int k=0;k<(read*step);k++) {
		cap >> frame;
		if (k%step == 0) frame.copyTo(eachframe[k/step]);
	}
    //对每个像素点进行运算
	result = Mat::zeros(rows,cols,CV_8UC3);
	result.forEach<Pixel>
	(
		[this](Pixel& pixel, const int * position)->void
		{
			uchar b[256] = { 0 };
			uchar g[256] = { 0 };
			uchar r[256] = { 0 };
			for (int k = 0; k < read; k++) {
				b[eachframe[k].ptr<Vec3b>(position[0])[position[1]][0]]++; 
				g[eachframe[k].ptr<Vec3b>(position[0])[position[1]][1]]++; 
				r[eachframe[k].ptr<Vec3b>(position[0])[position[1]][2]]++;
			}
			int maxB = b[0], maxG = g[0], maxR = r[0];
			int B = 0, G = 0, R = 0;
			for (int n = 1; n < 256; n++) {
				if (maxB <= b[n]) { maxB = b[n]; B = n; }
				if (maxG <= g[n]) { maxG = g[n]; G = n; }
				if (maxR <= r[n]) { maxR = r[n]; R = n; }
			}
			pixel[0] = B;
			pixel[1] = G;
			pixel[2] = R;
		}
	);
	//中值滤波，消除噪点
	Mat tmp;
	medianBlur(result, tmp, 3);
	medianBlur(tmp, result, 3);
	time = ((double)getTickCount() - t) / getTickFrequency();
	cout << "Process time: " << time << "s" << endl;
}


void Recovery::showResult()
{
	namedWindow("Result", WINDOW_AUTOSIZE);
	imshow("Result", result);
	waitKey(0);
}

