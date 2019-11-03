#include <vector>

#include "contours.hpp"
#include "qrcode.hpp"

int main(int argc, char** argv)
{
    Mat all_qr[4];
    if (argc < 5)
    {
        cout << "need more image!" << endl;
        return 0;
    }
    for (int i = 1; i <= 4; ++i)
    {
        Mat src = imread(argv[i]);
        QRcode_section_detect(src, all_qr);
    }
    Mat qrcode = QRcode_section_splice(all_qr);
    namedWindow("qr_info", WINDOW_AUTOSIZE);
    imshow("qr_info", qrcode);
    waitKey(0);
    QRCodeDetector test;
    string msg = test.detectAndDecode(qrcode);
    cout << msg << endl;
    return 0;
}
