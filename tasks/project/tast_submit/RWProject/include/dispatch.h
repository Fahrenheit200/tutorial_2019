#pragma once
#ifndef _THREADDISPATCH_DISPATCH_MODULE
#define _THREADDISPATCH_DISPATCH_MODULE
#include <thread>
#include <queue>
#include <mutex>
#include <chrono>
#include "request.h"
using namespace std;
/**
* @brief 请求调度器
* 处理请求，维护等待队列与线程池
*/
class Dispatcher
{
public:
	Dispatcher();
	/** 
	* @brief 向调度器发送一个请求
	* @param req 发送的请求
	*/
	void request(const Request& req);
	/** @brief 启动调度循环 */
	void run();
	/** @brief 停止调度循环 */
	void stop();
private:
	queue<Request> readers;
	queue<Request> writers;
	mutex mtx_rq;
	mutex mtx_wq;
	mutex mtx_cnt;
	bool running;
	chrono::steady_clock::time_point start_t;
	int occupied_cnt;
	Request::RequestType occupied;
	void requestReader(const Request& req);
	void requestWriter(const Request& req);
	vector<thread> thread_pool;
	void start_thread(Request req, const string& name);
};

#endif