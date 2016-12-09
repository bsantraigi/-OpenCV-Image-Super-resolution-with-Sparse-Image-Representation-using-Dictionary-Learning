#pragma once

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "Float2D.h"
#include "Utilities.h"

using namespace std;
using namespace cv;

#define del2D(mat,n) for(int i=0;i<n;i++){delete [] mat[i];}

#include <Eigen/Dense>
using Eigen::MatrixXd;
using Eigen::VectorXd;

class ImLoader
{
public:
	string folder, path;
	Size redSize;
	int patchSize, reduceTo;
	vector<int> imLocations;
	vector<int> rowList;
	vector<int> colList;
public:
	ImLoader();
	ImLoader(int reduceTo = 16, int patchSize = 8, string folder = "Faces_easy",
		string path = "D:/Users/Bishal Santra/Documents/MATLAB/MTP/neural_generative/caltech101/101_ObjectCategories/");
	~ImLoader();
	MatrixXd GetDataMatrix(int totalImage2Data = 2);
	Mat LoadImage(int id, int reduceTo = 0);
	Mat LoadImage(string fpath, int reduceTo);
	int PatchImage(MatrixXd& dataMatrix, int from, Mat &image);
	void UnPatchImage(MatrixXd& dataMatrix, int id);
	void DisplayFloat(MatrixXd& fImage, string s = "Default");
	void DisplayFloat(Float2D & f2d, string s = "Default");
};

