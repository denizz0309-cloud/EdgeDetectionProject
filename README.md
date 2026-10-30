# Kenar Algılama Projesi (Edge Detection)

## Proje Hakkında

Bu proje, görüntü işleme tekniklerini kullanarak dijital görüntülerdeki kenarların tespit edilmesini amaçlamaktadır. C++ programlama dili ve OpenCV kütüphanesi kullanılarak farklı kenar algılama algoritmaları manuel olarak uygulanmış ve OpenCV'nin hazır Canny algoritmasıyla karşılaştırılmıştır.

## Kullanılan Teknolojiler

- C++
- OpenCV 4.14.0
- Visual Studio 2022
- C++17

## Uygulanan Algoritmalar

### 1. Prewitt Kenar Algılama
- Birinci Prewitt kernel uygulaması
- İkinci Prewitt kernel uygulaması
- Yatay ve dikey kenarların tespiti

### 2. Sobel Kenar Algılama
- Yatay ve dikey Sobel filtreleri
- Gradyan büyüklüğünün hesaplanması

### 3. Laplacian Kenar Algılama
- 3x3 Laplacian filtresi

### 4. Laplacian of Gaussian (LoG)
- 7x7 LoG filtresi

### 5. OpenCV Canny
- OpenCV'nin hazır Canny fonksiyonu kullanılarak kenar tespiti

### 6. Manuel Canny Algoritması
Manuel Canny algoritması dört aşamada uygulanmıştır:

1. 5x5 Gaussian Blur
2. Sobel Gradyan Hesaplama
3. Non-Maximum Suppression
4. Hysteresis Thresholding

## Çoklu İş Parçacığı (Multithreading)

Performansı artırmak amacıyla manuel Canny algoritmasının Gaussian Blur, Sobel Gradyan ve Non-Maximum Suppression aşamalarında çoklu iş parçacığı kullanılmıştır.

## Proje Çıktıları

Algoritmaların uygulama sonuçları PNG formatında kaydedilmiştir. Görseller, farklı filtrelerin ve kenar algılama yöntemlerinin sonuçlarını karşılaştırmak amacıyla projeye eklenmiştir.

## Nasıl Çalıştırılır?

1. Projeyi bilgisayarınıza indirin veya klonlayın.
2. `EdgeDetectionProject.sln` dosyasını Visual Studio 2022 ile açın.
3. OpenCV kütüphanesinin bilgisayarınızda kurulu olduğundan emin olun.
4. Yapılandırmayı Release x64 olarak seçin.
5. Projeyi derleyin ve çalıştırın.

## Geliştirme Ortamı

- İşletim Sistemi: Windows
- IDE: Visual Studio 2022
- Programlama Dili: C++
- Görüntü İşleme Kütüphanesi: OpenCV
