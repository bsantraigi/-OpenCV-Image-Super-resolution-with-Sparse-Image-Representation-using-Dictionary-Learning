#pragma once
#include "CommonHeader.h"


using namespace std;
#define del2D(mat,n) for(int i=0;i<n;i++){delete [] mat[i];}
class Float2D
{
	float **fMatrix;
	int row, col;
public:
	Float2D::Float2D(vector<vector<float>>& fVec);
	~Float2D();
	float** get();
};

