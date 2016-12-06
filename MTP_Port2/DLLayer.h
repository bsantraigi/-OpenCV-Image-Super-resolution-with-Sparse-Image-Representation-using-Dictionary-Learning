#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "DLConfig.h"

using namespace std;

class DLLayer
{
public:
	DLLayer();
	DLLayer(vector<vector<double> > &fMat, DLConfig config);
	~DLLayer();
};

