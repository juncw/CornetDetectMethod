#include "cornerDetectH.h"

/*Harris Corner Detect*/
int quailtyLevel = 10;
void crrdet::cornerDetectHarris(const Mat& source, Mat& output, double alpha, int quailtyLevel)
{
	Mat gray;
	if (source.channels() == 3) {
		cvtColor(source, gray, CV_64F);
	}
	else {
		gray = source.clone();
	}
	gray.convertTo(gray, CV_64F);

	Mat xKernel = (Mat_<double>(1, 3) << -1, 0, 1);
	Mat yKernel = xKernel.t();
	Mat Ix, Iy;
	filter2D(gray, Ix, CV_64F, xKernel);
	filter2D(gray, Iy, CV_64F, yKernel);

	Mat Ix2, Iy2, Ixy;
	Ix2 = Ix.mul(Ix);
	Ixy = Ix.mul(Iy);
	Iy2 = Iy.mul(Iy);

	Mat gaussKernel = getGaussianKernel(7, 1);
	filter2D(Ix2, Ix2, CV_64F, gaussKernel);
	filter2D(Ixy, Ixy, CV_64F, gaussKernel);
	filter2D(Iy2, Iy2, CV_64F, gaussKernel);

	Mat matrixMR(gray.size(), gray.type());
	for (int x = 0; x < gray.rows; ++x) {
		for (int y = 0; y < gray.cols; ++y) {
			double det = Ix2.at<double>(x, y)*Iy2.at<double>(x, y) - Ixy.at<double>(x, y)*Ixy.at<double>(x, y);
			double trace = Ix2.at<double>(x, y) + Iy2.at<double>(x, y);
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
	double qL = 1.0 * quailtyLevel / 100000;
	double thresh = qL*maxStrength;
	cornerMap = matrixMR > thresh;
	//threshold(matrixMR, cornerMap, thresh, 255, THRESH_BINARY);
	bitwise_and(cornerMap, localMax, cornerMap);

	output = cornerMap.clone();
}
void crrdet::drawCornerOnImage(Mat& source, Mat& output)
{
	Mat_<uchar>::const_iterator it = output.begin<uchar>();
	Mat_<uchar>::const_iterator itd = output.end<uchar>();

	for (int i = 0; it != itd; it++, i++) {
		if (*it) {
			circle(source, Point(i%output.cols, i/output.cols), 3, Scalar(255, 0, 0), 1);
		}
	}
}
void crrdet::onChangeHarris(int, void*)
{
	Mat source = imread("..//images//lena.jpg");
	/* harris corner detection*/

	//Mat HarrisCorSource = Mat::zeros(source.size(), CV_8UC1);
	Mat HarrisCorSource = source.clone();
	
	Mat outputHarris;
	cornerDetectHarris(source, outputHarris, 0.04, quailtyLevel);
	drawCornerOnImage(HarrisCorSource, outputHarris);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
	imshow("Harris_Detect", HarrisCorSource);
}
void crrdet::runHarrisDetect()
{
	quailtyLevel = 10;
	namedWindow("Harris_Detect");
	createTrackbar("cornerNum", "Harris_Detect", &quailtyLevel, 1000, onChangeHarris);
	waitKey(0);
}
/* Shi_Tomasi corner Detect*/
int currNum = 0;
void crrdet::onChangeTomasi(int, void*) {
	Mat source, gray, output;

	source = imread("..//images//lena.jpg");
	if (source.channels() != 1) {
		cvtColor(source, gray, CV_RGB2GRAY);
	}
	else {
		gray = source.clone();
	}
	vector<Point2f> corner;
	goodFeaturesToTrack(gray, corner, currNum, 0.01, 10, Mat());

	Mat corner_det = Mat(gray.size(), gray.type());
	output = source.clone();
	for (int i = 0; i < corner.size(); ++i) {
		circle(output, corner[i], 3, Scalar(0, 255, 0), 1);
	}
	
	imshow("Shi-Tomasi", output);
}
void crrdet::ShiTomasiCorDetect()
{
	currNum = 30;
	namedWindow("Shi-Tomasi");
	createTrackbar("cornerName", "Shi-Tomasi", &currNum, 1000, onChangeTomasi);
	waitKey(0);
}