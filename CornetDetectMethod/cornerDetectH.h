#ifndef CORNERDETECTH_H_
#define CORNERDETECTH_H_

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

namespace crrdet {


	void cornerDetectHarris(const Mat& source, Mat& output, double alpha);
	void drawCornerOnImage(Mat& source, Mat& output);
}

#endif