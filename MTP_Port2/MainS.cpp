#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <chrono>
#define del2D(mat,n) for(int i=0;i<n;i++){delete [] mat[i];}


using namespace std::chrono;
using namespace cv;
using namespace std;
class Timer {
	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;
public:
	void start() {
		t1 = high_resolution_clock::now();
	}
	void stop() {
		t2 = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(t2 - t1).count();
		cout << "Time Elapsed: " << duration << endl;;
	}
};

Timer timer;

int main( int argc, char** argv )
{
    Mat image;
	string path = "D:/Users/Bishal Santra/Documents/MATLAB/MTP/neural_generative/caltech101/101_ObjectCategories/Faces_easy/";
	char imname[100];
	sprintf(imname, "image_%04d.jpg", 1);
	path = path.append(imname);
	cout << path << endl;
    image = imread(path, IMREAD_COLOR); // Read the file

    if( image.empty() ) // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl ;
        return -1;
    }

	int reduceTo = 64;
	Mat dimage;
	resize(image, dimage, Size(reduceTo, reduceTo));

    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( "Display window", dimage ); // Show our image inside it.

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