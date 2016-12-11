#include "Binornd.h"

Binornd* Binornd::_global_instance;
Binornd::Binornd()
{
	urd = uniform_real_distribution<double>(0.0f, 1.0f);
}


Binornd::~Binornd()
{
}

bool Binornd::_get(double pi){
	return urd(generator) <= pi;
}

bool Binornd::get(double pi){
	if (!_global_instance){
		_global_instance = new Binornd();
	}
	return _global_instance->_get(pi);
}