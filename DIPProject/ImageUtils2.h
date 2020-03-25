#pragma once
#include<opencv2/opencv.hpp>
#include <math.h>
#include <iostream>
#include <vector>

#define LOCAL_HISTOGRAM_EQUALIZATION -1
#define WHOLE_HISTOGRAM_EQUALIZATION 1

void laplacian1C(cv::Mat* inputImage, cv::Mat* outImage);
void sobel(cv::Mat* inputImage, cv::Mat* outImage);
void gamaCorrelation(cv::Mat* inputImage, cv::Mat* outImage, float gama);
void histogramEqualization_GRAY(cv::Mat* inputImage, cv::Mat* outImage, int type);
double ImageAverage1C(cv::Mat* image);
double ImageVariance1C(cv::Mat* image);
