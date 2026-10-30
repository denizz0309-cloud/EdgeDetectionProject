
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

// Manuel 3x3 Laplacian kenar tespit algoritmasi
void laplacianFilter(
    const Mat& input,
    Mat& output)
{
    CV_Assert(input.type() == CV_8UC1);

    // 3x3 Laplacian kernel matrisi
    int kernel[3][3] =
    {
        {-1, -1, -1},
        {-1,  8, -1},
        {-1, -1, -1}
    };

    output = Mat::zeros(input.size(), CV_8UC1);

    Mat result = Mat::zeros(input.size(), CV_32FC1);

    // Goruntunun ic bolgesini tara
    for (int y = 1; y < input.rows - 1; y++)
    {
        for (int x = 1; x < input.cols - 1; x++)
        {
            int sum = 0;

            // 3x3 konvolusyon islemi
            for (int ky = -1; ky <= 1; ky++)
            {
                for (int kx = -1; kx <= 1; kx++)
                {
                    int pixel = input.at<uchar>(y + ky, x + kx);

                    sum += pixel * kernel[ky + 1][kx + 1];
                }
            }

            result.at<float>(y, x) = abs(sum);
        }
    }

    // Sonucu 0-255 araligina normalize et
    normalize(
        result,
        output,
        0,
        255,
        NORM_MINMAX,
        CV_8UC1
    );

    cout << "Manuel 3x3 Laplacian filtresi uygulandi." << endl;
}
