#pragma once
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#include "Timer.h"
#include "ImLoader.h"
#include "Float2D.h"
#include "Utilities.h"

#define del2D(mat,n) for(int i=0;i<n;i++){delete [] mat[i];}