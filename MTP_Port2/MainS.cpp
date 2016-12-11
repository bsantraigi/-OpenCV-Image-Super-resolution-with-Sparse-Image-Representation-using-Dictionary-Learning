#include "CommonHeader.h"
#define ck(s) std::cout << s << endl
using namespace cv;
using namespace std;

Timer timer;

typedef Eigen::Matrix<bool, -1, -1> MatrixXb;

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
	MatrixXb B(2, 2);
	B << 1, 0, 0, 1;
	cout << "B" << endl << B << endl;
	B *= MatrixXb::Ones(2, 2);
	cout << "B" << endl << B << endl;
	cout << "B" << endl << B << endl;
	//DLLayer layer1(fMat, config1);

	timer.stop();
	
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}