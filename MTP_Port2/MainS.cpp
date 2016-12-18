#include "CommonHeader.h"
#define ck(s) std::cout << s << endl
using namespace cv;
using namespace std;

Timer timer;

int main()
{	
	ImLoader imloader(256, 8);
	MatrixXd fMat = imloader.GetDataMatrix(5);
	

	DLConfig config1;
	DLLayer layer1(fMat, config1);
	layer1.RunGibbs(30);

	MatrixXd Y_approx = layer1.GetY_approx();
	imloader.UnPatchImage(fMat, 0);
	imloader.UnPatchImage(Y_approx, 0);
	imloader.UnPatchImage(fMat, 1);
	imloader.UnPatchImage(Y_approx, 1);
	imloader.UnPatchImage(fMat, 2);
	imloader.UnPatchImage(Y_approx, 2);
	
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}