#include "Wrapper.h"


Wrapper::Wrapper()
{
	cout << "Wrapper constructor" << endl;
	//matrix = Matrix();
	matrix.data.push_back(1);
	matrix.data.push_back(2);
	matrix.data.push_back(3);
	matrix.data.push_back(4);
	matrix.data.push_back(5);
	matrix.data.push_back(6);
	cout << "Wrapper Exit ctor" << endl;
}

void Wrapper::printData(){
	cout << "Printdata entry" << endl;
	matrix.printData();
	cout << "Printdata exit" << endl;
}

Wrapper::~Wrapper()
{
}
