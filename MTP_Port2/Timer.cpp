#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::start() {
	t1 = high_resolution_clock::now();
}

void Timer::stop() {
	t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "Time Elapsed: " << duration << endl;;
}