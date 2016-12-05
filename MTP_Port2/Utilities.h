#pragma once

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class Utilities
{
public:	
	Utilities();
	static void DisplayMat(Mat& image, string s="");
	~Utilities();
};

