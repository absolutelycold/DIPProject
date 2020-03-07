#include <iostream>
#include "ImageUtils.h"
#include "ImageUtils1.h"
int main()
{
    cv::Mat sourceImage = cv::imread("./lena.jpg");
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
	imageShear(&sourceImage, &outImage, 0.3, 0);

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
 