#ifndef _RECOVERY_H
#define _RECOVERY_H
#include<iostream>
#include<time.h>
#include<string>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
class Recovery{
	public:
		void readVideo(string filePath);
		void process();
		void showResult();
	private:
		void setFile(string filePath);
		string getFile();
		string path;
};

int boa[3000][3000]={0};

void Recovery::readVideo(string filePath)
{
	Recovery::setFile(filePath);
}

void Recovery::setFile(string filePath)
{
	path=filePath;
}
string Recovery::getFile()
{
	return path;
}
void Recovery::process()
{
	clock_t start=clock();
	VideoCapture capture(getFile());
            if(!capture.isOpened())
            {
                    cout<<"fail to open file"<<endl;
                    return;
            }
	    int framenum=capture.get(CV_CAP_PROP_FRAME_COUNT);
	    int rate=framenum/25;
	    if(rate<1)rate=1;
           // cout<<"total frame is"<<framenum<<endl;
//	cout<<getFile()<<endl;
//waitKey(0);
	   //  bool stop=false;
            Mat frame;
	    Mat frame2;
	    Mat result;
            namedWindow("wi");
	    int total=2;
	    int i=0,j=0;
	    capture.read(frame);
//	capture.read(frame2);
	    capture.read(result);
	   //  int col=frame.cols;
	    //int row=frame.rows;
	   // cout<<1;
		while(1)
            {
	
		    // cout<<"1";
		//    total+=rate;
 		    total+=rate+1;
		    
		    if(total >= framenum-3) break;
                    capture.read(frame);
		  for(long p=0;p<rate&&total-rate+p<framenum-2;p++) capture.read(frame2);
		  
		   // capture>>frame;
            //imshow("wi",frame);
                    for(i=0;i<frame.rows;i++)
                    {
                            for(j=0;j<frame.cols;j++)
                            {
                                   /* Vec3b bgr = frame.at<Vec3b>(i,j);
                                    bgr[0]=255-bgr[0];
                                    bgr[1]=255-bgr[1];
                                    bgr[2]=255-bgr[2];
                                    frame.at<Vec3b>(i,j)=bgr;*/
				   if(boa[i][j]==1) continue;
				    Vec3b bgr = frame.at<Vec3b>(i,j);
				    Vec3b bgr2 = frame2.at<Vec3b>(i,j);
				    if (boa[i][j]==0&&bgr==bgr2){ boa[i][j]=1; result.at<Vec3b>(i,j)=bgr;}

                            }
                    }

	    }
               clock_t end=clock();
               cout<<"runing time is : "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
		imshow("wi",result);
		waitKey(0);
	//	imwrite("video2.jpg",frame);
   		return;
 

}
#endif
