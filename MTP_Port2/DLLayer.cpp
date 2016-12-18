#include "DLLayer.h"

DLLayer::DLLayer(MatrixXd& fMat, DLConfig config)
{
	// Copy the data, config arugments to class variables
	Y = fMat;

	this->config = DLConfig(config);

	// Call Init
	Init();
}

DLLayer::~DLLayer()
{
}

void DLLayer::GetSB(MatrixXd& SB)
{
	for (int k = 0; k < K; k++)
	{
		for (int i = 0; i < N; i++)
		{
			SB(k, i) = S(k, i)*B(k, i);
		}
	}
}

MatrixXd DLLayer::GetY_approx()
{
	MatrixXd SB(K, N);
	GetSB(SB);
	MatrixXd biasM = bias.replicate(1, N);
	return D*SB + biasM;
}

double DLLayer::MSE()
{
	return (Y - GetY_approx()).norm() / sqrt(M*N);
}

void DLLayer::Init(){
	Utilities::prettyStart("Layer Initialization STARTING");
	
	layerTimer.start();
	M = (Y.rows());
	N = (Y.cols());
	K = (config.K);

	D = (MatrixXd(M, K));
	S = (MatrixXd(K, N));

	B = (MatrixXi(K, N));
	PI = (VectorXd(K));	

	post_PI = MatrixXd(K, N);
	
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
	layerTimer.stop();
	Utilities::prettyEnd("Layer Initialization COMPLETE");
}

void DLLayer::RunGibbs(int iters)
{
	Utilities::prettyStart("Gibbs Sampling STARTING");

	int burn_ins = min(10, (int)iters / 2);

	for (; c_iter < burn_ins; c_iter++)
	{
		CompleteSampler();
	}

	cout << "** Burn_ins complete **" << endl;

	for (; c_iter < iters; c_iter++)
	{
		// Calculate MSE
		CompleteSampler();
	}

	trained = true;
	Utilities::prettyEnd("Gibbs Sampling COMPLETE");
}

void DLLayer::CompleteSampler()
{
	double tpi, tb, tgam, td, ts, tbias;

	// Sample PI
	layerTimer.start();
	SamplePI();
	layerTimer.stop(tpi);

	// Sample B
	layerTimer.start();
	SampleB();
	layerTimer.stop(tb);

	// Sample Gammas
	layerTimer.start();
	SampleGammas();
	layerTimer.stop(tgam);

	// If sampleD ==  true
	// Sample D
	layerTimer.start();
	SampleD();
	layerTimer.stop(td);

	// Sample S
	layerTimer.start();
	SampleS();
	layerTimer.stop(ts);

	// Sample Bias
	layerTimer.start();
	SampleBias();
	layerTimer.stop(tbias);

	printf("%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\tMSE:%0.5f\n", tpi/1000, tb/1000, tgam/1000, td/1000, ts/1000, tbias/1000, MSE());
}

void DLLayer::SamplePI()
{
	for (int k = 0; k < K; k++)
	{
		double s = B.row(k).sum();
		PI(k) = Betarnd::get(config.a_pi + s, config.b_pi + N - s);
	}
}
void DLLayer::SampleB()
{
	MatrixXd SB(K, N);
	GetSB(SB);
	for (int i = 0; i < N; i++)
	{
		VectorXd SBi = SB.col(i);
		for (int k = 0; k < K; k++)
		{
			B(k, i) = 1;
			VectorXd delY;
			if (k > 0){
				delY = Y.col(i) - bias - D.leftCols(k - 1)*SBi.topRows(k - 1);
			}
			else{
				delY = VectorXd::Zero(M);
			}
			if (k != K - 1){
				delY = delY - D.rightCols(K - k - 1)*SBi.bottomRows(K - k - 1);
			}
			double dkn2 = D.col(k).norm();
			double arg = (S(k, i) * S(k, i))*dkn2*dkn2 - 2 * S(k, i)*(D.col(k).dot(delY));
			double p1 = PI(k) *exp(-gam_n*arg / 2);

			B(k, i) = 0;
			double p0 = (1 - PI(k));
			p1 = p1 / (p1 + p0);
			B(k, i) = Binornd::get(p1);
			post_PI(k, i) = p1;
		}
	}
}
void DLLayer::SampleGammas()
{
	double alpha, beta, tau;

	// Sample gam_d
	alpha = K*M / 2 + config.a_d;
	tau = D.norm();
	beta = 0.5*tau*tau + config.b_d;
	gam_d = Gamrnd::get(alpha, beta);

	// Sample gam_s	
	alpha = K*N / 2 + config.a_s;
	tau = S.norm();
	beta = 0.5*tau*tau + config.b_s;
	gam_s = Gamrnd::get(alpha, beta);
	
	// Sample gam_n
	alpha = M*N / 2 + config.a_n;
	MatrixXd SB(K, N);
	GetSB(SB);
	tau = (Y - D*SB - bias.replicate(1, N)).norm();
	beta = 0.5*tau*tau + config.b_n;
	gam_n = Gamrnd::get(alpha, beta);
	
	// Sample gam_bias
	alpha = M / 2 + config.a_bias;
	tau = bias.norm();
	beta = 0.5*tau*tau + config.b_bias;
	gam_bias = Gamrnd::get(alpha, beta);
}
void DLLayer::SampleD()
{
	MatrixXd SB(K, N);
	GetSB(SB);
	MatrixXd biasM = bias.replicate(1, N);
	for (int k = 0; k < K; k++)
	{
		MatrixXd Y_approx;
		if (k > 0){
			Y_approx = D.leftCols(k - 1)*SB.topRows(k - 1) + biasM;
		}
		else{
			Y_approx = MatrixXd::Zero(M, N);
		}
		if (k != K - 1){
			Y_approx = Y_approx + D.rightCols(K - k - 1)*SB.bottomRows(K - k - 1) + biasM;
		}
		MatrixXd delY = Y - Y_approx;

		double sk2 = SB.row(k).norm();
		double prk = gam_n * sk2 * sk2 + gam_d;
		VectorXd muDk = (gam_n / prk)*(delY*SB.row(k).transpose());
		D.col(k) << Mvnrnd::get(muDk, (1 / prk)*MatrixXd::Identity(M, M));
	}
}
void DLLayer::SampleS()
{
	MatrixXd Ik = MatrixXd::Identity(K, K);
	for (int i = 0; i < N; i++)
	{
		MatrixXd DB(M, K);
		for (int m = 0; m < M; m++)
		{
			for (int k = 0; k < K; k++)
			{
				DB(m, k) = D(m, k) * B(k, i);
			}
		}
		MatrixXd DBt = DB.transpose();
		MatrixXd C = gam_n*(DBt*DB);
		for (int k = 0; k < K; k++)
		{
			C(k, k) += gam_s;
		}
		C = C.inverse();

		VectorXd muSi = C*(gam_n*DBt*(Y.col(i) - bias));
		S.col(i) = Mvnrnd::get(muSi, C);
	}
}
void DLLayer::SampleBias()
{
	double G = N*gam_n + gam_bias;
	MatrixXd SB(K, N);
	GetSB(SB);

	VectorXd mu = (gam_n / G)*((Y - D*SB).rowwise().sum());
	bias << Mvnrnd::get(mu, (1 / G)*MatrixXd::Identity(M, M));
}