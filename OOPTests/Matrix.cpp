#include "Matrix.h"

void Matrix::printData(){
	for each (int i in data)
	{
		cout << i << " " << endl;
	}
}
Matrix::Matrix()
{
}


Matrix::~Matrix()
{
	data.clear();
	cout << "Matrix object destroyed" << endl;
}
