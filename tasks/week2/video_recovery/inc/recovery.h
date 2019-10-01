#ifndef RECOVERY_H
#define RECOVERY_H

#include <string.h>
#include <opencv2/opencv.hpp>
class Recovery
{
public:
	/*readVideo
	 * @param filePath 文件绝对路径
	 *根据路径读取需要还远背景的文件
	 */
	 void readVideo(std::string filePath);

	/*process
	 *进行还原过程
	 */
	void process();

	/*showResult*/
	void showResult();
private:
	int framecount, rows, cols;
	cv::Mat result;
	cv::VideoCapture video;
};

#endif
