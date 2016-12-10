#include "DLLayer.h"

void DLLayer::Init()
{

}

DLLayer::DLLayer()
{
}

DLLayer::DLLayer(MatrixXd& fMat, DLConfig config)
{
	M = (fMat.rows());
	N = (fMat.cols());
	K = (config.K);

	D = (MatrixXd(M, K));
	S = (MatrixXd(K, N));

	B = (MatrixXb(K, N));
	PI = (VectorXd(K));
	Y = (MatrixXd(M, N));
	//cout << "fMat:" << endl << fMat << endl;
	Y << fMat;
	gam_d = Gamrnd::get(config.a_d, config.b_d);
	gam_s = Gamrnd::get(config.a_s, config.b_s);
	gam_n = Gamrnd::get(config.a_n, config.b_n);
	gam_bias = Gamrnd::get(config.a_bias, config.b_bias);

	VectorXd zmu = VectorXd::Zero(M);
	MatrixXd Id = MatrixXd::Identity(M, M);
	for (int k = 0; k < K; k++)
	{
		D.col(k) = Mvnrnd::get(zmu, (1/gam_d)*Id);		
	}

	zmu = VectorXd::Zero(K);
	MatrixXd Is = MatrixXd::Identity(K, K);
	for (int k = 0; k < K; k++)
	{
		S.col(k) = Mvnrnd::get(zmu, (1/gam_s)*Is);
	}

	bias = Mvnrnd::get(VectorXd::Zero(M), (1 / gam_bias)*Id);

	for (int k = 0; k < K; k++)
	{

	}
}


DLLayer::~DLLayer()
{
}
