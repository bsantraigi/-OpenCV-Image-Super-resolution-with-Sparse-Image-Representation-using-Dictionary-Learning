#pragma once
#include <random>

using namespace std;
class Binornd
{
	static Binornd* _global_instance;
	default_random_engine generator;
	uniform_real_distribution<double> urd;
	bool _get(double pi);
public:
	Binornd();
	~Binornd();
	static bool get(double pi);
};

