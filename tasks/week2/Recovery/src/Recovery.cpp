#include "Recovery.h"
#include <iostream>
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <chrono> 
#include <sys/stat.h>
using namespace std;
using namespace cv; 
using namespace chrono;

void Recovery::readVideo(string filePath)
{
	Mat temp,image, imageSource;
	count = 0;
	video.open(filePath);
	
	while (1) 
	{
		video >> temp;
		if (temp.empty())
			break;
		count++;
		image = temp.clone();
		store.push_back(image);
	}
	if(count==0)
	{
		cout<<"open failed"<<endl;
	}
}

void Recovery::process()
{
	auto start = system_clock::now();
	vector<Rect> ROIrect;
	//1.随便找两个相邻的帧 存一个的拷贝 转灰度
	//变量xl1：意为“相邻的第一个帧” xl2同理
	Mat xl1, xl2, xl1_copy;
	xl1 = store[count/2].clone();
	xl1_copy = xl1.clone();

	xl2 = store[count/2-1].clone();

	cvtColor(xl1, xl1, COLOR_BGR2GRAY);
	cvtColor(xl2, xl2, COLOR_BGR2GRAY);

	Mat diff;
	absdiff(xl1, xl2, diff);
	//相邻帧相减，得到的图设为diff：（两者除了障碍物的部分其他完全相同，转灰度之后相减会把相同的部分置为黑色）
	//如果障碍物的位置是连续的，会得到一个大致的障碍物的区域，diff也就是一个洞
	//如果障碍物的位置不连续，diff是两个洞

	//再任意找一个帧，我们就命名为“随便帧”吧（程序里用的是patch，补丁的来源的意思）
	//如果随便帧上的障碍物和diff上的洞不重合 
	//说明可以从随便帧上在对应的位置截一块下来作为补丁 补在diff上 从而实现背景还原
	int seed = 0;
	Mat patch_pic = store[seed].clone();
	Mat patch_pic_copy = patch_pic;
	cvtColor(patch_pic, patch_pic, COLOR_BGR2GRAY);



	//但是，随便帧上的障碍物还是有可能会和diff上的洞重合
	//接下来，用for循环遍历所有的帧来找这个满足条件的“随便帧”


	//去掉diff上的噪点
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	erode(diff, diff, element);


	//寻找diff上的洞的轮廓
	vector<vector<Point>> xlcontours;
	vector<Vec4i>hierarchy;
	findContours(diff, xlcontours, hierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_NONE);
	vector<Rect> bounds(xlcontours.size());

	//我们预期的洞的数量要么是1个 要么是2个
	//因为两个帧相减不可能会出现2个以上的洞
	//但是实际上findContour会得到几十个轮廓 其实很多都是噪点 我们用矩形把所有东西的轮廓都框起来
	//由于噪点的轮廓都比较小 那么其对应矩形的轮廓也很小 我们设定一个过滤值：mythreshold，只有矩形的面积大于这个
	//过滤值的时候，我们才认为这个轮廓框起来的是障碍物而非噪点
	//同时把符合条件的矩形存起来 作为补丁的范围
	int ai, mythreshold = 2000, counter = 0;
	for (ai = 0; ai < xlcontours.size(); ai++)
	{
		bounds[ai] = boundingRect(xlcontours[ai]);
		if (bounds[ai].area() > mythreshold)
		{
			ROIrect.push_back(bounds[ai]);
		}
	}

	//下面的for循环在判断“随便帧”上的障碍物是否和diff上的洞有相交
	//如果相交，则随便帧不满足条件 往下继续遍历 如果不相交，则该“随便帧”满足条件
	for (; seed < count; seed++)
	{
		//如果障碍物位置连续变化→diff上只有一个洞的情况：
		if (ROIrect.size() == 1)
		{
			Mat temp_diff1, temp_diff2;

			//由于三个帧除了各自障碍物的区域不同，其他的区域是完全相同的
			//转灰度之后做差可以把相同的区域变为黑色
			absdiff(patch_pic, xl1, temp_diff1);
			threshold(temp_diff1, temp_diff1, 20, 255, THRESH_BINARY);
			medianBlur(temp_diff1, temp_diff1, 5);

			absdiff(patch_pic, xl2, temp_diff2);
			threshold(temp_diff2, temp_diff2, 20, 255, THRESH_BINARY);
			medianBlur(temp_diff2, temp_diff2, 5);

			patch_pic = temp_diff1 | temp_diff2;
			//二值化一下
			threshold(patch_pic, patch_pic, 50, 255, THRESH_BINARY);
			//经过以上操作 我们就可以得到一张图，这张图上三张帧障碍物的对应区域是白色的，其他地方都是黑色
			//这张图命名为patch_pic


			//接下来用boundingRect判断patch_pic上究竟有几个洞
			//如果随便帧的障碍物和diff的障碍物不重合 且障碍物位置是连续变化的 那么应该有两个大矩形
			//如果重合了 只会有1个大矩形
			//2个以上的矩形是不会出现的
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

			if (blocks.size() == 2)//如果是2个大矩形 满足退出条件
			{
				break;
			}
			//若不满足 for循环继续 seed++  上述过程继续重复
		}

		//如果障碍物位置不连续变化→diff上有两个洞的情况：
		//如果随便帧上的障碍物和两个洞都不重合，则满足退出条件
		else if (ROIrect.size() == 2)
		{
			//由于已经进入到了这个分支 说明diff上的两个洞是不重合的（不然那就是一个洞了）
			//相邻帧和随便帧各自做差，会得到两张图，分别是其中一个相邻帧上的洞和随便帧上的洞（其余部分都是黑色）
			//做了二值化之后，障碍物的区域会变成白色，这两张图片相或的结果，是一张集中了相邻帧和随便帧的障碍物的图片，命名为patch_pic
			//如果随便帧的障碍物没有和相邻帧的任意一个障碍物相交，那么patch_pic上应该是3个洞 满足退出条件
			//否则 继续遍历
			Mat temp_diff1, temp_diff2;

			absdiff(patch_pic, xl1, temp_diff1);
			threshold(temp_diff1, temp_diff1, 10, 255, THRESH_BINARY);
			medianBlur(temp_diff1, temp_diff1, 9);

			absdiff(patch_pic, xl2, temp_diff2);
			threshold(temp_diff2, temp_diff2, 10, 255, THRESH_BINARY);
			medianBlur(temp_diff2, temp_diff2, 9);

			patch_pic = temp_diff1 | temp_diff2;

			//以下操作是在判断矩形的个数 和上面的流程一样 改一下退出条件就好了
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
			if (blocks.size() == 3)//如果是3个大矩形 满足退出条件
			{
				break;
			}
		}

	}

	//程序运行到这里 我们已经得到需要打补丁的区域范围和补丁的来源帧了
	//下面就是把补丁来源帧上的补丁区域打到对应区域 由于补丁可能会是2块，所以用个for循环
	for (int i = 0; i < ROIrect.size(); i++)
	{
		patch_pic_copy(ROIrect[i]).copyTo(xl1_copy(ROIrect[i]));
	}

	//结果保存在私有数据成员output中
	output = xl1_copy.clone();

	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "run time:"
		<< double(duration.count()) * microseconds::period::num / microseconds::period::den << "秒" << endl;

}

void Recovery::showResult()
{
	mkdir("result",S_IRWXU);
	imwrite("./result/output.jpg",output);
	namedWindow("result", WINDOW_NORMAL);
	imshow("result", output);
	waitKey(0);
}
