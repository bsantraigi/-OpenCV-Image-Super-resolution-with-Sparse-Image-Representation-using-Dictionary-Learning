#pragma once
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define del2D(mat,n) for(int i=0;i<n;i++){delete [] mat[i];}

#include <Eigen/Dense>
using Eigen::MatrixXd;
using Eigen::VectorXd;

class Float2D
{
	double **fMatrix;
	int row, col;
public:
	// Property getter
	int rows() { return row; }
	int cols() { return col; }

	// constructors
	Float2D();
	Float2D(int M, int N);
	Float2D(vector<vector<double>>& fVec);
	Float2D(MatrixXd& fVec);

	// paranthesis operator overload -> 2D access operator
	double& operator()(unsigned int i, unsigned int j) {
		return fMatrix[i][j];
	}

	// Get float array pointer
	double** get();
	
	// Destructor
	~Float2D();
};

