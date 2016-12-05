#pragma once
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


using namespace std;
#define del2D(mat,n) for(int i=0;i<n;i++){delete [] mat[i];}
class Float2D
{
	double **fMatrix;
	int row, col;
public:
	Float2D::Float2D(vector<vector<double>>& fVec);
	~Float2D();
	double** get();
};

