#ifndef _RECOVERY_RECOVERY_H
#define _RECOVERY_RECOVERY_H
#include <vector>
#include <chrono>
#include <opencv2/opencv.hpp>
using namespace cv;
class Recovery
{
public:
	/* readVideo
    * @param filePath 文件绝对路径
    * 根据绝对路径读取需要还原背景的文件
    */
	void readVideo(String filePath);
	/* process
    * 进行还原过程
    */
	void process();
	/* showResult
    * 窗口展示背景还原后的结果
    */
	void showResult();
private:
	void init();
	void initIterators();
	void moveIterators();
	void startClock();
	float endClock();
	void saveResult();
	double gsVec(const Vec3b& x, Vec3f miu, float sga);
	int getMatchModel(MatIterator_<Vec3b> it);
	int getBestModel();
	void resetModel(MatIterator_<Vec3b> it);
	void updateModel(MatIterator_<Vec3b> it, int bst);

	int fcnt;
	float rate;
	VideoCapture cap;
	Mat frame;
	Mat result;
	std::vector<Mat> mius, sigmas, omigas;
	std::chrono::steady_clock::time_point start_tp;
	std::vector<MatIterator_<Vec3f>> itus;
	std::vector<MatIterator_<float>> itas;
	std::vector<MatIterator_<float>> itos;
};
#endif
