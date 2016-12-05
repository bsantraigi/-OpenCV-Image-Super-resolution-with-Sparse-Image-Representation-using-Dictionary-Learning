#include "ImLoader.h"

ImLoader::ImLoader():ImLoader("Faces_easy", "D:/Users/Bishal Santra/Documents/MATLAB/MTP/neural_generative/caltech101/101_ObjectCategories/") {}

ImLoader::ImLoader(string folder = "Faces_easy", string path = "D:/Users/Bishal Santra/Documents/MATLAB/MTP/neural_generative/caltech101/101_ObjectCategories/") : folder(folder), path(path)
{
	redSize = Size(64, 64);
	this->folder = folder;
	this->path = path + folder;
}


ImLoader::~ImLoader()
{
}

vector<vector<float>> ImLoader::GetDataMatrix()
{
	vector<vector<float> > dataMatrix;	
	int fromCol = 0;
	for (int f = 0; f < 2; f++) {
		Mat image = LoadImage(f+1);
		PatchImage(dataMatrix, fromCol, image);
	}

	return dataMatrix;
}

Mat ImLoader::LoadImage(int id)
{
	cout << "Path set to: " << this->path << endl;
	char imname[100];
	string fpath;
	sprintf(imname, "/image_%04d.jpg", id);
	fpath = this->path.append(imname);
	cout << "Fpath: " << fpath << endl;
	Mat image = imread(fpath, IMREAD_COLOR); // Read the file
	
	if (image.empty()) // Check for invalid input
	{
		cout << "Could not open or find the image: " << fpath << std::endl;
		return Mat();
	}

	return image;
}

void ImLoader::PatchImage(vector<vector<float> > &dataMatrix, int from, Mat image)
{
}

void ImLoader::DisplayFloat(vector<vector<float>>& fImage)
{
	Float2D f2d(fImage);
	float** fMat = f2d.get();
	Mat image = Mat(fImage.size(), fImage[0].size(), CV_64FC4, fMat);
}
