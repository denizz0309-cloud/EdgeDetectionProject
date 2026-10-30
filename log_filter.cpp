
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

// Manuel 7x7 Laplacian of Gaussian algoritmasi
void logFilter7x7(const Mat& input, Mat& output)
{
    CV_Assert(input.type() == CV_8UC1);

    const int kernelSize = 7;
    const int radius = kernelSize / 2;
    const double sigma = 1.4;

    // 7x7 LoG kernel matrisini olustur
    Mat kernel(kernelSize, kernelSize, CV_64F);

    double kernelSum = 0.0;

    // LoG formulu ile kernel degerlerini hesapla
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            double r2 = x * x + y * y;

            double value =
                ((r2 - 2.0 * sigma * sigma) /
                    pow(sigma, 4)) *
                exp(-r2 / (2.0 * sigma * sigma));

            kernel.at<double>(y + radius, x + radius) = value;

            kernelSum += value;
        }
    }

    // Kernel toplamýný sifira yaklastir
    double mean = kernelSum / (kernelSize * kernelSize);

    double absoluteSum = 0.0;

    for (int y = 0; y < kernelSize; y++)
    {
        for (int x = 0; x < kernelSize; x++)
        {
            kernel.at<double>(y, x) -= mean;
            absoluteSum += abs(kernel.at<double>(y, x));
        }
    }

    // Kernel degerlerini normalize et
    kernel /= absoluteSum;

    // Konvolusyon sonucu icin float matris
    Mat response = Mat::zeros(input.size(), CV_32FC1);

    // Manuel 7x7 konvolusyon islemi
    for (int y = radius; y < input.rows - radius; y++)
    {
        for (int x = radius; x < input.cols - radius; x++)
        {
            double sum = 0.0;

            for (int ky = -radius; ky <= radius; ky++)
            {
                for (int kx = -radius; kx <= radius; kx++)
                {
                    double pixel = input.at<uchar>(y + ky, x + kx);

                    double kernelValue =
                        kernel.at<double>(ky + radius, kx + radius);

                    sum += pixel * kernelValue;
                }
            }

            response.at<float>(y, x) =
                static_cast<float>(abs(sum));
        }
    }

    // Sonucu goruntulenebilir araliga getir
    normalize(
        response,
        output,
        0,
        255,
        NORM_MINMAX,
        CV_8UC1
    );

    cout << "Manuel 7x7 LoG filtresi uygulandi." << endl;
}
