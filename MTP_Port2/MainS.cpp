#include "CommonHeader.h"

using namespace cv;
using namespace std;

Timer timer;

int main( int argc, char** argv )
{
	ImLoader imloader;
	Mat image = imloader.LoadImage(1);

	int reduceTo = 64;
	Mat dimage;
	resize(image, dimage, Size(reduceTo, reduceTo));

	Utilities::DisplayMat(dimage);

	// My code
	timer.start();
	float **dataMatrix = new float*[reduceTo];
	for (int i = 0; i < reduceTo; i++) {
		dataMatrix[i] = new float[reduceTo];
		for (int j = 0; j < reduceTo; j++) {
			dataMatrix[i][j] = (float)image.ptr(i)[j] / 255.0f;
		}
	}
	timer.stop();

	del2D(dataMatrix, reduceTo);
	
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}