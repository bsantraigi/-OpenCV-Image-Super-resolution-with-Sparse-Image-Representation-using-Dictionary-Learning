#include "ImLoader.h"

ImLoader::ImLoader():ImLoader(16, 8, "Faces_easy", "D:/ProjectData/caltech101/101_ObjectCategories/") {}

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

vector<vector<double>> ImLoader::GetDataMatrix(int totalImg2Data)
{
	
	// prepare file list - ids only: 1:end - 1/count:end
	vector<string> flist = Utilities::GetAllFiles(this->folder);

	// decide what would be the size of data matrix - Calculate exact size of matrix in MB
	map<int, Mat> indices;
	int dataMatSize = 0;
	for (int i = 0; i < flist.size(); i += (flist.size() - 1) / (totalImg2Data - 1)) {
		indices[i] = LoadImage(flist[i], reduceTo);
		dataMatSize += (indices[i].rows - patchSize + 1)*(indices[i].cols - patchSize + 1);
	}
	// Call loadimage with each id

	// prepare and return datamatrix or Y
	vector<vector<double> > dataMatrix(patchSize*patchSize, vector<double>(dataMatSize, 0));
	int from = 0;
	for(map<int, Mat>::iterator it = indices.begin(); it != indices.end(); it++)
	{		
		from = PatchImage(dataMatrix, from, it->second);
	}
	DisplayFloat(dataMatrix, "DataMat");
	return dataMatrix;
}

Mat ImLoader::LoadImage(int id, int reduceTo)
{
	char imname[100];
	string fpath;
	sprintf(imname, "/image_%04d.jpg", id);
	fpath = string(this->path.c_str()).append(imname);
	return LoadImage(fpath, reduceTo);
}
Mat ImLoader::LoadImage(string fpath, int reduceTo) 
{
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
					dataMatrix[u*patchSize + v][from] = (double)image.ptr(i + v)[j + u]/255.0f;
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
	
	return from;
}

void ImLoader::DisplayFloat(vector<vector<double>>& fImage, string s)
{
	Float2D f2d(fImage);
	double** fMat = f2d.get();
	Mat image = Mat(fImage.size(), fImage[0].size(), CV_64F, fMat);
	Utilities::DisplayMat(image, s);	
}
