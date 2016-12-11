#include "DLLayer.h"

DLLayer::DLLayer(MatrixXd& fMat, DLConfig config)
{
	Init(fMat, config);
}

DLLayer::~DLLayer()
{
}

void DLLayer::Init(MatrixXd& fMat, DLConfig config){
	M = (fMat.rows());
	N = (fMat.cols());
	K = (config.K);

	D = (MatrixXd(M, K));
	S = (MatrixXd(K, N));

	B = (MatrixXb(K, N));
	PI = (VectorXd(K));
	Y = (MatrixXd(M, N));

	post_PI = MatrixXd(K, N);

	Y << fMat;
	gam_d = Gamrnd::get(config.a_d, config.b_d);
	gam_s = Gamrnd::get(config.a_s, config.b_s);
	gam_n = Gamrnd::get(config.a_n, config.b_n);
	gam_bias = Gamrnd::get(config.a_bias, config.b_bias);

	VectorXd zmu = VectorXd::Zero(M);
	MatrixXd Id = MatrixXd::Identity(M, M);
	for (int k = 0; k < K; k++)
	{
		D.col(k) = Mvnrnd::get(zmu, (1 / gam_d)*Id);
	}

	zmu = VectorXd::Zero(K);
	MatrixXd Is = MatrixXd::Identity(K, K);
	for (int k = 0; k < K; k++)
	{
		S.col(k) = Mvnrnd::get(zmu, (1 / gam_s)*Is);
	}

	bias = Mvnrnd::get(VectorXd::Zero(M), (1 / gam_bias)*Id);

	for (int k = 0; k < K; k++)
	{
		PI(k) = Betarnd::get(config.a_pi, config.b_pi);
		for (int i = 0; i < N; i++)
		{
			B(k, i) = Binornd::get(PI(k));
		}
	}

	for (int i = 0; i < N; i++)
	{
		post_PI.col(i) << PI;
	}

	cout << "** Layer initialization complete **" << endl;
}

void DLLayer::CompleteSampler()
{
	// Sample PI
	// Sample B
	// Sample Gammas

	// If sampleD ==  true
	// Sample D

	// Sample S
	// Sample Bias
}

void DLLayer::RunGibbs(int iters)
{
	int burn_ins = min(10, (int)iters/2);
	int c_iter;
	for (c_iter = 0; c_iter < burn_ins; c_iter++)
	{
		CompleteSampler();
	}

	cout << "** Burn_ins complete **" << endl;

	for (; c_iter < iters; c_iter++)
	{
		/*
		If debugging
		display "Y_approx"
		*/

		// Y_approx = ??

		// Calculate MSE

		CompleteSampler();
	}

	trained = true;
	cout << "** All Gibbs iterations complete **" << endl;
}
