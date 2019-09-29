#ifndef _TIMER_INCLUDED
#define _TIMER_INCLUDED
#include <map>
#include <chrono>

using namespace std;

class Timer
{
public:
	typedef chrono::steady_clock::time_point TP;
	typedef chrono::steady_clock::duration duration;
	TP start(int tid=0);
	double stop(int tid=0);
	double update(int tid=0);
	double get_average_t(int tid=0);
private:
	TP (*now)() = chrono::steady_clock::now;
	double get_s(duration d) { return chrono::duration_cast<chrono::milliseconds>(d).count() / 1000.0;}
	double get_ms(duration d) { return chrono::duration_cast<chrono::microseconds>(d).count() / 1000.0;}
	map<int, TP> tps;
	map<int, double> accu;
	map<int, int> cnt;
};
#endif