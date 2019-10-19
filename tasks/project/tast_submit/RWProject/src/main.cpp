#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include "request.h"
#include "dispatch.h"
#include "generator.h"
using namespace std;
vector<Request> reqs;
int main(int argc, char** argv)
{
	cout << "[main] start" << endl;
	if (argc < 2)
	{
		cout << "No input file provided, exit" << endl;
		return 0;
	}
	cout << "[main] try open " << argv[1] << endl;
	ifstream fin(argv[1]);
	if (!fin.is_open())
	{
		cout << "Open input file failed, exit" << endl;
		return 0;
	}
	else
	{
		cout << "[main] open " << argv[1] << " success" << endl;
	}
	Dispatcher dispatcher;
	RequestGenerator gen(dispatcher);
	gen.loadFromFile(fin);
	gen.run();
	dispatcher.run();
	gen.join();
	return 0;
}