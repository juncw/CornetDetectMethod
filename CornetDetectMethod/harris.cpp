#include "cornerDetectH.h"

void crrdet::cornerDetectHarris(const Mat& source, Mat& output, double alpha)
{
	Mat gray;
	if (source.channels() == 3) {
		cvtColor(source, gray, CV_64F);
	}
	else {
		gray = source.clone();
	}
	Mat xKernel = (Mat_<double>(1, 3) << -1, 0, 1);
	Mat yKernel = xKernel.t();
	Mat Ix, Iy;
	filter2D(source, Ix, CV_64F, xKernel);
	filter2D(source, Iy, CV_64F, yKernel);

	Mat Ix2, Iy2, Ixy;
	Ix2 = Ix.mul(Ix);
	Ixy = Ix.mul(Iy);
	Iy2 = Iy.mul(Iy);

	Mat gaussKernel = getGaussianKernel(7, 1);
	filter2D(Ix2, Ix2, CV_64F, gaussKernel);
	filter2D(Ixy, Ixy, CV_64F, gaussKernel);
	filter2D(Iy2, Iy2, CV_64F, gaussKernel);

	Mat matrixMR(gray.size(), CV_64F);
	for (int x = 0; x < gray.rows; ++x) {
		for (int y = 0; y < gray.cols; ++y) {
			double det = Ix2.at<double>(x, y)*Ix2.at<double>(x, y)*Iy2.at<double>(x, y)*Iy2.at<double>(x, y) - \
				Ixy.at<double>(x, y)*Ixy.at<double>(x, y);
			double trace = Ix2.at<double>(x, y)*Ix2.at<double>(x, y) + Iy2.at<double>(x, y)*Iy2.at<double>(x, y);
			matrixMR.at<double>(x, y) = det - alpha*trace*trace;
		}
	}

	// threshold
	double maxStrength;
	minMaxLoc(matrixMR, NULL, &maxStrength, NULL, NULL);
	Mat dilated, localMax;
	dilate(matrixMR, dilated, Mat());
	compare(matrixMR, dilated, localMax, CMP_EQ);
	

	Mat cornerMap;
	double quailtyLevel = 0.01;
	double thresh = quailtyLevel*maxStrength;
	threshold(matrixMR, cornerMap, thresh, 255, THRESH_BINARY);
	cornerMap.convertTo(cornerMap, CV_8U);
	bitwise_and(cornerMap, localMax, cornerMap);

	output = cornerMap.clone();
	
}
void crrdet::drawCornerOnImage(Mat& source, Mat& output)
{
	Mat_<uchar>::const_iterator it = output.begin<uchar>();
	Mat_<uchar>::const_iterator itd = output.end<uchar>();

	for (int i = 0; it != itd; it++, i++) {
		if (*it) {
			circle(source, Point(i%output.cols, i/output.cols), 2, Scalar(255, 0, 0), 1);
		}
	}
}