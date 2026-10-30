
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

// =====================================================
// 1. PREWITT FILTRESI
// =====================================================

void prewittFilter(
    const Mat& input,
    Mat& horizontalEdges,
    Mat& verticalEdges,
    Mat& combinedEdges)
{
    CV_Assert(input.type() == CV_8UC1);

    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-1, 0, 1},
        {-1, 0, 1}
    };

    int Gy[3][3] =
    {
        {-1, -1, -1},
        { 0,  0,  0},
        { 1,  1,  1}
    };

    horizontalEdges = Mat::zeros(input.size(), CV_8UC1);
    verticalEdges = Mat::zeros(input.size(), CV_8UC1);

    Mat magnitude = Mat::zeros(input.size(), CV_32FC1);

    for (int y = 1; y < input.rows - 1; y++)
    {
        for (int x = 1; x < input.cols - 1; x++)
        {
            int sumX = 0;
            int sumY = 0;

            for (int ky = -1; ky <= 1; ky++)
            {
                for (int kx = -1; kx <= 1; kx++)
                {
                    int pixel = input.at<uchar>(y + ky, x + kx);

                    sumX += pixel * Gx[ky + 1][kx + 1];
                    sumY += pixel * Gy[ky + 1][kx + 1];
                }
            }

            horizontalEdges.at<uchar>(y, x) =
                saturate_cast<uchar>(abs(sumX) / 4.0);

            verticalEdges.at<uchar>(y, x) =
                saturate_cast<uchar>(abs(sumY) / 4.0);

            float gradient = sqrt(
                static_cast<float>(sumX * sumX + sumY * sumY));

            magnitude.at<float>(y, x) = gradient;
        }
    }

    normalize(
        magnitude,
        combinedEdges,
        0, 255,
        NORM_MINMAX,
        CV_8UC1
    );

    cout << "Birinci Prewitt filtresi uygulandi." << endl;
}


// =====================================================
// 2. PREWITT FILTRESI (IKINCI KERNEL)
// =====================================================

void prewittFilterSecond(
    const Mat& input,
    Mat& horizontalEdges,
    Mat& verticalEdges,
    Mat& combinedEdges)
{
    CV_Assert(input.type() == CV_8UC1);

    int Gx[3][3] =
    {
        {-1, -1, -1},
        { 0,  0,  0},
        { 1,  1,  1}
    };

    int Gy[3][3] =
    {
        {-1,  0,  1},
        {-1,  0,  1},
        {-1,  0,  1}
    };

    horizontalEdges = Mat::zeros(input.size(), CV_8UC1);
    verticalEdges = Mat::zeros(input.size(), CV_8UC1);

    Mat magnitude = Mat::zeros(input.size(), CV_32FC1);

    for (int y = 1; y < input.rows - 1; y++)
    {
        for (int x = 1; x < input.cols - 1; x++)
        {
            int sumX = 0;
            int sumY = 0;

            for (int ky = -1; ky <= 1; ky++)
            {
                for (int kx = -1; kx <= 1; kx++)
                {
                    int pixel = input.at<uchar>(y + ky, x + kx);

                    sumX += pixel * Gx[ky + 1][kx + 1];
                    sumY += pixel * Gy[ky + 1][kx + 1];
                }
            }

            horizontalEdges.at<uchar>(y, x) =
                saturate_cast<uchar>(abs(sumX) / 4.0);

            verticalEdges.at<uchar>(y, x) =
                saturate_cast<uchar>(abs(sumY) / 4.0);

            float gradient = sqrt(
                static_cast<float>(sumX * sumX + sumY * sumY));

            magnitude.at<float>(y, x) = gradient;
        }
    }

    normalize(
        magnitude,
        combinedEdges,
        0, 255,
        NORM_MINMAX,
        CV_8UC1
    );

    cout << "Ikinci Prewitt filtresi uygulandi." << endl;
}
