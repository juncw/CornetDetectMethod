
#include "cornerDetectH.h"

int main(void) 
{
	Mat source = imread("..//images//buliding.png");
	Mat image = source.clone();

	Mat outputHarris;
	crrdet::cornerDetectHarris(source, outputHarris, 0.01);
	crrdet::drawCornerOnImage(source, outputHarris);
	imshow("gray_image2", source);
	/*waitKey(0);*/

	cvtColor(image, image, CV_RGB2GRAY);
	cornerHarris(image, image, 3, 3, 0.01);
	threshold(image, image, 0.001, 255, THRESH_BINARY);
	imshow("cornerHarris", image);
	waitKey(0);

	return 0;
}