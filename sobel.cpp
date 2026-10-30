
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

// Manuel Sobel kenar tespit algoritmasi
void sobelFilter(
    const Mat& input,
    Mat& horizontalEdges,
    Mat& verticalEdges,
    Mat& combinedEdges)
{
    CV_Assert(input.type() == CV_8UC1);

    // Sobel yatay gradyan kerneli
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    // Sobel dikey gradyan kerneli
    int Gy[3][3] =
    {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    horizontalEdges = Mat::zeros(input.size(), CV_8UC1);
    verticalEdges = Mat::zeros(input.size(), CV_8UC1);

    Mat magnitude = Mat::zeros(input.size(), CV_32FC1);

    // Goruntunun ic bolgesini tara
    for (int y = 1; y < input.rows - 1; y++)
    {
        for (int x = 1; x < input.cols - 1; x++)
        {
            int sumX = 0;
            int sumY = 0;

            // 3x3 konvolusyon islemi
            for (int ky = -1; ky <= 1; ky++)
            {
                for (int kx = -1; kx <= 1; kx++)
                {
                    int pixel = input.at<uchar>(y + ky, x + kx);

                    sumX += pixel * Gx[ky + 1][kx + 1];
                    sumY += pixel * Gy[ky + 1][kx + 1];
                }
            }

            // Yatay ve dikey gradyanlar
            horizontalEdges.at<uchar>(y, x) =
                saturate_cast<uchar>(abs(sumX) / 8.0);

            verticalEdges.at<uchar>(y, x) =
                saturate_cast<uchar>(abs(sumY) / 8.0);

            // Birlesik gradyan buyuklugu
            float gradient = sqrt(
                static_cast<float>(sumX * sumX + sumY * sumY));

            magnitude.at<float>(y, x) = gradient;
        }
    }

    // Sonucu 0-255 araligina getir
    normalize(
        magnitude,
        combinedEdges,
        0,
        255,
        NORM_MINMAX,
        CV_8UC1
    );

    cout << "Manuel Sobel filtresi uygulandi." << endl;
}
