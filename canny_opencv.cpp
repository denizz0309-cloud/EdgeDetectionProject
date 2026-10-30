
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// OpenCV hazir Canny kenar tespit algoritmasi
void cannyOpenCV(
    const Mat& input,
    Mat& output)
{
    CV_Assert(input.type() == CV_8UC1);

    // Canny oncesinde Gaussian ile gurultuyu azalt
    Mat blurred;

    GaussianBlur(
        input,
        blurred,
        Size(5, 5),
        1.4
    );

    // OpenCV Canny algoritmasi
    Canny(
        blurred,
        output,
        50,
        150,
        3,
        true
    );

    cout << "OpenCV Canny algoritmasi uygulandi." << endl;
}
