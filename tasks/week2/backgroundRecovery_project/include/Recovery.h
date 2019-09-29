#ifndef __RECOVERY_H
#define __RECOVERY_H
#include<string>
#include<vector>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
using std::string;
using std::vector;
class Recovery
{
public:
	/* readVideo
	* @param filePath 文件绝对路径
	* 根据绝对路径读取需要还原背景的文件
	*/
	void readVideo(string filePath);

	/* process
	* 进行还原过程
	*/

	void process();
	/* showResult
	* 窗口展示背景还原后的结果
	*/
	void showResult();          

private:
	/* getMode
	* @param A 元素为 uchar 型的 vector 容器
	* 获取 A 中的众数
	*/
	uchar getMode(vector<uchar>& A);   
	Mat outputImage;				//处理后的图片
	long totalFrameNumber;			//进行处理的总帧数
	string file_path;				//视频文件的绝对路径      
};
#endif   // end of Recovery.h
