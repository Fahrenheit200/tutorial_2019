#include "Recovery.h"
using namespace std;
using namespace cv;
void Recovery::readVideo(string filepath)
{
    int position=0;
	N=0;
    VideoCapture cap;
	if(!cap.open(filepath)) {cout<<"Error"<<endl;}
	long frame_num=cap.get(CV_CAP_PROP_FRAME_COUNT);//get frame number
	cap.set(CAP_PROP_POS_FRAMES, position);//set beginning position
	//Reading at a fixed interval
	if(frame_num<M)
	{
	for(int i=0; i<frame_num-1; i++)
    {
        cap>>images[i];
		N++;
    }
	}
	else
	{
	for(int i=0; i<M; i++)
    {
        cap>>images[i];
        cap.set(CAP_PROP_POS_FRAMES, position);
		position+=frame_num/M;	//change reading position
		N++;
    }
	}
	}
void Recovery::process()
{
	
    ans=images[0];
    int row = images[0].rows;
    int col = images[0].cols;
	//逐帧逐像素读取
    for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                for(int k=0; k<N; k++)
                {
                    b.push_back(images[k].at<Vec3b>(i,j)[0]);
                    g.push_back(images[k].at<Vec3b>(i,j)[1]);
                    r.push_back(images[k].at<Vec3b>(i,j)[2]);
                }
				//generate every pixel
                ans.at<Vec3b>(i,j)[0]=majorityElement(b);
                ans.at<Vec3b>(i,j)[1]=majorityElement(g);
                ans.at<Vec3b>(i,j)[2]=majorityElement(r);
				b.clear(); g.clear(); r.clear();
            }
        }
}

void Recovery::showResult()
{
	//open window to show image
    namedWindow( "Display window", WINDOW_NORMAL);
	// fixed window size
    resizeWindow("Display window",800,600);
    imshow("Display window",ans);
	//save image
	//imwrite("result.png",ans);
	waitKey(0);
}

int Recovery::majorityElement(vector<int> nums)
{
	//Sort arrays, substituting the middle value for the value with the most occurrences
    sort(nums.begin(),nums.end());
    return nums[nums.size()/2];
}

