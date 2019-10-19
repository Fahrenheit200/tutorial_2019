#include <algorithm>
#include <thread>
#include <chrono>
#include "generator.h"
RequestGenerator::RequestGenerator(Dispatcher& _dispatcher) : dispatcher(_dispatcher)
{
	cur_req = 0;
	cur_tick = 0;
	running = false;
}


void RequestGenerator::loadFromFile(ifstream& fin)
{
	requests.clear();
	int rid, st, durat;
	string type;
	while (!fin.eof())
	{
		fin >> rid >> type >> st >> durat;
		requests.push_back(Request(rid, type, st, durat));
	}
	sort(requests.begin(), requests.end());
}

void RequestGenerator::run()
{
	running = true;
	run_thread = thread([&]() {
		using namespace chrono_literals;
		while (this->running && cur_req < requests.size())
		{
			while (cur_req < requests.size() && requests[cur_req].getStartT() == cur_tick)
			{
				dispatcher.request(requests[cur_req]);
				cur_req++;
			}
			this_thread::sleep_for(1s);
			cur_tick++;
			
		}
		dispatcher.stop();
		});
}

void RequestGenerator::join()
{
	run_thread.join();
}

void RequestGenerator::stop()
{
	running = false;
	run_thread.detach();
}
