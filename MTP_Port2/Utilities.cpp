#include "Utilities.h"


Utilities::Utilities()
{
}

void Utilities::DisplayMat(Mat &image, string s)
{
	if (s.size() == 0) {
		namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
		imshow("Display window", image); // Show our image inside it.
	}
	else {
		namedWindow(s, WINDOW_AUTOSIZE); // Create a window for display.
		imshow(s, image); // Show our image inside it.
	}
}


Utilities::~Utilities()
{
}
