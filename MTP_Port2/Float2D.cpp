#include "Float2D.h"

Float2D::Float2D(vector<vector<float>>& fVec): row(fVec.size()), col(fVec[0].size())
{
	fMatrix = new float*[row];
	for (size_t i = 0; i < row; i++)
	{
		fMatrix[i] = new float[col];
		for (size_t j = 0; j < col; j++)
		{
			fMatrix[i][j] = fVec[i][j];
		}
	}
}


Float2D::~Float2D()
{
	cout << "Deleting Float2D\n";
	del2D(fMatrix, row);
}

float ** Float2D::get()
{
	return fMatrix;
}
