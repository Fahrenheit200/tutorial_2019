#pragma once
#ifndef _THREADDISPATCH_REQUEST_MODULE
#define _THREADDISPATCH_REQUEST_MODULE
#include <string>
#include <vector>
using namespace std;
/**
* @brief ������
*/
class Request
{
public:
	/** @brief �������ͣ�R��ʾread��W��ʾwrite */
	enum RequestType { R, W };
	/** 
	* @brief ����������� 
	* @param _rid ����id
	* @param rt ��������
	* @param st ������ʱ��
	* @param durat ����ʱ��
	*/
	Request(int _rid = 0, RequestType rt = R, int st = 0, int durat = 0);
	Request(int _rid, const string& rt, int st, int durat);
	/** @brief ��������id */
	int getRid() const { return rid; }
	/** @brief ������������ */
	RequestType getType() const { return type; }
	/** @brief ����������ʱ�� */
	int getStartT() const { return start_t; }
	/** @brief ���س���ʱ�� */
	int getDuration() const { return duration; }
	bool operator<(const Request& req) const
	{
		if (start_t == req.start_t)
		{
			if (type != req.type) return type == W;
			else return rid < req.rid;
		}
		return start_t < req.start_t;
	}
private:
	int rid;
	RequestType type;
	int start_t;
	int duration;
};
#endif