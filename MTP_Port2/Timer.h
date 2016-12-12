#pragma once
#include <chrono>
#include <iostream>

using namespace std::chrono;
using namespace std;

class Timer
{
	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;
public:
	Timer();
	void start();
	void stop();
	void stop(int iter);
	~Timer();
};

