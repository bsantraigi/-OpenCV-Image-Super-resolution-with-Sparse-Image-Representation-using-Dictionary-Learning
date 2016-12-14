#include "CommonHeader.h"
#define ck(s) std::cout << s << endl
using namespace cv;
using namespace std;

Timer timer;

typedef Eigen::Matrix<bool, -1, -1> MatrixXb;

int main( int argc, char** argv )
{	
	ImLoader imloader(32, 4);
	//Mat image = imloader.LoadImage(1, 32);
	//Utilities::DisplayMat(image);

	MatrixXd fMat = imloader.GetDataMatrix(10);
	//imloader.UnPatchImage(fMat, 0);

	MatrixXd a = MatrixXd::Zero(2, 3);
	cout << "TestMat:" << endl << a << endl;

	// My code
	timer.start();

	DLConfig config1;
	/*MatrixXd B(3, 3);
	B << 1, 2, 3, 4, 50, 6, 7, 8, 9;
	cout << "B:" << endl << B << endl;
	cout << endl;

	MatrixXd Bt = B.transpose();
	MatrixXd C = B*Bt;
	cout << "Binv: " << endl << C << endl;
	cout << endl;*/

	DLLayer layer1(fMat, config1);
	layer1.RunGibbs(15);

	timer.stop();
	
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}