#include <iostream>
#include "ImageUtils0.h"
#include "ImageUtils1.h"
#include "ImageUtils2.h"
#include "ImageUtils3.h"

int main()
{
	cv::Mat sourceImage = cv::imread("/home/justice/Pictures/rampr128.pgm", cv::IMREAD_GRAYSCALE);
	//cv::Mat sourceImage = cv::imread("/home/justice/Pictures/lena.jpg");
	cv::Mat outImage;
	//alternativeLineReduction(&sourceImage, &outImage, 100, 100);
	//biLinearInterpolation(&sourceImage, &outImage);
	//fractionEnlargement(&sourceImage, &outImage, 400, 600);
	//nearestEnlargement(&sourceImage, &outImage);
	//negativeImage(&sourceImage, &outImage);
	//pixelReplication(&sourceImage, &outImage, 2);
	//bicubicInterpolation(&sourceImage, &outImage);
	//imageTranslation(&sourceImage, &outImage, -50, 20);
	//imageRotation(&sourceImage, &outImage, 15);
	//imageShear(&sourceImage, &outImage, 0.2, 0.2);
	//averageFilter(&sourceImage, &outImage, 5);
	//medianFilter(&sourceImage, &outImage, 9);
	//binarizationFilter(&sourceImage, &outImage, 150);
	//laplacian1C(&sourceImage, &outImage);
	//sobel(&sourceImage, &outImage);
	//gamaCorrelation(&sourceImage, &outImage, 1);
	//histogramEqualization_GRAY(&sourceImage, &outImage, LOCAL_HISTOGRAM_EQUALIZATION);

	//int test[] = { 432, 3, 4324, 43, 432, 54, 4 };
	//bolbSortInt(test, 7);

	// Ideal Lowpass filter
	/*
	cv::Mat ideal = ILPF(sourceImage, 60);
	ideal = ideal(cv::Rect(0, 0, sourceImage.cols, sourceImage.rows));
	*/

	// Butterworth lowpass filter
	/*
	cv::Mat butterworth = BLPF(sourceImage, 30);
	butterworth = butterworth(cv::Rect(0, 0, sourceImage.cols, sourceImage.rows));
	*/

	// Gaussian lowpass filter
	/*
	cv::Mat gaussian = GLPF(sourceImage, 60);
	gaussian = gaussian(cv::Rect(0, 0, sourceImage.cols, sourceImage.rows));

	if (sourceImage.empty())
	{
		std::cout << "The pic cannot read.\n";
		return EXIT_FAILURE;
	}
	*/


	/*
	if (outImage.empty())
	{
		std::cout << "Generate Empty pic\n";
		return EXIT_FAILURE;
	}
	*/
	TwoDDFT(sourceImage);
	//cv::imshow("source image", sourceImage);

	//cv::imshow("out image", outImage);
	//cv::waitKey();
	
}
