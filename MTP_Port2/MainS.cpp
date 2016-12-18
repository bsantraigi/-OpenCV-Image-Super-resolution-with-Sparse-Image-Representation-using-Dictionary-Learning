#include "CommonHeader.h"
#define ck(s) std::cout << s << endl
using namespace cv;
using namespace std;

Timer timer;

int main()
{	
	ImLoader imloader(64, 8);
	//Mat image = imloader.LoadImage(1, 32);
	//Utilities::DisplayMat(image);

	MatrixXd fMat = imloader.GetDataMatrix(10);
	

	DLConfig config1;
	DLLayer layer1(fMat, config1);
	layer1.RunGibbs(15);

	imloader.UnPatchImage(fMat, 0);
	
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}