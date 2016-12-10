#pragma once
#include <random>
using namespace std;
class Gamrnd
{
	default_random_engine generator;
	gamma_distribution<double> gd;
	gamma_distribution<double>::param_type param;
	bool initialized;

	static Gamrnd* _global_instance;
private:
	Gamrnd();
	~Gamrnd();
	double _get(double alpha, double beta);
public:	
	static double get(double alpha, double beta);
};

