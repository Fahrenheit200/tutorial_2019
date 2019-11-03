/**
* @file cli.h
* @brief CLI接口
* @author bbpumpkin
* @version 1.0.0
* @date 2019-10-14
*/
#pragma once
#ifndef _GATE_CLI_MODULE
#define _GATE_CLI_MODULE
#include <vector>
#include <map>
#include <string>
#include <functional>
#include "gate.h"
using namespace std;
/** @brief 表示命令状态 */
enum CmdState { CMD_UNKNOWN, CMD_FAIL, CMD_SUCCEED };
/**
* @brief 命令实现
*/
class CommandImpl
{
public:
	/**
	* @param _board 执行命令的Board实例的引用
	*/
	CommandImpl(Board& _board);
	/**
	* @brief 运行命令的接口
	* @param cmd_name 命令名
	* @param args 参数列表
	*/
	CmdState runCommand(const string& cmd_name, const vector<string>& args);
private:
	Board board;
	bool exit(const vector<string>& args);
	bool help(const vector<string>& args);
	bool create(const vector<string>& args);
	bool setInput(const vector<string>& args);
	bool setOutput(const vector<string>& args);
	bool connect(const vector<string>& args);
	bool list(const vector<string>& args);
	bool exec(const vector<string>& args);
	bool print(const vector<string>& args);
	bool clear(const vector<string>& args);
	void getHelp(const string& cmd_name);
	using Handler = function<bool(const vector<string>& args)>;
	map<string, Handler> map_handler;
	map<Board::Port, Gate::InputSet> input_buf;
	map<int, Gate::OutputSet> output_buf;
};
/**
* @brief CLI控制台
* 维护主循环，提供提示符，从控制台获得输入并调用CommandImpl执行命令
*/
class Console
{
public:
	Console(const CommandImpl& _impl);
	/**
	* @brief 启动主循环
	*/
	void run();
	/**
	* @brief 从控制台输入获得指令与参数序列
	* @param cmd_name 获得的命令名
	* @param args 获得的参数序列
	* @return 是否获得有效输入
	*/
	bool getInput(string& cmd_name, vector<string>& args);
	/**
	* @brief 获得提示符
	* @return 提示符
	*/
	const string& getPrompt() const;
	/**
	* @brief 设置提示符
	*/
	void setPrompt(const string& pt);
	/**
	* @brief 停止主循环
	*/
	void stop();
private:
	CommandImpl impl;
	string prompt;
	bool running;
};
#endif