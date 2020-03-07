#include "ImageUtils1.h"

void imageTranslation(cv::Mat* inputImage, cv::Mat* outputImage, int x, int y)
{

	int inputWidth = inputImage->cols;
	int inputHeight = inputImage->rows;

	// Initialize the outputImage
	*outputImage = cv::Mat::zeros(cv::Size(inputWidth, inputHeight), CV_8UC3);

	for (int row = 0; row < inputHeight; row++)
	{
		for (int col = 0; col < inputWidth; col++)
		{
			// move the x coordinate
			int newX = row + x;
			// move the y coordinate
			int newY = col + y;
			// move current pixel to (newX, newY)
			if ((newX >= 0) && (newX < inputHeight))
			{
				if ((newY >=0) && (newY < inputWidth))
				{
					outputImage->at<cv::Vec3b>(newX, newY) = inputImage->at<cv::Vec3b>(row, col);
				}
			}
		}
	}

}

void imageRotation(cv::Mat* inputImage, cv::Mat* outputImage, int degree)
{
	int inputWidth = inputImage->cols;
	int inputHeight = inputImage->rows;
	*outputImage = cv::Mat::zeros(cv::Size(inputWidth, inputHeight), CV_8UC3);

	for (int row = 0; row < inputHeight; row++)
	{
		for (int col = 0; col < inputWidth; col++)
		{
			float radians = degree * (M_PI / 180);
			int newX = row * cos(radians) - col * sin(radians);
			int newY = row * sin(radians) + col * cos(radians);

			// move current pixel to (newX, newY)
			if ((newX >= 0) && (newX < inputHeight))
			{
				if ((newY >= 0) && (newY < inputWidth))
				{
					outputImage->at<cv::Vec3b>(newX, newY) = inputImage->at<cv::Vec3b>(row, col);
				}
			}


		}
	}
}

void imageShear(cv::Mat* inputImage, cv::Mat* outputImage, float horizental, float vertical)
{
	int inputWidth = inputImage->cols;
	int inputHeight = inputImage->rows;

	*outputImage = cv::Mat::zeros(cv::Size(inputWidth, inputHeight), CV_8UC3);

	for (int row = 0; row < inputHeight; row++)
	{
		for (int col = 0; col < inputWidth; col++)
		{
			//shear horizental
			// move the x coordinate
			int newX = floor(row + vertical * col);
			// move the y coordinate
			int newY = col;

			//shear vertical
			newY += floor(horizental * newX);

			// move current pixel to (newX, newY)
			if ((newX >= 0) && (newX < inputHeight))
			{
				if ((newY >= 0) && (newY < inputWidth))
				{
					outputImage->at<cv::Vec3b>(newX, newY) = inputImage->at<cv::Vec3b>(row, col);
				}
			}
		}
	}

}
