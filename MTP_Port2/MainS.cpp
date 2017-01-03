#include "CommonHeader.h"
#define ck(s) std::cout << s << endl
using namespace cv;
using namespace std;

Timer timer;
DLLayer layer1;
DLLayer layer2;

bool CTRL_C_Handled = false;

BOOL WINAPI consoleHandler(DWORD signal) {

	if (signal == CTRL_C_EVENT){
		if (!CTRL_C_Handled){
			printf("SOFT EXIT\n");
			CTRL_C_Handled = true;
			if (layer1.running){
				layer1.Break();
			}
			else if (layer2.running){
				layer2.Break();
			}
		}
		else{
			printf("HARD EXIT\n");
			exit(1);
		}
	}

	return TRUE;
}

int main()
{	
	if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
		printf("\nERROR: Could not set control handler");
		return 1;
	}
	int prop_imsize = 128;
	int prop_patchsize = 8;
	int prop_imcount = 5;

	ImLoader imloader(prop_imsize, prop_patchsize);
	MatrixXd fMat = imloader.GetDataMatrix(prop_imcount);
	
	DLConfig config1;
	layer1 = DLLayer(fMat, config1);
	layer1.RunGibbs(50, 1);

	CTRL_C_Handled = false;

	MatrixXd SB1 = MatrixXd::Zero(config1.K, fMat.cols());
	layer1.GetSB(SB1);
	layer2 = DLLayer(layer1.GetPostPI(), config1);
	layer2.RunGibbs(50, 2);

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