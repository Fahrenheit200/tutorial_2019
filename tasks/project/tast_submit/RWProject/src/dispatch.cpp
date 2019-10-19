#include <iostream>
#include <chrono>
#include "dispatch.h"
#include "request.h"
using namespace std;
using namespace std::chrono;
Dispatcher::Dispatcher()
{
	running = false;
	occupied_cnt = 0;
	occupied = Request::R;
}
// thread_safe
void Dispatcher::request(const Request& req)
{
	if (req.getType() == Request::R)
	{
		requestReader(req);
	}
	else
	{
		requestWriter(req);
	}
}

void Dispatcher::run()
{
	running = true;
	start_t = chrono::steady_clock::now();
	while (running || !writers.empty() || !readers.empty())
	{
		if (occupied_cnt == 0)
		{
			Request req;
			if (!writers.empty())
			{
				mtx_wq.lock();
				req = writers.front();
				writers.pop();
				mtx_wq.unlock();
				occupied = Request::W;
				occupied_cnt = 1;
				start_thread(req, "writer1");
			}
			else if (!readers.empty())
			{
				occupied = Request::R;
				mtx_rq.lock();
				while (!readers.empty())
				{
					
					req = readers.front();
					readers.pop();
					occupied_cnt++;
					string name = "reader0"; name[name.size() - 1] += occupied_cnt;
					start_thread(req, name);
				}
				mtx_rq.unlock();
			}
			
		}
		else if (occupied == Request::R && writers.empty() && !readers.empty())
		{
			Request req;
			occupied = Request::R;
			mtx_rq.lock();
			req = readers.front();
			readers.pop();
			mtx_rq.unlock();
			occupied_cnt++;
			string name = "reader0"; name[name.size() - 1] += occupied_cnt;
			start_thread(req, name);
		}
	}
	for (int i = 0; i < thread_pool.size(); i++)
	{
		thread_pool[i].join();
	}
}

void Dispatcher::stop()
{
	running = false;
}

void Dispatcher::requestReader(const Request& req)
{
	mtx_rq.lock();
	readers.push(req);
	mtx_rq.unlock();
}

void Dispatcher::requestWriter(const Request& req)
{
	mtx_wq.lock();
	writers.push(req);
	mtx_wq.unlock();
}

void Dispatcher::start_thread(Request req, const string& name)
{
	int now =
		duration_cast<seconds>(steady_clock::now() - start_t).count();
	thread_pool.push_back(thread([&](Request req, int now, const string& name)->void {
		printf("[%s] <id: %d> %ds: Keep for %ds\n", name.c_str(), req.getRid(), now, req.getDuration());
		this_thread::sleep_for(seconds(req.getDuration()));
		int exit_t =
			duration_cast<seconds>(steady_clock::now() - start_t).count();
		printf("[%s] <id: %d> %ds: exit\n", name.c_str(), req.getRid(), exit_t);
		this->occupied_cnt--;
		}, req, now, name));
}
