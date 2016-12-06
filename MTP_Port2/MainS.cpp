#include "CommonHeader.h"

using namespace cv;
using namespace std;

Timer timer;

int main( int argc, char** argv )
{
	ifstream inf("rfiles/pointerList.list1");
	char a[80];
	while (!inf.eof()) {
		inf >> a;
		if (strcmp("Faces_easy", a) == 0) {			
			cout << a << " ";
			inf >> a;
			cout << a << endl;
		}
		else {
			inf >> a;
		}
	}
	inf.close();

	ImLoader imloader(16, 4);
	//Mat image = imloader.LoadImage(1, 32);
	//Utilities::DisplayMat(image);
	vector<vector<double>> fMat = imloader.GetDataMatrix();


	// My code
	timer.start();
	timer.stop();
	
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}