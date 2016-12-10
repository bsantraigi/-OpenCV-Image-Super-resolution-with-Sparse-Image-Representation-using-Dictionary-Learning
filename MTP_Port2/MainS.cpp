#include "CommonHeader.h"
#define ck(s) std::cout << s << endl
using namespace cv;
using namespace std;

Timer timer;

int main( int argc, char** argv )
{	
	ImLoader imloader(8, 4);
	//Mat image = imloader.LoadImage(1, 32);
	//Utilities::DisplayMat(image);

	MatrixXd fMat = imloader.GetDataMatrix(5);
	imloader.UnPatchImage(fMat, 0);

	MatrixXd a = MatrixXd::Zero(2, 3);
	cout << "TestMat:" << endl << a << endl;

	// My code
	timer.start();

	DLConfig config1;
	
	DLLayer layer1(fMat, config1);

	timer.stop();
	
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}