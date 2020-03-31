#ifndef __ImageUtils1630003036_3
#define __ImageUtils1630003036_3
#include <opencv2/opencv.hpp>
#include <opencv2/core/core_c.h>
#include <string>

cv::Mat ILPF(cv::Mat& src, float sigma);
cv::Mat ideal_lbrf_kernel(cv::Mat& scr,float sigma);
cv::Mat freqfilt(cv::Mat &scr,cv::Mat &blur);

#endif