#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <random>

#include "DLConfig.h"
#include "Float2D.h"
#include "Gamrnd.h"
#include "Mvnrnd.h"
#include "Betarnd.h"
#include "Binornd.h"

using namespace std;

#include <Eigen/Dense>
using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::MatrixXi;
typedef Eigen::Matrix<bool, -1, -1> MatrixXb;

class DLLayer
{
	// Float2D lives and dies with this class : for any external
	// access return 2D vector

	MatrixXd Y, D, S, post_PI;
	MatrixXb B;
	VectorXd PI, bias;
	int M, N, K;
	double gam_d, gam_s, gam_n, gam_bias;

	default_random_engine generator;
	gamma_distribution<double> gdist;
	bool trained = false;
private:
	void Init(MatrixXd& fMat, DLConfig config);
public:
	// Ctor and Dtor
	DLLayer(MatrixXd &fMat, DLConfig config);	
	~DLLayer();

	//Getter
	bool IsTrained(){ return trained; }

	/*
	Function: RunGibbs
	Starts Gibbs sampling algorithm for this layer
	*/
	void RunGibbs(int iters);
	void CompleteSampler();
	
};

