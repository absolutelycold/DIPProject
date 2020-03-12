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


void averageFilter(cv::Mat* inputImage, cv::Mat* outputImage, int filterSize)
{
	int inputWidth = inputImage->cols;
	int inputHeight = inputImage->rows;

	int recycleWidth = inputWidth - filterSize + 1;
	int recycleHeight = inputHeight - filterSize + 1;

	*outputImage = cv::Mat::zeros(cv::Size(recycleWidth, recycleHeight), CV_8UC3);

	for (int i = 0; i < recycleHeight; i++)
	{
		for (int j = 0; j < recycleWidth; j++)
		{
			// For channel
			for (int channel = 0; channel < 3; channel++)
			{
				int average = 0;
				//For (filterSize x filterSize) filter
				for (int filterX = 0; filterX < filterSize; filterX++)
				{
					for (int filterY = 0; filterY < filterSize; filterY++)
					{
						average += inputImage->at<cv::Vec3b>(i + filterX, j + filterY)[channel];
					}
				}

				// Calculate the average:
				average /= (filterSize * filterSize);

				outputImage->at<cv::Vec3b>(i, j)[channel] = average;
			}
		}
	}
}

void medianFilter(cv::Mat* inputImage, cv::Mat* outputImage, int filterSize)
{
	int inputWidth = inputImage->cols;
	int inputHeight = inputImage->rows;

	int recycleWidth = inputWidth - filterSize + 1;
	int recycleHeight = inputHeight - filterSize + 1;

	*outputImage = cv::Mat::zeros(cv::Size(recycleWidth, recycleHeight), CV_8UC3);

	for (int i = 0; i < recycleHeight; i++)
	{
		for (int j = 0; j < recycleWidth; j++)
		{
			// For channel
			for (int channel = 0; channel < 3; channel++)
			{
				int* filterBuffer = new int[filterSize * filterSize];
				int count = 0;
				//For (filterSize x filterSize) filter
				for (int filterX = 0; filterX < filterSize; filterX++)
				{
					for (int filterY = 0; filterY < filterSize; filterY++)
					{
						filterBuffer[count] = inputImage->at<cv::Vec3b>(i + filterX, j + filterY)[channel];
						count++;
					}
				}

				//sort the array
				bolbSortInt(filterBuffer, filterSize * filterSize);
				
				// Get median:
				if (((filterSize * filterSize) % 2) == 1)
				{
					outputImage->at<cv::Vec3b>(i, j)[channel] = filterBuffer[((filterSize * filterSize) / 2) + 1];
				}
				else
				{
					outputImage->at<cv::Vec3b>(i, j)[channel] = (filterBuffer[((filterSize * filterSize) / 2)]
						+ filterBuffer[((filterSize * filterSize) / 2) + 1]) / 2;
				}

				delete[] filterBuffer;
			}
		}
	}

}

void binarizationFilter(cv::Mat* inputImage, cv::Mat* outputImage, int threshold)
{
	int inputWidth = inputImage->cols;
	int inputHeight = inputImage->rows;

	*outputImage = cv::Mat::zeros(cv::Size(inputWidth, inputHeight), CV_8UC3);

	for (int i = 0; i < inputHeight; i++)
	{
		for (int j = 0; j < inputWidth; j++)
		{
			// For channels
			for (int channel = 0; channel < 3; channel++)
			{
				if (inputImage->at<cv::Vec3b>(i, j)[channel] < threshold)
				{
					outputImage->at<cv::Vec3b>(i, j)[channel] = 0;
				}
				else
				{
					outputImage->at<cv::Vec3b>(i, j)[channel] = 255;
				}
			}
		}
	}
}
