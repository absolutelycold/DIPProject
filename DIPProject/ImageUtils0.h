#ifndef __ImageUtils1630003036_0
#define __ImageUtils1630003036_0

#include<opencv2/opencv.hpp>
void alternativeLineReduction(cv::Mat* inputImage, cv::Mat* outputImage, int width, int height);
void fractionReduction(cv::Mat* inputImage, cv::Mat* outputImage, int width, int height);
void fractionEnlargement(cv::Mat* inputImage, cv::Mat* outputImage, int width, int height);
void pixelReplication(cv::Mat* inputImage, cv::Mat* enlargedImage, int scaleNum);
void negativeImage(cv::Mat* inputImage, cv::Mat* negativedImage);
void nearestEnlargement(cv::Mat* inputImage, cv::Mat* enlargedImage);
void biLinearInterpolation(cv::Mat* inputImage, cv::Mat* outputImage);
void bicubicInterpolation(cv::Mat* inputImage, cv::Mat* outputImage);
double getBicubicValue(int a[][4], int x, int y);
double getBilinearValue(int cornerPoints[][2], double p, double q);
int getPixelValue(cv::Mat image, int x, int y, int channel);


#endif // !__ImageUtils1630003036

