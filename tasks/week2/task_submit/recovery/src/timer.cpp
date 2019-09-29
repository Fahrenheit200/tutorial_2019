#include <iostream>
#include <chrono>
#include "timer.h"
using namespace std;
Timer::TP Timer::start(int tid)
{
	tps[tid] = now();
}
double Timer::update(int tid)
{
	if (tps.count(tid) == 0) return -1;
	duration d = now() - tps[tid];
	double costt = get_ms(d);
	accu[tid] += costt;
	cnt[tid]++;
	return costt;
}
double Timer::stop(int tid)
{
	if (tps.count(tid) == 0) return -1;
	accu[tid] = 0;
	cnt[tid] = 0;
	return get_s(now() - tps[tid]);
}
double Timer::get_average_t(int tid)
{
	if (tps.count(tid) == 0) return -1;
	return accu[tid] / cnt[tid];
}