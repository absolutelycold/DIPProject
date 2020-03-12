#include <iostream>
#include "ImageUtils0.h"
#include "ImageUtils1.h"
int main()
{
    cv::Mat sourceImage = cv::imread("./bridge.pgm");
	cv::Mat outImage;
	//alternativeLineReduction(&sourceImage, &outImage, 100, 100);
	//biLinearInterpolation(&sourceImage, &outImage);
	//fractionEnlargement(&sourceImage, &outImage, 400, 600);
	//nearestEnlargement(&sourceImage, &outImage);
	//negativeImage(&sourceImage, &outImage);
	//pixelReplication(&sourceImage, &outImage, 2);
	//bicubicInterpolation(&sourceImage, &outImage);
	//imageTranslation(&sourceImage, &outImage, -50, 20);
	//imageRotation(&sourceImage, &outImage, 45);
	//imageShear(&sourceImage, &outImage, 0.2, 0.2);
	//averageFilter(&sourceImage, &outImage, 9);
	//medianFilter(&sourceImage, &outImage, 6);
	binarizationFilter(&sourceImage, &outImage, 150);
	//int test[] = { 432, 3, 4324, 43, 432, 54, 4 };
	//bolbSortInt(test, 7);
	if (sourceImage.empty())
	{
		std::cout << "The pic cannot read.\n";
		return EXIT_FAILURE;
	}

	if (outImage.empty())
	{
		std::cout << "Generate Empty pic\n";
		return EXIT_FAILURE;
	}

	cv::imshow("source image", sourceImage);
	cv::imshow("out image", outImage);
	cv::waitKey();
	return EXIT_SUCCESS;
}
 