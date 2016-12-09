#include "DLLayer.h"

void DLLayer::Init()
{

}

DLLayer::DLLayer()
{
}

DLLayer::DLLayer(MatrixXd& fMat, DLConfig config) : M(fMat.rows()), N(fMat.cols()), K(config.K), 
													Y(fMat), D(MatrixXd(M, K)), S(MatrixXd(K, N)),
													B(MatrixXd(K, N)), PI(VectorXd(K))
{
	cout << "Into DLLAyer coonst." << endl;
	gdist = gamma_distribution<double>(config.a_d, config.b_d);
	cout << "Out of DLLAyer coonst." << endl;	
}


DLLayer::~DLLayer()
{
}
