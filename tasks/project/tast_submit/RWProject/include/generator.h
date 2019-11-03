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
* @brief ��������
* ���ļ�����������Ϣ������ʱ��������
*/
class RequestGenerator
{
public:
	/**
	* @brief ��ʼ��
	* @param _dispatcher ��������һ������
	*/
	RequestGenerator(Dispatcher& _dispatcher);
	/**
	* @brief ���ļ�����������Ϣ
	* @param fin �����ļ���
	*/
	void loadFromFile(ifstream& fin);
	/** @brief ������������������ѭ�� */
	void run();
	/** @brief �ȴ�������ѭ���� */
	void join();
	/** @brief ֹͣ������ѭ�� */
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