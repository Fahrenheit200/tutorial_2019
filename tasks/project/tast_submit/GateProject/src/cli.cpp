/**
* @file cli.cpp
* @brief Console和CommandImpl的实现
* @author bbpumpkin
* @version 1.0.0
* @date 2019-10-14
*/
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <functional>
#include "gate.h"
#include "cli.h"
#define HANDLER(cmd) bind(&CommandImpl::cmd, this, _1);
using namespace std;
using namespace std::placeholders;
Console::Console(const CommandImpl& _impl):impl(_impl)
{
	prompt = "GS> ";
}

void Console::run()
{
	running = true;
	string cmd_name;
	vector<string> args;
	cout << "*-------------------------------------------------------*\n"
		 << "|  Gate Simlator CLI                                    |\n"
		 << "|  Author: bbpumpkin                                    |\n"
		 << "|  Enter \"help\" to get help                             |\n"
		 << "*-------------------------------------------------------*\n";
	while (running)
	{
		cout << prompt;
		if (!getInput(cmd_name, args)) continue;
		CmdState state = impl.runCommand(cmd_name, args);
		switch(state)
		{
		case CMD_UNKNOWN:
			cout << "Unknown command: " << cmd_name << endl;
			break;
		case CMD_FAIL:
			cout << cmd_name << ": Command execution failed" << endl;
			break;
		case CMD_SUCCEED:
			break;
		default:
			cout << "Unknow error happen" << endl;

		}
	}
}




bool Console::getInput(string& cmd_name, vector<string>& args)
{
	string input; getline(cin, input);
	if (input.empty()) return false;
	int pl = 0, pr = 0;
	args.clear();
	for (; pl < input.size() && isspace(input[pl]); pl++);
	bool first = true;
	while (pl < input.size())
	{
		pr = pl;
		for (; pr < input.size() && !isspace(input[pr]); pr++);
		string word = input.substr(pl, pr - pl);
		if (first)
		{
			cmd_name = word;
			first = false;
		}
		else
		{
			args.push_back(word);
		}
		for (; pr < input.size() && isspace(input[pr]); pr++);
		pl = pr;
	}
	return true;
}

const string& Console::getPrompt() const
{
	return prompt;
}

void Console::setPrompt(const string& pt)
{
	prompt = pt;
}

void Console::stop()
{
	running = false;
}

// create connect list setInput exec print

CommandImpl::CommandImpl(Board& _board) //TODO fix!!!
{
	board = _board;
	map_handler["exit"] = HANDLER(exit);
	map_handler["help"] = HANDLER(help);
	map_handler["create"] = HANDLER(create);
	map_handler["setInput"] = HANDLER(setInput);
	map_handler["setOutput"] = HANDLER(setOutput);
	map_handler["connect"] = HANDLER(connect);
	map_handler["list"] = HANDLER(list);
	map_handler["exec"] = HANDLER(exec);
	map_handler["print"] = HANDLER(print);
	map_handler["clear"] = HANDLER(clear);
}

CmdState CommandImpl::runCommand(const string& cmd_name, const vector<string>& args)
{
	if (!map_handler.count(cmd_name)) return CMD_UNKNOWN;
	return map_handler[cmd_name](args) ? CMD_SUCCEED : CMD_FAIL;
}


bool CommandImpl::exit(const vector<string>& args)
{
	cout << "--Exit Gate Simulator--" << endl;
	std::exit(0);
}

bool CommandImpl::help(const vector<string>& args)
{
	if (!args.size() || args.size() > 1)
	{
		cout << "Usage: help cmd_name" << endl;
	}
	else
	{
		getHelp(args[0]);
	}
	return true;
}
void CommandImpl::getHelp(const string& cmd_name)
{
	if (cmd_name == "exit")
	{
		cout << "Usage: exit" << endl
			<< "Function: Exit the Gate Simulator" << endl;
	}
	else if (cmd_name == "create")
	{
		cout << "Usage: create gid [type]" << endl
			<< "Function: Create a gate" << endl
			<< "available type: VOID NOT AND OR XOR" << endl;
	}
	else if (cmd_name == "setInput")
	{
		cout << "Usage: setInput gid1 bmask1 input1 gid2 bmask2 input2..." << endl
			<< "Function: Set the input value" << endl;
	}
	else if (cmd_name == "setOutput")
	{
		cout << "Usage: setOutput gid1 gid2 ..." << endl
			<< "Function: Set the output gates" << endl;
	}
	else if (cmd_name == "connect")
	{
		cout << "Usage: connect from_gid to_gid bmask" << endl
			<< "Function: Connect the gates" << endl;
	}
	else if (cmd_name == "list")
	{
		cout << "Usage: list [gate|connection]" << endl
			<< "Function: show inforamtion" << endl
			<< "\"list gate\" show all the gates" << endl
			<< "\"list connection\" show all the connections" << endl;
	}
	else if (cmd_name == "exec")
	{
		cout << "Usage: exec" << endl
			<< "Function: execute the gate network" << endl;
	}
	else if (cmd_name == "print")
	{
		cout << "Usage: print" << endl
			<< "Function: print the results of execution" << endl;
	}
	else if (cmd_name == "clear")
	{
		cout << "Usage: clear" << endl
			<< "Function: reset all the gates" << endl;
	}
	else
	{
		cout << "No help information" << endl;
	}
}
bool CommandImpl::create(const vector<string>& args)
{
	if (args.size() < 1 || args.size() > 2)
	{
		getHelp("create");
		return false;
	}
	if (args.size() == 1)
	{
		return board.add(Gate::VOID, atoi(args[0].c_str()));
	}
	else
	{
		Gate::GateType type = Gate::VOID;
		if (args[1] == "VOID")
		{
			type = Gate::VOID;
		}
		else if (args[1] == "NOT")
		{
			type = Gate::NOT;
		}
		else if (args[1] == "AND")
		{
			type = Gate::AND;
		}
		else if (args[1] == "OR")
		{
			type = Gate::OR;
		}
		else if (args[1] == "XOR")
		{
			type = Gate::XOR;
		}
		return board.add(type, atoi(args[0].c_str()));
	}
}

bool CommandImpl::setInput(const vector<string>& args)
{
	if (args.size() % 3) { getHelp("setInput"); return false; }
	input_buf.clear();
	for (int i = 0; i < args.size(); i += 3)
	{
		input_buf.insert(make_pair<Board::Port, Gate::InputSet>(
			Board::Port{ atoi(args[i].c_str()), atoi(args[i + 1].c_str()) },
			Gate::InputSet(atoi(args[i + 2].c_str())))
		);
	}
	return true;
}

bool CommandImpl::setOutput(const vector<string>& args)
{
	vector<int> output_gates;
	for (int i = 0; i < args.size(); i++)
	{
		output_gates.push_back(atoi(args[i].c_str()));
	}
	board.setOutputGates(output_gates);
	return true;
}

bool CommandImpl::connect(const vector<string>& args)
{
	if (args.size() != 3) { getHelp("connect"); return false; }
	int from_gid = atoi(args[0].c_str()), to_gid = atoi(args[1].c_str()), bmask = atoi(args[2].c_str());
	return board.connect(from_gid, to_gid, bmask);
}

bool CommandImpl::list(const vector<string>& args)
{
	if (args.size() > 1) { getHelp("list"); return false; }
	if (args.size() == 1)
	{
		if (args[0] == "gate")
			board.showInfo();
		else if (args[0] == "connection")
			board.showConn();
		else {
			getHelp("list"); return false;
		}
	}
	else {
		board.showInfo();
		board.showConn();
	}
	return true;
}

bool CommandImpl::exec(const vector<string>& args)
{
	output_buf = board.calculate(input_buf);
	print(args);
	return true;
}

bool CommandImpl::print(const vector<string>& args)
{
	if (output_buf.empty())
	{
		cout << "No result" << endl;
		return true;
	}
	cout << "Result: " << endl;
	for (auto it = output_buf.begin(); it != output_buf.end(); ++it)
	{
		cout << it->first << ": " << it->second << endl;
	}
	return true;
}

bool CommandImpl::clear(const vector<string>& args)
{
	if (args.size()) { getHelp("clear"); return false; }
	board.clear();
	return true;
}
