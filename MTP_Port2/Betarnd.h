#pragma once
#include "Gamrnd.h"
class Betarnd
{
	static Betarnd* _global_instance;
	double _get(double alpha, double beta);
public:
	Betarnd();
	~Betarnd();
	static double get(double alpha, double beta);
};

