#pragma once
#ifndef _THREADDISPATCH_REQUEST_MODULE
#define _THREADDISPATCH_REQUEST_MODULE
#include <string>
#include <vector>
using namespace std;
/**
* @brief 请求类
*/
class Request
{
public:
	/** @brief 请求类型，R表示read，W表示write */
	enum RequestType { R, W };
	/** 
	* @brief 给出请求参数 
	* @param _rid 请求id
	* @param rt 请求类型
	* @param st 请求发起时间
	* @param durat 持续时间
	*/
	Request(int _rid = 0, RequestType rt = R, int st = 0, int durat = 0);
	Request(int _rid, const string& rt, int st, int durat);
	/** @brief 返回请求id */
	int getRid() const { return rid; }
	/** @brief 返回请求类型 */
	RequestType getType() const { return type; }
	/** @brief 返回请求发起时间 */
	int getStartT() const { return start_t; }
	/** @brief 返回持续时间 */
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