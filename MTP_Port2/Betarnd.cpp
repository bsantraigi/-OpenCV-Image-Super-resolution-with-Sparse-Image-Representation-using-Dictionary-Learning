#include "Betarnd.h"

Betarnd* Betarnd::_global_instance;

Betarnd::Betarnd()
{
}


Betarnd::~Betarnd()
{
}

double Betarnd::_get(double alpha, double beta)
{
	double x = Gamrnd::get(alpha, 1);
	double y = Gamrnd::get(beta, 1);
	return x / (x + y);
}

double Betarnd::get(double alpha, double beta)
{
	if (!_global_instance){
		_global_instance = new Betarnd();
	}
	return _global_instance->_get(alpha, beta);
}
