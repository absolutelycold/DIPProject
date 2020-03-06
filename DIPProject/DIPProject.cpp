#include <iostream>
#include "ImageUtils.h"
int main()
{
    cv::Mat sourceImage = cv::imread("./lena.jpg");
	cv::Mat outImage;
	//ImageUtils::alternativeLineReduction(&sourceImage, &outImage, 100, 100);
	//ImageUtils::biLinearInterpolation(&sourceImage, &outImage);
	//ImageUtils::fractionEnlargement(&sourceImage, &outImage, 400, 600);
	//ImageUtils::nearestEnlargement(&sourceImage, &outImage);
	//ImageUtils::negativeImage(&sourceImage, &outImage);
	//ImageUtils::pixelReplication(&sourceImage, &outImage, 2);
	ImageUtils::bicubicInterpolation(&sourceImage, &outImage);
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
 