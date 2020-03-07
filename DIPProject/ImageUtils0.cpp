#include "ImageUtils.h"

void alternativeLineReduction(cv::Mat* inputImage, cv::Mat* outputImage, int width, int height)
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

void fractionReduction(cv::Mat* inputImage, cv::Mat* outputImage, int width, int height)
{
    int input_width = inputImage->cols;
    int input_height = inputImage->rows;

    // Initialize output image with scaled width and height
    *outputImage = cv::Mat::zeros(cv::Size(width, height), CV_8UC3);
    float widthScale = (float)width / input_width;
    float heightScale = (float)height / input_height;

    std::cout << "Width scale:" << widthScale << std::endl;
    std::cout << "Height scale:" << heightScale << std::endl;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            outputImage->at<cv::Vec3b>(i, j) = inputImage->at<cv::Vec3b>(round(i / heightScale), round(j / widthScale));
        }
    }
}

void fractionEnlargement(cv::Mat* inputImage, cv::Mat* outputImage, int width, int height)
{
    int input_width = inputImage->cols;
    int input_height = inputImage->rows;

    // Initialize output image with scaled width and height
    *outputImage = cv::Mat::zeros(cv::Size(width, height), CV_8UC3);
    float widthScale = (float)width / input_width;
    float heightScale = (float)height / input_height;

    std::cout << "Width scale:" << widthScale << std::endl;
    std::cout << "Height scale:" << heightScale << std::endl;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            outputImage->at<cv::Vec3b>(i, j) = inputImage->at<cv::Vec3b>(round(i / heightScale), round(j / widthScale));
        }
    }
}

void pixelReplication(cv::Mat* inputImage, cv::Mat* enlargedImage, int scaleNum)
{
    int width = inputImage->cols;
    int height = inputImage->rows;
    *enlargedImage = cv::Mat::zeros(cv::Size(width * scaleNum, height * scaleNum), CV_8UC3);
    // read each rows in original image
    for (int i = 0; i < height; ++i) {
        // read each columns in original image
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < scaleNum; ++k) {
                for (int l = 0; l < scaleNum; ++l) {
                    enlargedImage->at<cv::Vec3b>((i * scaleNum) + k, (j * scaleNum) + l) = inputImage->at<cv::Vec3b>(i, j);
                }
            }

        }
    }
}

void negativeImage(cv::Mat* inputImage, cv::Mat* negativedImage)
{
    int width = inputImage->cols;
    int height = inputImage->rows;
    // initialize the output image
    *negativedImage = cv::Mat::zeros(cv::Size(width, height), CV_8UC3);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            // negative 3 channels
            cv::Vec3b currentPixel = inputImage->at<cv::Vec3b>(i, j);
            negativedImage->at<cv::Vec3b >(i, j)[0] = 255 - currentPixel[0];
            negativedImage->at<cv::Vec3b >(i, j)[1] = 255 - currentPixel[1];
            negativedImage->at<cv::Vec3b >(i, j)[2] = 255 - currentPixel[2];
        }
    }
}

void nearestEnlargement(cv::Mat* inputImage, cv::Mat* enlargedImage)
{
    int inputWidth = inputImage->cols;
    int inputHeight = inputImage->rows;

    // The reason why minus 1 is to delete the padding
    int enlargeWidth = (inputWidth * 3) - 1;
    int enlargeHeight = (inputHeight * 3) - 1;

    *enlargedImage = cv::Mat::zeros(cv::Size(enlargeWidth, enlargeHeight), CV_8UC3);

    for (int i = 0; i < inputHeight; ++i) {
        for (int j = 0; j < inputWidth; ++j) {
            if (i == 0) {
                // First row
                if (j == 0) {
                    // the left top corner
                    enlargedImage->at<cv::Vec3b>(0, 0) = inputImage->at<cv::Vec3b>(i, j);
                    enlargedImage->at<cv::Vec3b>(0, 1) = inputImage->at<cv::Vec3b>(i, j);
                    enlargedImage->at<cv::Vec3b>(1, 0) = inputImage->at<cv::Vec3b>(i, j);
                    enlargedImage->at<cv::Vec3b>(1, 1) = inputImage->at<cv::Vec3b>(i, j);
                }
                else {
                    // the first row except the top corner one, we need fill 2x3 vectors into enlarged image
                    for (int k = 0; k < 2; ++k) {
                        for (int l = 0; l < 3; ++l) {
                            //Because we are in the first row, only k=2 rows
                            enlargedImage->at<cv::Vec3b>(k, (j * 3) + l - 1) = inputImage->at<cv::Vec3b>(i, j);
                        }
                    }

                }
            }
            else if (j == 0) {
                // first column
                for (int k = 0; k < 3; ++k) {
                    for (int l = 0; l < 2; ++l) {
                        enlargedImage->at<cv::Vec3b>((i * 3) + k - 1, l) = inputImage->at<cv::Vec3b>(i, j);
                    }
                }
            }
            else {
                // other pixel not in the edge
                for (int k = 0; k < 3; ++k) {
                    for (int l = 0; l < 3; ++l) {
                        enlargedImage->at<cv::Vec3b>((i * 3) + k - 1, (j * 3) + l - 1) = inputImage->at<cv::Vec3b>(i, j);
                    }
                }
            }
        }
    }
}

void biLinearInterpolation(cv::Mat* inputImage, cv::Mat* outputImage)
{
    int inputWidth = inputImage->cols;
    int inputHeight = inputImage->rows;

    int newWidth = 2 * inputWidth;
    int newHeight = 2 * inputHeight;

    // Put previous pixel to the enlarged image
    *outputImage = cv::Mat::zeros(cv::Size(newWidth, newHeight), CV_8UC3);
    for (int i = 0; i < inputHeight; ++i) {
        for (int j = 0; j < inputWidth; ++j) {
            outputImage->at<cv::Vec3b>(i * 2, j * 2) = inputImage->at<cv::Vec3b>(i, j);
        }
    }

    // Interpolate pixel in the center of 4 pixels
    // the reason why += 2 is that we only want to interpolate the center pixel
    for (int k = 1; k < newHeight; k += 2) {
        for (int i = 1; i < newWidth; i += 2) {
            if ((k != newHeight - 1) & (i != newWidth - 1)) {
                // if the filled center is not in the edge, we fill it.
                for (int channel = 0; channel < 3; ++channel) {
                    // Because I initialize the enlarged image as CV_8UC3, we need calculate the
                    // interpolated point in all the 3 channels
                    // also because I choose the center as the interpolation position
                    // I can simply use (sum of pixel at four corner) / 4 as the pixel in the center
                    int LeftTopCorner = outputImage->at<cv::Vec3b>(k - 1, i - 1)[channel];
                    int RightTopCorner = outputImage->at<cv::Vec3b>(k + 1, i - 1)[channel];
                    int LeftBelowCorner = outputImage->at<cv::Vec3b>(k - 1, i + 1)[channel];
                    int RightBelowCorner = outputImage->at<cv::Vec3b>(k + 1, i + 1)[channel];
                    int cornerPoints[2][2] = { {LeftTopCorner, RightTopCorner},
                                              {LeftBelowCorner, RightBelowCorner} };


                    // fill the center pixel
                    outputImage->at<cv::Vec3b>(k, i)[channel] = getBilinearValue(cornerPoints, 0.5, 0.5);
                    // fill the pixel left to the center pixel
                    outputImage->at<cv::Vec3b>(k, i - 1)[channel] = getBilinearValue(cornerPoints, 0.5, 0);
                    // fill the pixel above the center pixel
                    outputImage->at<cv::Vec3b>(k - 1, i)[channel] = getBilinearValue(cornerPoints, 0, 0.5);
                    // fill in the pixel right to the center pixel
                    outputImage->at<cv::Vec3b>(k + 1, i)[channel] = getBilinearValue(cornerPoints, 0.5, 1);
                    // fill in the pixel below to the center pixel
                    outputImage->at<cv::Vec3b>(k, i + 1)[channel] = getBilinearValue(cornerPoints, 1, 0.5);
                }
            }


        }
    }
}

void bicubicInterpolation(cv::Mat* inputImage, cv::Mat* outputImage)
{
    int inputWidth = inputImage->cols;
    int inputHeight = inputImage->rows;
    
    //newSize
    int newWidth = 2 * inputWidth;
    int newHeight = 2 * inputHeight;
    *outputImage = cv::Mat::zeros(cv::Size(newWidth, newHeight), CV_8UC3);

    std::cout << newWidth * newHeight << std::endl;
    //fill pixel in the enlarged image

    int insertRow = 0;
    int insertCol = 0;
    //int pixelnum1 = 0;
    for (int row = 0; row < inputHeight; row++)
    {
        for (int col = 0; col < inputWidth; col++)
        {
            insertRow = 2 * row;
            insertCol = 2 * col;
            
            if ((insertRow < newHeight) & (insertCol < newWidth))
            {
                //pixelnum1++;
                outputImage->at<cv::Vec3b>(insertRow, insertCol) = inputImage->at<cv::Vec3b>(row, col);
            }
            
        }
    }

    //interpolation
    //int pixelnum2 = 0;
    int iRec = 0;
    for (int i = 0; i < newHeight; i++)
    {
        int jRec = 0;
        for (int j = 1; j < newWidth; j+=2)
        {
            jRec++;
            //3 channels
            for (int channel = 0; channel < 3; channel++)
            {
                iRec = i / 2;
                //pixelnum2++;
                int pixel00 = getPixelValue(*inputImage, iRec - 1, jRec - 1, channel);
                int pixel01 = getPixelValue(*inputImage, iRec - 1, jRec, channel);
                int pixel02 = getPixelValue(*inputImage, iRec - 1, jRec + 1, channel);
                int pixel03 = getPixelValue(*inputImage, iRec - 1, jRec + 2, channel);
                int pixel10 = getPixelValue(*inputImage, iRec, jRec - 1, channel);
                int pixel11 = getPixelValue(*inputImage, iRec, jRec, channel);
                int pixel12 = getPixelValue(*inputImage, iRec, jRec + 1, channel);
                int pixel13 = getPixelValue(*inputImage, iRec, jRec + 2, channel);
                int pixel20 = getPixelValue(*inputImage, iRec + 1, jRec - 1, channel);
                int pixel21 = getPixelValue(*inputImage, iRec + 1, jRec, channel);
                int pixel22 = getPixelValue(*inputImage, iRec + 1, jRec + 1, channel);
                int pixel23 = getPixelValue(*inputImage, iRec + 1, jRec + 2, channel);
                int pixel30 = getPixelValue(*inputImage, iRec + 2, jRec - 1, channel);
                int pixel31 = getPixelValue(*inputImage, iRec + 2, jRec, channel);
                int pixel32 = getPixelValue(*inputImage, iRec + 2, jRec + 1, channel);
                int pixel33 = getPixelValue(*inputImage, iRec + 2, jRec + 2, channel);

                int pixels[4][4] = { {pixel00, pixel01, pixel02, pixel03},
                {pixel10, pixel11, pixel12, pixel13},
                {pixel20, pixel21, pixel22, pixel23},
                {pixel30, pixel31, pixel32, pixel33},
                };

                int interpolationValue = floor(getBicubicValue(pixels, 1, 1));

                outputImage->at<cv::Vec3b>(i, j)[channel] = interpolationValue;

                //std::cout << interpolationValue << std::endl;

            }

        }

        //For extra points:
        if (i % 2 == 1)
        {
            jRec = 0;
            for (int j = 0; j < newWidth; j+=2)
            {
                jRec++;

                // 3 channels
                for (int channel = 0; channel < 3; channel++)
                {
                    iRec = i / 2;
                    //pixelnum2++;
                    int pixel00 = getPixelValue(*inputImage, iRec - 1, jRec - 1, channel);
                    int pixel01 = getPixelValue(*inputImage, iRec - 1, jRec, channel);
                    int pixel02 = getPixelValue(*inputImage, iRec - 1, jRec + 1, channel);
                    int pixel03 = getPixelValue(*inputImage, iRec - 1, jRec + 2, channel);
                    int pixel10 = getPixelValue(*inputImage, iRec, jRec - 1, channel);
                    int pixel11 = getPixelValue(*inputImage, iRec, jRec, channel);
                    int pixel12 = getPixelValue(*inputImage, iRec, jRec + 1, channel);
                    int pixel13 = getPixelValue(*inputImage, iRec, jRec + 2, channel);
                    int pixel20 = getPixelValue(*inputImage, iRec + 1, jRec - 1, channel);
                    int pixel21 = getPixelValue(*inputImage, iRec + 1, jRec, channel);
                    int pixel22 = getPixelValue(*inputImage, iRec + 1, jRec + 1, channel);
                    int pixel23 = getPixelValue(*inputImage, iRec + 1, jRec + 2, channel);
                    int pixel30 = getPixelValue(*inputImage, iRec + 2, jRec - 1, channel);
                    int pixel31 = getPixelValue(*inputImage, iRec + 2, jRec, channel);
                    int pixel32 = getPixelValue(*inputImage, iRec + 2, jRec + 1, channel);
                    int pixel33 = getPixelValue(*inputImage, iRec + 2, jRec + 2, channel);

                    int pixels[4][4] = { {pixel00, pixel01, pixel02, pixel03},
                    {pixel10, pixel11, pixel12, pixel13},
                    {pixel20, pixel21, pixel22, pixel23},
                    {pixel30, pixel31, pixel32, pixel33},
                    };

                    int interpolationValue = floor(getBicubicValue(pixels, 1, 1));

                    outputImage->at<cv::Vec3b>(i, j)[channel] = interpolationValue;

                    //std::cout << interpolationValue << std::endl;

                }

            }
        }
    }


    




    //std::cout << pixelnum1 + pixelnum2 << std::endl;
}

double getBicubicValue(int a[][4], int x, int y)
{
    double interpolationNum = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            double XWeight;
            double YWeight;
            int XMinusXi = abs(x - i);
            if (XMinusXi <= 1)
            {
                XWeight = (1.5 * XMinusXi * XMinusXi * XMinusXi) - (2.5 * XMinusXi * XMinusXi) + 1;
            }
            else if (XMinusXi < 2)
            {
                XWeight = (-0.5 * XMinusXi * XMinusXi * XMinusXi) + (2.5 * XMinusXi * XMinusXi) - (4.0 * XMinusXi + 2);
            }
            else {
                XWeight = 0;
            }

            int YMinusYi = abs(y - j);
            if (YMinusYi <= 1)
            {
                YWeight = (1.5 * YMinusYi * YMinusYi * YMinusYi) - (2.5 * YMinusYi * YMinusYi) + 1;
            }
            else if (YMinusYi < 2)
            {
                YWeight = (-0.5 * YMinusYi * YMinusYi * YMinusYi) + (2.5 * YMinusYi * YMinusYi) - (4.0 * YMinusYi + 2);
            }
            else {
                YWeight = 0;
            }

            interpolationNum = interpolationNum + (XWeight * YWeight * a[i][j]);
        }
    }
    //std::cout << interpolationNum << std::endl;
    return interpolationNum;
}

double getBilinearValue(int cornerPoints[][2], double p, double q)
{
    double interpolateValue = ((1 - p) * (1 - q) * cornerPoints[0][0])
        + (p * (1 - q) * cornerPoints[0][1])
        + ((1 - p) * q * cornerPoints[1][0])
        + (p * q * cornerPoints[1][1]);
    return interpolateValue;
}

int getPixelValue(cv::Mat image, int x, int y, int channel)
{
    int imageHeight = image.rows;
    int imageWidth = image.cols;
    if (x < 0)
    {
        return 0;
    }
    if (x >= imageHeight)
    {
        return 0;
    }
    if (y < 0)
    {
        return 0;
    }
    if (y >= imageWidth)
    {
        return 0;
    }

    return image.at<cv::Vec3b>(x, y)[channel];
}
