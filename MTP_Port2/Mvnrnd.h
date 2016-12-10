#pragma once
#include <random>

#include <Eigen/Cholesky>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

using namespace std;

class Mvnrnd
{
	static Mvnrnd* _global_instance;
	default_random_engine generator;
	normal_distribution<double> nd_base;
private:
	Mvnrnd();
	~Mvnrnd();
	VectorXd _get(VectorXd mu, MatrixXd cov);
public:
	static VectorXd get(VectorXd mu, MatrixXd cov);
};

