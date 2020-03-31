#include "ImageUtils2.h"

void laplacian1C(cv::Mat* inputImage, cv::Mat* outImage)
{
	int width = inputImage->cols;
	int height = inputImage->rows;

	int newWidth = width - 3 + 1;
	int newHeight = width - 3 + 1;

	*outImage = cv::Mat::zeros(cv::Size(newWidth, newHeight), CV_8UC3);

	for (int i = 0; i < newHeight; i++)
	{
		for (int j = 0; j < newWidth; j++)
		{
			// use Laplacian kernal scan the picture
			for (int c = 0; c < 3; c++)
			{
				int leftTop = inputImage->at<cv::Vec3b>(i, j)[c];
				int centerTop = inputImage->at<cv::Vec3b>(i, j + 1)[c];
				int rightTop = inputImage->at<cv::Vec3b>(i, j + 2)[c];
				int leftCenter = inputImage->at<cv::Vec3b>(i + 1, j)[c];
				int center = inputImage->at<cv::Vec3b>(i + 1, j + 1)[c];
				int rightCenter = inputImage->at<cv::Vec3b>(i + 1, j + 2)[c];
				int leftBelow = inputImage->at<cv::Vec3b>(i + 2, j)[c];
				int centerBelow = inputImage->at<cv::Vec3b>(i + 2, j + 1)[c];
				int rightBelow = inputImage->at<cv::Vec3b>(i + 2, j + 2)[c];

				// multiply to the Laplacian kernal
				int resultPixel = (leftTop * 0) + (centerTop * (-1)) + (rightTop * 0)
					+ (leftCenter * (-1)) + (center * 4) + (rightCenter * (-1))
					+ (leftBelow * 0) + (centerBelow * (-1)) + (rightBelow * 0);

				if (resultPixel < 0)
				{
					resultPixel = 0;
				}

				if (resultPixel > 255)
				{
					resultPixel = 255;
				}

				outImage->at<cv::Vec3b>(i, j)[c] = resultPixel;
			}
		}
	}

}

void sobel(cv::Mat* inputImage, cv::Mat* outImage)
{
	int width = inputImage->cols;
	int height = inputImage->rows;

	int newWidth = width - 3 + 1;
	int newHeight = height - 3 + 1;

	*outImage = cv::Mat::zeros(cv::Size(newWidth, newHeight), CV_8UC3);

	for (int i = 0; i < newHeight; i++)
	{
		for (int j = 0; j < newWidth; j++)
		{
			// use Sobel kernal scan the picture
			for (int c = 0; c < 3; c++)
			{
				int leftTop = inputImage->at<cv::Vec3b>(i, j)[c];
				int centerTop = inputImage->at<cv::Vec3b>(i, j + 1)[c];
				int rightTop = inputImage->at<cv::Vec3b>(i, j + 2)[c];
				int leftCenter = inputImage->at<cv::Vec3b>(i + 1, j)[c];
				int center = inputImage->at<cv::Vec3b>(i + 1, j + 1)[c];
				int rightCenter = inputImage->at<cv::Vec3b>(i + 1, j + 2)[c];
				int leftBelow = inputImage->at<cv::Vec3b>(i + 2, j)[c];
				int centerBelow = inputImage->at<cv::Vec3b>(i + 2, j + 1)[c];
				int rightBelow = inputImage->at<cv::Vec3b>(i + 2, j + 2)[c];

				// multiply to the Sobel kernal

				int G_x = (leftTop * (-1)) + (centerTop * 0) + (rightTop * 1)
					+ (leftCenter * (-2)) + (center * 0) + (rightCenter * 2)
					+ (leftBelow * (-1)) + (centerBelow * 0) + (rightBelow * 1);

				int G_y = (leftTop * 1) + (centerTop * 2) + (rightTop * 1)
					+ (leftCenter * 0) + (center * 0) + (rightCenter * 0)
					+ (leftBelow * (-1)) + (centerBelow * (-2)) + (rightBelow * (-1));

				int resultPixel = abs(G_x) + abs(G_y);

				if (resultPixel < 0)
				{
					resultPixel = 0;
				}

				if (resultPixel > 255)
				{
					resultPixel = 255;
				}

				outImage->at<cv::Vec3b>(i, j)[c] = resultPixel;
			}
		}
	}


}

void gamaCorrelation(cv::Mat* inputImage, cv::Mat* outImage, float gama)
{
	int width = inputImage->cols;
	int height = inputImage->rows;

	*outImage = cv::Mat::zeros(cv::Size(width, height), CV_8UC3);

	double gammaCorrelation = 1.0 / gama;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{

			for (int c = 0; c < 3; c++)
			{
				outImage->at<cv::Vec3b>(i, j)[c] = 255 * pow(double(inputImage->at<cv::Vec3b>(i, j)[c]) / 255, 
					gammaCorrelation);
			}
		}
	}

	double imageAvr = ImageVariance1C(outImage);
	char varInfo[256];
	sprintf(varInfo, "Variance: %.5f", imageAvr);
	char gamaInfo[256];
	sprintf(gamaInfo, "Gama: %.2f", gama);
	cv::putText(*outImage, varInfo, cv::Point(10, 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 
		1.5);
	cv::putText(*outImage, gamaInfo, cv::Point(10, 35), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 
		1.5);
}

void histogramEqualization_GRAY(cv::Mat* inputImage, cv::Mat* outImage, int type)
{

	unsigned char histogram[256];
	unsigned char afterEqulization[256];
	// initialize zero to all pixel values
	memset(histogram, 0, 256);

	int width = inputImage->cols;
	int height = inputImage->rows;
	int totalPixels = width * height;

	// First, copy original picture to our output image
	inputImage->copyTo(*outImage);

	if (type == WHOLE_HISTOGRAM_EQUALIZATION)
	{

		int sum = 0;

		// Get the histogram.
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int pixelValue = inputImage->at<unsigned char>(i, j);
				histogram[pixelValue] += 1;
			}
		}

		// Calculate the out value after equalization
		for (int i = 0; i < 256; i++)
		{
			sum += histogram[i];

			afterEqulization[i] = (1.0 * sum / totalPixels) * 255;

		}

		// give the new pixel value to the outImage
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				outImage->at<unsigned char>(i, j) = afterEqulization[outImage->at<unsigned char>(i, j)];
			}
		}
		
		
	}

	if (type == LOCAL_HISTOGRAM_EQUALIZATION) {


		//Local equalization
		for (int i = 0; i < height; i+= 3)
		{
			for (int j = 0; j < width; j += 3)
			{
				int sum = 0;

				// Get the histogram.
				// Suppose the local size is 3 * 3
				for (int k = 0; k < 3; k++)
				{
					for (int l = 0; l < 3; l++)
					{

						// Prevent over size
						if ((i + k) < height && (j + l) < width) {
							int pixelValue = inputImage->at<unsigned char>(i + k, j + l);
							histogram[pixelValue] += 1;
						}
					}
				}

				// Calculate the out value after equalization
				for (int k = 0; k < 256; k++)
				{
					sum += histogram[i];

					afterEqulization[i] = (1.0 * sum / totalPixels) * 255;

				}

				// give the new pixel value to the outImage
				for (int k = 0; k < 3; k++)
				{
					for (int l = 0; l < 3; l++)
					{
						//Prevent over size
						if ((i + k) < height && (j + l) < width)
						{
							outImage->at<unsigned char>(i + k, j + l) = 
								afterEqulization[outImage->at<unsigned char>(i + k, j + l)];
						}
						
					}
				}

			}


		}

		

		
	}
}

double ImageAverage1C(cv::Mat* image)
{
	int width = image->cols;
	int height = image->rows;

	int totalPixels = width * height;

	double sum = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			sum += image->at<cv::Vec3b>(i, j)[0];
		}
	}

	return sum / totalPixels;
}

double ImageVariance1C(cv::Mat* image)
{
	int width = image->cols;
	int height = image->rows;
	double imageAverage = ImageAverage1C(image);
	int totalPixels = width * height;
	double sum = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			sum += pow((image->at<cv::Vec3b>(i, j)[0] - imageAverage), 2);
		}
	}

	return sqrt(sum / totalPixels);
}
