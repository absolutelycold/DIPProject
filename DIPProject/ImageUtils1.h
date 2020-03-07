#ifndef __ImageUtils1630003036_1
#define __ImageUtils1630003036_1
#define M_PI 3.141592653589793238462643383279502884
#include<opencv2/opencv.hpp>

void imageTranslation(cv::Mat* inputImage, cv::Mat* outputImage, int x, int y);
void imageRotation(cv::Mat* inputImage, cv::Mat* outputImage, int degree);
void imageShear(cv::Mat* inputImage, cv::Mat* outputImage, float horizental, float veritical);
#endif // !__ImageUtils1630003036_1


