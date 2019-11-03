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
* @brief ���������
* ��������ά���ȴ��������̳߳�
*/
class Dispatcher
{
public:
	Dispatcher();
	/** 
	* @brief �����������һ������
	* @param req ���͵�����
	*/
	void request(const Request& req);
	/** @brief ��������ѭ�� */
	void run();
	/** @brief ֹͣ����ѭ�� */
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