#pragma once

#include "CommonHeader.h"

#define del2D(mat,n) for(int i=0;i<n;i++){delete [] mat[i];}

using namespace cv;
using namespace std;

class ImLoader
{
public:
	string folder;
	string path;
	Size redSize;
public:
	ImLoader();
	ImLoader(string folder, string path);
	~ImLoader();
	vector<vector<float> > GetDataMatrix();
	Mat LoadImage(int id);
	void PatchImage(vector<vector<float>>& dataMatrix, int from, Mat image);
	void DisplayFloat(vector<vector<float> >& fImage);
};

