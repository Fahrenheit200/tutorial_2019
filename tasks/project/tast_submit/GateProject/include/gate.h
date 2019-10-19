/**
* @file gate.h
* @brief 逻辑门类
* @author bbpumpkin
* @version 1.0.0
* @date 2019-10-14
*/
#pragma once
#ifndef _GATE_GATE_MODULE
#define _GATE_GATE_MEDULE
#include <iostream>
#include <vector>
#include <map>
using namespace std;
/**
* @brief 逻辑门类
* 表示一个逻辑门，并具有连接其他门、输入输出数据的功能
*/
class Gate
{
public:
	typedef unsigned int InputSet;///< 抽象的输入位集合类型
	typedef unsigned int OutputSet;///< 抽象的输出位集合类型
	/** @brief 逻辑门类型 */
	enum GateType {
		NOT, ///<非
		AND, ///<与
		OR, ///<或
		XOR, ///<异或
		VOID ///<空
	};
	/**
	* @brief 门类型到字符串的映射
	* @param type 门类型
	* @return 对应字符串
	*/
	static string typeToStr(GateType type) {
		switch (type)
		{
		case VOID: return "VOID";
		case NOT: return "NOT";
		case AND: return "AND";
		case OR: return "OR";
		case XOR: return "XOR";
		default: return "UNDEFINED";
		}
	}
	/**
	* @param t 门类型
	* @param _gid 门id
	*/
	Gate(GateType t=VOID, int _gid=0);
	/**
	* @brief 连接到指定门指定端口
	* @param dst 门id
	* @param dst_id 连接端口
	*/
	void connectTo(Gate& dst, int dst_id);
	/**
	* @brief 沿图传播
	*/
	void propogate();
	/**
	* @brief 沿图传播
	* @param in 输入位集
	*/
	void propogate(InputSet in);
	/**
	* @brief 设置输入位值
	* @param in 值
	* @param dst_id 设置的位
	*/
	void setBit(bool in, int dst_id);
	/**
	* @brief 重置门状态
	*/
	void clear();
	/**
	* @brief 获得输出状态
	* @return 门输出
	*/
	OutputSet getOutput() const;
	/**
	* @brief 获得门id
	* @return 门id
	*/
	int getGid() const;
	/**
	* @brief 执行门的逻辑
	* @param in 输入
	* @return 输出
	*/
	OutputSet handle(InputSet in);
	/**
	* @brief 检验是否全部输入位都已得到输入
	* @return 是否全部输入位都已得到输入
	*/
	bool isAllSet() const;
	/**
	* @brief CLI接口，显示门内部状态
	*/
	void showInfo() const
	{
		cout << typeToStr(type) << '\t' << input_buf << '\t' << output_buf << '\t' << mask << endl;
	}
	/**
	* @brief CLI接口，显示门连接状态
	*/
	void showConn() const
	{
		for (Dst info : mp)
		{
			cout << info.dst->getGid() << " : " << info.dst_id << endl;
		}
	}
private:
	struct Dst
	{
		Gate* dst;
		int dst_id;
	};
	GateType type;
	int gid;
	vector<Dst> mp;
	InputSet input_buf;
	OutputSet output_buf;
	int mask;
};
/**
* @brief 模拟线路板
* 门与线路的管理接口，管理所有门的id
*/
class Board
{
public:
	/**
	* @brief 端口结构
	*/
	struct Port
	{
		int gid;///<门id
		int bmask;///<端口号
		Port(int g = 0, int b = 0) :gid(g), bmask(b) {}
		bool operator<(const Port& other) const { return gid < other.gid; }
	};
	/**
	* @brief 添加门
	* @param type 门类型
	* @param gid 门id
	* @return 操作是否成功
	*/
	bool add(Gate::GateType type, int gid);
	/**
	* @brief 返回门列表
	* @return 门列表
	*/
	const map<int, Gate>& listGate() const;
	/** @brief 重置所有门的状态 */
	void clear();
	/**
	* @brief 连接门
	* @param from_gid 输出门id
	* @param to_gid 输入门id
	* @param to_bid 输入端口
	* @return 操作是否成功
	*/
	bool connect(int from_gid, int to_gid, int to_bid);
	//bool setInputGates(const vector<Port>& ports);
	/**
	* @brief 设置输出门集合
	* @param gids 输出门的列表
	* @return 操作是否成功
	*/
	bool setOutputGates(const vector<int>& gids);
	/**
	* @brief 运行门电路系统
	* @param ins 输入数据
	* @return 输入数据
	*/
	map<int, Gate::OutputSet> calculate(const map<Port, Gate::InputSet>& ins);
	/**
	* @brief CLI接口，显示门内部状态
	*/
	void showInfo() {
		cout << "GID\tType\tInput\tOutput\tMask\n";
		for (auto it = gates.begin(); it != gates.end(); ++it)
		{
			cout << it->first << '\t'; it->second.showInfo();
		}
	}
	/**
	* @brief CLI接口，显示门内部状态
	*/
	void showConn() {
		for (auto it = gates.begin(); it != gates.end(); ++it)
		{
			cout << it->first << "->\n"; it->second.showConn();
		}
	}
	bool checkLoop() const;
private:
	map<int, Gate> gates;
	vector<Port> input_gates;
	vector<int> output_gates;
};
#endif
