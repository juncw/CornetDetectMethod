#ifndef CORNERDETECTH_H_
#define CORNERDETECTH_H_

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


namespace crrdet {


	void cornerDetectHarris(const Mat& source, Mat& output, double alpha, int quailtyLevel);
	void drawCornerOnImage(Mat& source, Mat& output);
	void onChangeHarris(int, void*);
	void runHarrisDetect();

	void ShiTomasiCorDetect();
	void onChangeTomasi(int, void*);
	
}

#endif