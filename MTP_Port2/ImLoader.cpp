#include "ImLoader.h"

ImLoader::ImLoader():ImLoader(16, 8, "Faces_easy", "D:/Users/Bishal Santra/Documents/MATLAB/MTP/neural_generative/caltech101/101_ObjectCategories/") {}

ImLoader::ImLoader(int reduceTo, int patchSize,  string folder, string path) : folder(folder), path(path)
{
	this->folder = folder;
	this->path = path + folder;
	this->patchSize = 8;
	this->reduceTo = reduceTo;
	redSize = Size(reduceTo, reduceTo);
	this->patchSize = patchSize;
}


ImLoader::~ImLoader()
{
}

vector<vector<double>> ImLoader::GetDataMatrix()
{
	vector<vector<double> > dataMatrix(patchSize*patchSize, vector<double>(1000, 0));
	int from = 0;
	for (int f = 0; f < 2; f++) {
		Mat image = LoadImage(f+1, reduceTo);
		from = PatchImage(dataMatrix, from, image);
	}

	return dataMatrix;
}

Mat ImLoader::LoadImage(int id, int reduceTo)
{
	char imname[100];
	string fpath;
	sprintf(imname, "/image_%04d.jpg", id);
	fpath = string(this->path.c_str()).append(imname);
	Mat image = imread(fpath, IMREAD_COLOR); // Read the file

	if (image.empty()) // Check for invalid input
	{
		cout << "Could not open or find the image: " << fpath << std::endl;
		return Mat();
	}
	if (reduceTo > 0) {
		Mat dimage;
		resize(image, dimage, Size(reduceTo, reduceTo));
		return dimage;
	}
	else {
		return image;
	}
}

int ImLoader::PatchImage(vector<vector<double> > &dataMatrix, int from, Mat& image)
{
	int start = from;
	int row = image.rows, col = image.cols;
	for (int i = 0; i < row - patchSize + 1; i++)
	{
		for (int j = 0; j < col - patchSize + 1; j++)
		{
			for (int u = 0; u < patchSize; u++)
			{
				for (int v = 0; v < patchSize; v++)
				{
					dataMatrix[u*patchSize + v][from] = image.ptr(i + v)[j + u]/255;
				}
			}
			from++;
		}
	}

	//ECHO HERE - TOBE REMOVED
	
	/*cout.precision(3);
	cout << "Printing Image:" << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << image.ptr(i)[j] / 255.0f << fixed << " ";
		}
		cout << endl;
	}
	cout << "Printing Data mat:" << endl;
	for (int i = 0; i < patchSize*patchSize; i++) {
		for (int c = start; c < from; c++) {
			cout << dataMatrix[i][c] << fixed << " ";
		}
		cout << endl;
	}*/
	DisplayFloat(dataMatrix, "DataMat");
	return from;
}

void ImLoader::DisplayFloat(vector<vector<double>>& fImage, string s)
{
	Float2D f2d(fImage);
	double** fMat = f2d.get();
	cout << sizeof(double) << endl;
	Mat image = Mat(fImage.size(), fImage[0].size(), CV_32FC1, fMat);
	Utilities::DisplayMat(image, s);	
}
