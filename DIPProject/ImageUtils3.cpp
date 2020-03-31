#include "ImageUtils3.h"

cv::Mat ILPF(cv::Mat &src, float sigma)
{
    int M = cv::getOptimalDFTSize(src.rows);
    int N = cv::getOptimalDFTSize(src.cols);
    cv::Mat padded; //調整圖像加速傅里葉變換
    copyMakeBorder(src, padded, 0, M - src.rows, 0, N - src.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
    padded.convertTo(padded, CV_32FC1); //將圖像轉換爲flaot型

    cv::Mat ideal_kernel = ideal_lbrf_kernel(padded, sigma); //理想低通濾波器
    cv::Mat result = freqfilt(padded, ideal_kernel);
    return result;
}

cv::Mat BLPF(cv::Mat &src, float d0, int n)
{
    //H = 1 / (1+(D/D0)^2n)    n表示巴特沃斯濾波器的次數

    //調整圖像加速傅里葉變換
    int M = cv::getOptimalDFTSize(src.rows);
    int N = cv::getOptimalDFTSize(src.cols);
    cv::Mat padded;
    copyMakeBorder(src, padded, 0, M - src.rows, 0, N - src.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
    padded.convertTo(padded, CV_32FC1); //將圖像轉換爲flaot型

    cv::Mat butterworth_kernel = butterworth_lbrf_kernel(padded, d0, n); //理想低通濾波器
    cv::Mat result = freqfilt(padded, butterworth_kernel);
    return result;
}

cv::Mat GLPF(cv::Mat& scr,float sigma) {
    int M = cv::getOptimalDFTSize(scr.rows);
    int N = cv::getOptimalDFTSize(scr.cols);
    cv::Mat padded; //調整圖像加速傅里葉變換
    copyMakeBorder(scr, padded, 0, M - scr.rows, 0, N - scr.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
    padded.convertTo(padded, CV_32FC1); //將圖像轉換爲flaot型

    cv::Mat ideal_kernel = gaussian_lbrf_kernal(padded, sigma); //理想低通濾波器
    cv::Mat result = freqfilt(padded, ideal_kernel);
    return result;
}

cv::Mat gaussian_lbrf_kernal(cv::Mat& scr, float sigma)
{
    cv::Mat gaussianBlur(scr.size(), CV_32FC1); //，CV_32FC1
    float d0 = 2 * sigma * sigma;           //高斯函数参数，越小，频率高斯滤波器越窄，滤除高频成分越多，图像就越平滑
    for (int i = 0; i < scr.rows; i++)
    {
        for (int j = 0; j < scr.cols; j++)
        {
            float d = pow(float(i - scr.rows / 2), 2) + pow(float(j - scr.cols / 2), 2); //分子,计算pow必须为float型
            gaussianBlur.at<float>(i, j) = expf(-d / d0);                                //expf为以e为底求幂（必须为float型）
        }
    }
    
    std::string name = "高斯低通滤波器d0=" + std::to_string(sigma);
    imshow(name, gaussianBlur);
    return gaussianBlur;
}

cv::Mat butterworth_lbrf_kernel(cv::Mat &scr, float sigma, int n)
{
    //    階數n=1 無振鈴和負值
    //    階數n=2 輕微振鈴和負值
    //    階數n=5 明顯振鈴和負值
    //    階數n=20 與ILPF相似
    cv::Mat butterworth_low_pass(scr.size(), CV_32FC1); //，CV_32FC1
    double D0 = sigma;                                  //半徑D0越小，模糊越大；半徑D0越大，模糊越小
    for (int i = 0; i < scr.rows; i++)
    {
        for (int j = 0; j < scr.cols; j++)
        {
            double d = sqrt(pow((i - scr.rows / 2), 2) + pow((j - scr.cols / 2), 2)); //分子,計算pow必須爲float型
            butterworth_low_pass.at<float>(i, j) = 1.0 / (1 + pow(d / D0, 2 * n));
        }
    }

    std::string name = "巴特沃斯低通濾波器d0=" + std::to_string(sigma) + "n=" + std::to_string(n);
    imshow(name, butterworth_low_pass);
    return butterworth_low_pass;
}

cv::Mat ideal_lbrf_kernel(cv::Mat &scr, float sigma)
{
    cv::Mat ideal_low_pass(scr.size(), CV_32FC1); //，CV_32FC1
    float d0 = sigma;                             //半徑D0越小，模糊越大；半徑D0越大，模糊越小
    for (int i = 0; i < scr.rows; i++)
    {
        for (int j = 0; j < scr.cols; j++)
        {
            double d = sqrt(pow((i - scr.rows / 2), 2) + pow((j - scr.cols / 2), 2)); //分子,計算pow必須爲float型
            if (d <= d0)
            {
                ideal_low_pass.at<float>(i, j) = 1;
            }
            else
            {
                ideal_low_pass.at<float>(i, j) = 0;
            }
        }
    }
    std::string name = "理想低通濾波器d0=" + std::to_string(sigma);
    imshow(name, ideal_low_pass);
    return ideal_low_pass;
}

cv::Mat freqfilt(cv::Mat &scr, cv::Mat &blur)
{
    //***********************DFT*******************
    cv::Mat plane[] = {scr, cv::Mat::zeros(scr.size(), CV_32FC1)}; //創建通道，存儲dft後的實部與虛部（CV_32F，必須爲單通道數）
    cv::Mat complexIm;
    merge(plane, 2, complexIm); //合併通道 （把兩個矩陣合併爲一個2通道的Mat類容器）
    dft(complexIm, complexIm);  //進行傅立葉變換，結果保存在自身

    //***************中心化********************
    split(complexIm, plane); //分離通道（數組分離）
                             //    plane[0] = plane[0](Rect(0, 0, plane[0].cols & -2, plane[0].rows & -2));//這裏爲什麼&上-2具體查看opencv文檔
                             //    //其實是爲了把行和列變成偶數 -2的二進制是11111111.......10 最後一位是0
    int cx = plane[0].cols / 2;
    int cy = plane[0].rows / 2;                        //以下的操作是移動圖像  (零頻移到中心)
    cv::Mat part1_r(plane[0], cv::Rect(0, 0, cx, cy)); //元素座標表示爲(cx,cy)
    cv::Mat part2_r(plane[0], cv::Rect(cx, 0, cx, cy));
    cv::Mat part3_r(plane[0], cv::Rect(0, cy, cx, cy));
    cv::Mat part4_r(plane[0], cv::Rect(cx, cy, cx, cy));

    cv::Mat temp;
    part1_r.copyTo(temp); //左上與右下交換位置(實部)
    part4_r.copyTo(part1_r);
    temp.copyTo(part4_r);

    part2_r.copyTo(temp); //右上與左下交換位置(實部)
    part3_r.copyTo(part2_r);
    temp.copyTo(part3_r);

    cv::Mat part1_i(plane[1], cv::Rect(0, 0, cx, cy)); //元素座標(cx,cy)
    cv::Mat part2_i(plane[1], cv::Rect(cx, 0, cx, cy));
    cv::Mat part3_i(plane[1], cv::Rect(0, cy, cx, cy));
    cv::Mat part4_i(plane[1], cv::Rect(cx, cy, cx, cy));

    part1_i.copyTo(temp); //左上與右下交換位置(虛部)
    part4_i.copyTo(part1_i);
    temp.copyTo(part4_i);

    part2_i.copyTo(temp); //右上與左下交換位置(虛部)
    part3_i.copyTo(part2_i);
    temp.copyTo(part3_i);

    //*****************濾波器函數與DFT結果的乘積****************
    cv::Mat blur_r, blur_i, BLUR;
    multiply(plane[0], blur, blur_r); //濾波（實部與濾波器模板對應元素相乘）
    multiply(plane[1], blur, blur_i); //濾波（虛部與濾波器模板對應元素相乘）
    cv::Mat plane1[] = {blur_r, blur_i};
    merge(plane1, 2, BLUR); //實部與虛部合併

    //*********************得到原圖頻譜圖***********************************
    magnitude(plane[0], plane[1], plane[0]);        //獲取幅度圖像，0通道爲實部通道，1爲虛部，因爲二維傅立葉變換結果是複數
    plane[0] += cv::Scalar::all(1);                 //傅立葉變換後的圖片不好分析，進行對數處理，結果比較好看
    log(plane[0], plane[0]);                        // float型的灰度空間爲[0，1])
    normalize(plane[0], plane[0], 1, 0, CV_MINMAX); //歸一化便於顯示
                                                    //    imshow("原圖像頻譜圖",plane[0]);

    idft(BLUR, BLUR);                               //idft結果也爲複數
    split(BLUR, plane);                             //分離通道，主要獲取通道
    magnitude(plane[0], plane[1], plane[0]);        //求幅值(模)
    normalize(plane[0], plane[0], 1, 0, CV_MINMAX); //歸一化便於顯示
    return plane[0];                                //返回參數
}