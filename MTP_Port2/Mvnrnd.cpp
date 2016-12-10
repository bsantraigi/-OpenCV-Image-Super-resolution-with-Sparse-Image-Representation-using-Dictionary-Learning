#include "Mvnrnd.h"

Mvnrnd *Mvnrnd::_global_instance = NULL;

Mvnrnd::Mvnrnd()
{
	normal_distribution<double> nd_base(0, 1);
}

Mvnrnd::~Mvnrnd()
{
}

VectorXd Mvnrnd::_get(VectorXd mu, MatrixXd cov)
{
	VectorXd x(mu.size());
	for (int d = 0; d < x.size(); d++) {
		x[d] = nd_base(generator);
	}
	x = mu + cov.llt().matrixL()*x;// From Cholesky decomposition
	return x;
}

VectorXd Mvnrnd::get(VectorXd mu, MatrixXd cov)
{
	if (!_global_instance) {
		_global_instance = new Mvnrnd();
	}
	return _global_instance->_get(mu, cov);
}
