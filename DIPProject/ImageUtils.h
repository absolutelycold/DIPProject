#pragma once
#include<opencv2/opencv.hpp>

class ImageUtils
{
public:
	ImageUtils();
	~ImageUtils();
    static void alternativeLineReduction(cv::Mat* inputImage, cv::Mat* outputImage, int width, int height);
    static void fractionReduction(cv::Mat* inputImage, cv::Mat* outputImage, int width, int height);
    static void fractionEnlargement(cv::Mat* inputImage, cv::Mat* outputImage, int width, int height);
    static void pixelReplication(cv::Mat* inputImage, cv::Mat* enlargedImage, int scaleNum);
    static void negativeImage(cv::Mat* inputImage, cv::Mat* negativedImage);
    static void nearestEnlargement(cv::Mat* inputImage, cv::Mat* enlargedImage);
    static void biLinearInterpolation(cv::Mat* inputImage, cv::Mat* outputImage);
    static void bicubicInterpolation(cv::Mat* inputImage, cv::Mat* outputImage);

private:
    static double getBicubicValue(double a[][4], double x, double y);
    static double getBilinearValue(int cornerPoints[][2], double p, double q);
};