#pragma once

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <fstream>

#include <map>
#include <unordered_map>
#include <unordered_set>
#include "Float2D.h"

using namespace std;
using namespace cv;

class Utilities
{
private:
	static map<string, int> groupCounts;
	static map<string, vector<string> > groupedImages;
public:	
	Utilities();	
	//static vector<string> GetAllFiles(string folder);
	static void DisplayMat(Mat& image, string s="");
	static vector<string> GetAllFiles(string imageCategory);
	~Utilities();
};

