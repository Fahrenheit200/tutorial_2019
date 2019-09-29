/******************************************************************
 * @file        Recovery.cpp
 * @brief       This file define class Recovery
 * Details.
 *
 * @version     1.0.1
 * @author      林嘉鸿
 * @email       1073097404@qq.com
 *
 * -----------------------------------------------------------------
 *  Change History:
 *  <Date>      |<Version>      |<Author>       |<Description>
 *  ----------------------------------------------------------------
 *  2019/09/29  |1.0.1          |林嘉鸿         |Create file
 *
 *  ****************************************************************/

#include "../include/Recovery.hpp"

int main(int argc,char** argv)
{
	Recovery Rec;
	Rec.readVideo(string(argv[1]));
	Rec.process();
	Rec.showResult();
}

void Recovery::readVideo(String f)
{
	//保存地址
        filePath=f;
	//保存视频数据
        cap.open(filePath);
	//示意视频是否成功打开
	if (!cap.isOpened())
        {
                printf("Open file fail\n");
        }
	else
		printf("Open file success\n");
};

void Recovery::process()
{
	cout<<"Start"<<endl;
        Mat frame1,frame2,frame3,frame4,frame5,frame6;
        int i,j,k,num;
	//开始计时
        double t = (double)cvGetTickCount();
	//读取第一帧图像并保存
        cap.read(frame1);
	//寻找前景不与第一帧有重叠的另一帧图像
	while(true)
        {
                //读入一张图片
                cap.read(frame2);
                //与第一帧图片作差分
                absdiff(frame1,frame2,frame3);
                //差分图转换成灰度图
                cvtColor(frame3,frame3,CV_BGR2GRAY);
                //将差分灰度图二值化
                threshold(frame3,frame3,1,255,CV_THRESH_BINARY);
                //腐蚀差分黑白图像
                Mat element_1=getStructuringElement(MORPH_RECT,Size(5,5));
                erode(frame3,frame4,element_1);
                //定义vector数组储存轮廓信息
                vector<vector<Point>> contours_out;
                vector<Vec4i> hierarchy;
                //寻找差分黑白图像中的轮廓
                findContours(frame4,contours_out,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_NONE);
                //判断轮廓的大小，将太小的轮廓判为噪点并除去
                for(k=0;k<contours_out.size();k++)
                {
                        //经过测试，500像素是一个比较通用的阈值
                        if(contours_out.at(k).size()<500)
                                //小轮廓内填充黑色
                                drawContours(frame4,contours_out,k,Scalar(0,0,0),CV_FILLED);
                }
                //再次寻找轮廓，判断优化后的图像有几个轮廓
		findContours(frame4,contours_out,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_NONE);
                //如果剩下两个较大的轮廓，则前景物体不重叠，这两张图经过处理就可以拼成一张完整的图像
                if((contours_out.size()!=2))
                        continue;
                cout<<"Foreground target have been detected"<<endl;
                //将第一张图的前景去除
                rectangle(frame1,boundingRect(contours_out[0]),Scalar(0,0,0),-1,4);
                //备份frame1，作进一步处理
                frame1.copyTo(frame5);
                //frame5转换为灰度图像
                cvtColor(frame5,frame5,CV_BGR2GRAY);
                //frame5二值化，生成反向掩模
                threshold(frame5, frame5, 0, 255, CV_THRESH_BINARY);
                //frame5反色
                bitwise_not(frame5,frame5);
                //frame1掩模处理？？
                frame1.setTo(0,frame5);
                //frame5再反色
                bitwise_not(frame5,frame5);
                //frame2掩模处理
                frame2.setTo(0,frame5);
                //frame1和frame2叠加得到全幅背景
                frame6=frame1+frame2;
		//保存结果
		result=frame6;
		break;
	}
	//释放空间
        cap.release();
        //结束计时并输出
        t=(double)getTickCount()-t;
        cout<<"Finish"<<endl<<"Total time:"<<t/getTickFrequency()<<"s"<<endl;
	
}

void Recovery::showResult()
{
	//将全幅背景储存为jpg图像
	if(!result.empty())
		imwrite("./result/res"+filePath.substr(16,1)+".jpg",result);
}
