#pragma once

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

class Utilities
{
private:
	//static std::wstring s2ws(const std::string & s);
public:	
	Utilities();	
	//static vector<string> GetAllFiles(string folder);
	static void DisplayMat(Mat& image, string s="");
	~Utilities();
};

