#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat img = imread("pista_PALTAN_CHUNCHO_KLEBER_ARIEL.png", IMREAD_GRAYSCALE);

    // Encontrar I_min e I_max
    uchar I_min = 255, I_max = 0;
    for (int r = 0; r < img.rows; ++r) {
        const uchar* row = img.ptr<uchar>(r);
        for (int c = 0; c < img.cols; ++c) {
            uchar p = row[c];
            if (p < I_min) I_min = p;
            if (p > I_max) I_max = p;
        }
    }

    if (I_max == I_min) {
        cerr << "La imagen no tiene variacion de contraste" << endl;
        return -1;
    }

    // Aplicar estiramiento de contraste
    Mat result = Mat::zeros(img.size(), img.type());
    for (int r = 0; r < img.rows; ++r) {
        const uchar* src = img.ptr<uchar>(r);
        uchar* dst = result.ptr<uchar>(r);
        for (int c = 0; c < img.cols; ++c) {
            float val = (float)(src[c] - I_min) / (I_max - I_min) * 255.0f;
            dst[c] = saturate_cast<uchar>(val);
        }
    }

    imshow("Original", img);
    imshow("Codigo revelado", result);
    imwrite("codigo_revelado.png", result);

    cout << "I_min = " << (int)I_min << ", I_max = " << (int)I_max << endl;
    cout << "Resultado guardado en codigo_revelado.png" << endl;
    cout << "Presione cualquier tecla para salir..." << endl;
    waitKey(0);
    return 0;
}
