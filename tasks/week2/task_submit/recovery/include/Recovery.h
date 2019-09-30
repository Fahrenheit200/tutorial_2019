/*****************************************************************************
* 
*  @file	Recovery.h
*  @brief	Recovery类
* 
*  @author	PumpkinJimmy
*  @email	996344439@qq.com
*  @version	v1.0.0
*  @date	2019-09-30
* 
*****************************************************************************/
#ifndef _RECOVERY_RECOVERY_H
#define _RECOVERY_RECOVERY_H
#include <vector>
#include <chrono>
#include <opencv2/opencv.hpp>
using namespace cv;
/**
* @brief 用于背景还原的类
*
*/
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
	/**
	* 初始化模型参数矩阵
	*/
	void init();
	/**
	* 初始化迭代器
	*/
	void initIterators();
	/**
	* 移动迭代器
	*/
	void moveIterators();
	/**
	* 开始计时
	*/
	void startClock();
	/**
	* 停止计时
	* @return 经过时间
	*/
	float endClock();
	/**
	* 保存成果
	*/
	void saveResult();
	/**
	* 三维正态分布概率密度
	* @param x 输入向量
	* @param miu 均值向量
	* @param sga 标准差
	* @return 概率密度
	*/
	double gsVec(const Vec3b& x, Vec3f miu, float sga);
	/**
	* 寻找匹配模型
	* @param it 当前像素迭代器
	* @return 匹配模型编号
	*/
	int getMatchModel(MatIterator_<Vec3b> it);
	/**
	* 寻找最佳模型
	* @return 最佳模型
	*/
	int getBestModel();
	/**
	* 设置新模型
	* @param it 当前像素迭代器
	*/
	void resetModel(MatIterator_<Vec3b> it);
	
	/**
	* 更新匹配的模型
	* @param it 当前像素迭代器
	* @param bst 匹配的模型
	*/
	void updateModel(MatIterator_<Vec3b> it, int bst);

	int fcnt; ///<帧数
	float rate; ///<学习率
	VideoCapture cap; ///<视频读取
	Mat frame; ///<当前帧
	Mat result; ///<结果
	std::vector<Mat> mius, sigmas, omigas; ///<保存模型参数的矩阵
	std::chrono::steady_clock::time_point start_tp; ///<起始时间点
	std::vector<MatIterator_<Vec3f>> itus; ///<当前均值迭代器
	std::vector<MatIterator_<float>> itas; ///<当前标准差迭代器
	std::vector<MatIterator_<float>> itos; ///<当前权值迭代器
};
#endif
