
#include "cornerDetectH.h"

int main(void) 
{
	Mat source = imread("..//images//lena.jpg");
	Mat outputHarris;
	crrdet::cornerDetectHarris(source, outputHarris, 0.001);
	crrdet::drawCornerOnImage(source, outputHarris);

	imshow("gray_image", source);
	waitKey(0);
	return 0;

}