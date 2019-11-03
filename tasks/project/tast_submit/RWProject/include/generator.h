#pragma once
#ifndef _THREADDISPATCH_GENERATOR_MODULE
#define _THREADDISPATCH_GENERATOR_MODULE
#include <fstream>
#include <vector>
#include <thread>
#include "request.h"
#include "dispatch.h"
using namespace std;
/**
* @brief 请求发生器
* 从文件载入请求信息，并按时发送请求
*/
class RequestGenerator
{
public:
	/**
	* @brief 初始化
	* @param _dispatcher 调度器的一个引用
	*/
	RequestGenerator(Dispatcher& _dispatcher);
	/**
	* @brief 从文件加载请求信息
	* @param fin 输入文件流
	*/
	void loadFromFile(ifstream& fin);
	/** @brief 启动非阻塞的请求发送循环 */
	void run();
	/** @brief 等待请求发送循环完 */
	void join();
	/** @brief 停止请求发送循环 */
	void stop();
private:
	Dispatcher& dispatcher;
	vector<Request> requests;
	int cur_req;
	int cur_tick;
	thread run_thread;
	bool running;
};
#endif