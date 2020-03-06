#include "ImageUtils.h"

void ImageUtils::alternativeLineReduction(cv::Mat* inputImage, cv::Mat* outputImage, int width, int height)
{
    int inputWidth = inputImage->cols;
    int inputHeight = inputImage->rows;
    // Initialize reduction image with input size witch 3 channel
    *outputImage = cv::Mat::zeros(cv::Size(width, height), CV_8UC3);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            outputImage->at<cv::Vec3b>(i, j) = inputImage->at<cv::Vec3b>(floor(((float)i / height) * inputHeight),
                floor(((float)j / width) * inputWidth));
        }
    }
}

void ImageUtils::fractionReduction(cv::Mat* inputImage, cv::Mat* outputImage, int width, int height)
{

}
