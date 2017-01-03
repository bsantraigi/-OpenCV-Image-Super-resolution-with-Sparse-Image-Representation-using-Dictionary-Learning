#include "DLConfig.h"



DLConfig::DLConfig()
{
	K = 80;
	a_d = a_s = a_bias = 1;
	b_d = b_s = b_bias = 1;
	a_n = b_n = 1e-1;

	a_pi = 1;
	b_pi = 1200;
}


DLConfig::~DLConfig()
{
}
