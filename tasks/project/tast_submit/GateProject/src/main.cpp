/**
* @file main.cpp
* @brief 主程序
* @mainpage GateSimulator
* @author bbpumpkin
* @version 1.0.0
* @date 2019-10-14
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include "gate.h"
#include "cli.h"
using namespace std;
int main(int argc, char** argv)
{
	Board board;
	CommandImpl impl(board);
	Console console(impl);
	console.run();
	return 0;
}