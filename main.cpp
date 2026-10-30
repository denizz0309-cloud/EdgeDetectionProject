#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


// =====================================================
// FONKSIYON BILDIRIMLERI
// =====================================================

// Prewitt
void prewittFilter(const Mat&, Mat&, Mat&, Mat&);
void prewittFilterSecond(const Mat&, Mat&, Mat&, Mat&);

// Sobel
void sobelFilter(const Mat&, Mat&, Mat&, Mat&);

// Laplacian
void laplacianFilter(const Mat&, Mat&);

// 7x7 LoG
void logFilter7x7(const Mat&, Mat&);

// OpenCV Canny
void cannyOpenCV(const Mat&, Mat&);

// Manuel Canny
Mat gaussianBlurManual(const Mat&);

void sobelGradient(
    const Mat& input,
    Mat& magnitude,
    Mat& direction
);

Mat nonMaximumSuppression(
    const Mat& magnitude,
    const Mat& direction
);

void hysteresisThreshold(
    const Mat& input,
    Mat& output,
    float lowThreshold,
    float highThreshold
);


// =====================================================
// MAIN
// =====================================================

int main()
{
    // 1. Orijinal goruntuyu oku
    Mat original = imread("edge_input.png", IMREAD_GRAYSCALE);

    if (original.empty())
    {
        cout << "HATA: Goruntu bulunamadi!" << endl;
        return -1;
    }

    cout << "Goruntu basariyla yuklendi!" << endl;


    // =================================================
    // 2. GAUSSIAN BLUR
    // =================================================

    Mat blurred;
    GaussianBlur(original, blurred, Size(5, 5), 1.0);


    // =================================================
    // 3. BIRINCI PREWITT
    // =================================================

    Mat prewitt1X, prewitt1Y, prewitt1Combined;

    prewittFilter(
        blurred,
        prewitt1X,
        prewitt1Y,
        prewitt1Combined
    );


    // =================================================
    // 4. IKINCI PREWITT
    // =================================================

    Mat prewitt2X, prewitt2Y, prewitt2Combined;

    prewittFilterSecond(
        blurred,
        prewitt2X,
        prewitt2Y,
        prewitt2Combined
    );


    // =================================================
    // 5. SOBEL
    // =================================================

    Mat sobelX, sobelY, sobelCombined;

    sobelFilter(
        blurred,
        sobelX,
        sobelY,
        sobelCombined
    );


    // =================================================
    // 6. LAPLACIAN 3x3
    // =================================================

    Mat laplacianResult;

    laplacianFilter(
        blurred,
        laplacianResult
    );


    // =================================================
    // 7. LAPLACIAN OF GAUSSIAN 7x7
    // =================================================

    Mat logResult;

    logFilter7x7(
        original,
        logResult
    );


    // =================================================
    // 8. OPENCV HAZIR CANNY
    // =================================================

    Mat cannyResult;

    cannyOpenCV(
        original,
        cannyResult
    );


    // =================================================
    // 9. MANUEL CANNY - 1. ADIM
    // 5x5 Gaussian Smoothing
    // =================================================

    Mat manualGaussian = gaussianBlurManual(original);


    // =================================================
    // 10. MANUEL CANNY - 2. ADIM
    // Sobel Gradient
    // =================================================

    Mat gradientMagnitude;
    Mat gradientDirection;

    sobelGradient(
        manualGaussian,
        gradientMagnitude,
        gradientDirection
    );


    // =================================================
    // 11. MANUEL CANNY - 3. ADIM
    // Non-Maximum Suppression
    // =================================================

    Mat nmsResult;

    nmsResult = nonMaximumSuppression(
        gradientMagnitude,
        gradientDirection
    );


    // =================================================
    // 12. MANUEL CANNY - 4. ADIM
    // Hysteresis Thresholding
    // =================================================

    Mat manualCannyResult;

    // Yeni Hysteresis fonksiyonu normalize edilmemis
    // gradyan buyuklugu uzerinde esikleme yapar.
    // Bu nedenle baslangic esikleri 50 ve 150'dir.
    hysteresisThreshold(
        nmsResult,
        manualCannyResult,
        50.0f,
        150.0f
    );


    // =================================================
    // 13. SONUCLARI KAYDET
    // =================================================

    imwrite("01_gray_image.png", original);
    imwrite("02_gaussian_blur.png", blurred);

    imwrite("03_prewitt1_gx.png", prewitt1X);
    imwrite("04_prewitt1_gy.png", prewitt1Y);
    imwrite("05_prewitt1_combined.png", prewitt1Combined);

    imwrite("06_prewitt2_gx.png", prewitt2X);
    imwrite("07_prewitt2_gy.png", prewitt2Y);
    imwrite("08_prewitt2_combined.png", prewitt2Combined);

    imwrite("09_sobel_gx.png", sobelX);
    imwrite("10_sobel_gy.png", sobelY);
    imwrite("11_sobel_combined.png", sobelCombined);

    imwrite("12_laplacian_3x3.png", laplacianResult);
    imwrite("13_log_7x7.png", logResult);

    imwrite("14_canny_opencv.png", cannyResult);


    // =================================================
    // 14. MANUEL CANNY ARA SONUCLARINI GORUNTULEMEYE
    // UYGUN HALE GETIR
    // =================================================

    Mat manualGaussianDisplay;
    Mat magnitudeDisplay;
    Mat nmsDisplay;

    normalize(
        manualGaussian,
        manualGaussianDisplay,
        0,
        255,
        NORM_MINMAX,
        CV_8UC1
    );

    normalize(
        gradientMagnitude,
        magnitudeDisplay,
        0,
        255,
        NORM_MINMAX,
        CV_8UC1
    );

    normalize(
        nmsResult,
        nmsDisplay,
        0,
        255,
        NORM_MINMAX,
        CV_8UC1
    );

    imwrite("15_manual_gaussian.png", manualGaussianDisplay);
    imwrite("16_manual_sobel_magnitude.png", magnitudeDisplay);
    imwrite("17_manual_nms.png", nmsDisplay);
    imwrite("18_manual_canny.png", manualCannyResult);


    // =================================================
    // 15. SONUCLARI EKRANDA GOSTER
    // =================================================

    imshow("Orijinal Goruntu", original);
    imshow("Gaussian Blur", blurred);

    imshow("Birinci Prewitt", prewitt1Combined);
    imshow("Ikinci Prewitt", prewitt2Combined);

    imshow("Sobel", sobelCombined);

    imshow("Laplacian 3x3", laplacianResult);
    imshow("LoG 7x7", logResult);

    imshow("OpenCV Canny", cannyResult);

    imshow("Manuel Canny - Gaussian", manualGaussianDisplay);
    imshow("Manuel Canny - Sobel", magnitudeDisplay);
    imshow("Manuel Canny - NMS", nmsDisplay);
    imshow("Manuel Canny - Final", manualCannyResult);


    // =================================================
    // 16. PROGRAMI BITIR
    // =================================================

    cout << endl;
    cout << "Tum kenar tespit islemleri tamamlandi!" << endl;
    cout << "OpenCV Canny ve Manuel Canny sonuclari olusturuldu." << endl;

    waitKey(0);
    destroyAllWindows();

    return 0;
}
