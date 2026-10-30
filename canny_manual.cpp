
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <algorithm>
#include <deque>

using namespace cv;
using namespace std;

// =====================================================
// YARDIMCI: GUVENLI IS PARCACIGI SAYISI
// =====================================================

unsigned int getThreadCount(int totalRows)
{
    unsigned int count = thread::hardware_concurrency();

    if (count == 0)
        count = 4;

    // Her is parcacigina en az bir satir dusmesini sagla.
    count = min(count, static_cast<unsigned int>(max(1, totalRows)));

    return count;
}

// =====================================================
// 1. ADIM: MANUEL 5x5 GAUSSIAN BLUR
// =====================================================

Mat gaussianBlurManual(const Mat& input)
{
    CV_Assert(input.type() == CV_8UC1);
    CV_Assert(!input.empty());

    int kernel[5][5] =
    {
        { 1,  4,  6,  4,  1},
        { 4, 16, 24, 16,  4},
        { 6, 24, 36, 24,  6},
        { 4, 16, 24, 16,  4},
        { 1,  4,  6,  4,  1}
    };

    const int divisor = 256;
    Mat output(input.size(), CV_32FC1);

    unsigned int threadCount = getThreadCount(input.rows);
    vector<thread> threads;
    threads.reserve(threadCount);

    auto processRows = [&](int startRow, int endRow)
        {
            for (int y = startRow; y < endRow; y++)
            {
                for (int x = 0; x < input.cols; x++)
                {
                    float sum = 0.0f;

                    for (int ky = -2; ky <= 2; ky++)
                    {
                        for (int kx = -2; kx <= 2; kx++)
                        {
                            int pixelY = min(max(y + ky, 0), input.rows - 1);
                            int pixelX = min(max(x + kx, 0), input.cols - 1);

                            sum += input.at<uchar>(pixelY, pixelX) *
                                kernel[ky + 2][kx + 2];
                        }
                    }

                    output.at<float>(y, x) = sum / divisor;
                }
            }
        };

    int rowsPerThread = input.rows / static_cast<int>(threadCount);

    for (unsigned int i = 0; i < threadCount; i++)
    {
        int startRow = static_cast<int>(i) * rowsPerThread;
        int endRow = (i == threadCount - 1)
            ? input.rows
            : startRow + rowsPerThread;

        threads.emplace_back(processRows, startRow, endRow);
    }

    for (auto& t : threads)
        t.join();

    cout << "Gaussian Blur tamamlandi." << endl;
    return output;
}
