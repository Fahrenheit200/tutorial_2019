#include "Recovery.h" 

double random(double start,double end) {
    return start + (end - start) * rand() / (RAND_MAX + 1.0);
}

void Recovery::readVideo(String filePath){
	video = VideoCapture(filePath);
}

void Recovery::process(){
	cout<<"Start now!!!`~`"<<endl;
	chrono::steady_clock::time_point start = chrono::steady_clock::now();
	vector<Mat> backs;
	int count = 0;
	int num_frames = (int)video.get(CV_CAP_PROP_FRAME_COUNT);
	while(count < 40) {
		count++;
		Mat frame1, frame2;
		int f1 = (int)random(0, num_frames);
		int f2 = (int)random(0, num_frames);
		video.set(CAP_PROP_POS_FRAMES, f1);
		video >> frame1;
		video.set(CAP_PROP_POS_FRAMES, f2);
		video >> frame2;
		GaussianBlur(frame1, frame1, Size(3, 3), 5, 5);
		GaussianBlur(frame2, frame2, Size(3, 3), 5, 5);
		Mat diff;
		absdiff(frame1, frame2, diff);

		Mat edge;
		cvtColor(diff, edge, CV_BGR2GRAY);
		threshold(edge, edge, 16, 255, CV_THRESH_BINARY);
		vector<vector<Point>> contours;
		vector<Vec4i> hierarcy;
		findContours(edge, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
		auto itc = contours.begin();  
		while (itc != contours.end()) {
			if(contourArea(*itc) < 10000) {  
			    itc= contours.erase(itc);  
			}
			else itc++;  
		} 	
		if(contours.size() != 2) continue;
		Rect box1 = boundingRect(Mat(contours[0]));
		Rect box2 = boundingRect(Mat(contours[1]));
		box1 = box1 + Point(-50, -50) + Size(100, 50);
		box2 = box2 + Point(-50, -50) + Size(100, 50);
		rectangle(edge, box1, (255,255,255), -1);
		rectangle(edge, box2, (255,255,255), -1);

		Mat back = frame1.clone();	
		for(int i=0; i<back.rows; i++) {
			unsigned char * p = edge.ptr<unsigned char>(i);
            for(int j=0; j<back.cols; j++) {
				if(p[j] ==255) {
					back.at<Vec3b>(i, j)[0] = 0;  
            		back.at<Vec3b>(i, j)[1] = 0;  
            		back.at<Vec3b>(i, j)[2] = 0;  
				}	
            }
        }
		backs.push_back(back);
		if(waitKey(33) >= 0) break;
	}

	result = backs[0].clone();
	for(int k=0; k<backs.size(); k++){
		for(int i=0;i<result.rows;i++) {
            for(int j=0;j<result.cols;j++) {
				bool b1 = result.at<Vec3b>(i,j)[0] == 0&&result.at<Vec3b>(i,j)[1] == 0&&result.at<Vec3b>(i,j)[2] == 0;
				bool b2 = backs[k].at<Vec3b>(i,j)[0] == 0&&backs[k].at<Vec3b>(i,j)[1] == 0&&backs[k].at<Vec3b>(i,j)[2] == 0;
				if(b1&& (!b2)){
					result.at<Vec3b>(i,j) = backs[k].at<Vec3b>(i,j);
				}
				else if(!b1 && !b2) {
					result.at<Vec3b>(i,j)[0] = (result.at<Vec3b>(i,j)[0] + backs[k].at<Vec3b>(i,j)[0])/2;
					result.at<Vec3b>(i,j)[1] = (result.at<Vec3b>(i,j)[1] + backs[k].at<Vec3b>(i,j)[1])/2;
					result.at<Vec3b>(i,j)[2] = (result.at<Vec3b>(i,j)[2] + backs[k].at<Vec3b>(i,j)[2])/2;
				}	
            }
        }
	}
	imwrite("./result/result.jpg", result);

	chrono::steady_clock::time_point end = chrono::steady_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(end - start);
	cout << "Process time:" << time_span.count() << "s\n";
}

void Recovery::showResult(){
	namedWindow("Result", 0);	
	cvResizeWindow("Result", 800, 600);
	imshow("Result", result);
	waitKey(0);
}
