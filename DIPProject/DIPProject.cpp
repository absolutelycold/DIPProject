// DIPProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ImageUtils.h"
int main()
{
    cv::Mat sourceImage = cv::imread("./lena.jpg");
	cv::Mat outImage;
	ImageUtils::alternativeLineReduction(&sourceImage, &outImage, 100, 100);
	if (sourceImage.empty())
	{
		std::cout << "The pic cannot read.\n";
		return EXIT_FAILURE;
	}

	cv::imshow("source image", sourceImage);
	cv::imshow("out image", outImage);
	cv::waitKey();
	return EXIT_SUCCESS;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
 