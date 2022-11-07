#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

const String keys = 
"{help h usage ? |                      | print help}"
"{image          |../test_img/blur.jpg  | input image}"
"{R              |53                    | radius}"
"{SNR            |5200                  | signal to noise ratio}";

void help() {
    cout << "DeBlur excercise \n";
}

void calcPSF(Mat& out_img, Size filter_size, int R) {
    Mat h(filter_size, CV_32F, Scalar(0));
    Point point(filter_size.width / 2, filter_size.height / 2);
    circle(h, point, R, 255, -1, 8);
    Scalar summa = sum(h);
    out_img = h/summa[0];
}

void ffshift(const Mat& input_img, Mat& out_img) {
    out_img = input_img.clone();
    int cx = out_img.cols / 2;
    int cy = out_img.rows / 2;
    Mat q0(out_img, Rect(0, 0, cx, cy));
    Mat q1(out_img, Rect(cx, 0, cx, cy));
    Mat q2(out_img, Rect(0, cy, cx, cy));
    Mat q3(out_img, Rect(cx, cy, cx, cy));
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
}

void calcWnrFilter(const Mat& input_h_psf, Mat& output_g, double nsr) {
    Mat h_psf_shifted;
    ffshift(input_h_psf, h_psf_shifted);
    Mat planes[2] = {
        Mat_<float>(h_psf_shifted.clone()),
        Mat::zeros(h_psf_shifted.size(), CV_32F)
    };
    Mat complexi;
    merge(planes, 2, complexi);
    dft(complexi, complexi);
    split(complexi, planes);
    Mat denom;
    pow(abs(planes[0]), 2, denom);
    denom += nsr;
    divide(planes[0], denom, output_g);
}

void filter2DFreq(const Mat& input_img, Mat& out_img, const Mat& H) {
    Mat planes[2] = {
        Mat_<float>(input_img.clone()), 
        Mat::zeros(input_img.size(), CV_32F)
    };
    Mat complexi;
    merge(planes, 2, complexi);
    dft(complexi, complexi, DFT_SCALE);

    Mat planesH[2] = {
        Mat_<float>(H.clone()),
        Mat::zeros(H.size(), CV_32F)
    };
    Mat complexh;
    merge(planesH, 2, complexh);
    Mat complexih;
    mulSpectrums(complexi, complexh, complexih, 0);

    idft(complexih, complexih);
    split(complexih, planes);
    out_img = planes[0];
}

int main(int argc, char** argv) {
    help();
    CommandLineParser parser(argc, argv, keys);
    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }

    int R = parser.get<int>("R");
    int snr = parser.get<int>("SNR");
    string img_path = parser.get<String>("image");

    if (!parser.check()) {
        parser.printErrors();
        return 0;
    }

    Mat img;
    img = imread(img_path, IMREAD_GRAYSCALE);
    if (img.empty()) {
        cout << "ERROR: opening image.." << endl;
        return -1;
    }

    Mat dst;
    Rect roi = Rect(0, 0, img.cols & -2, img.rows & -2);

    Mat Hw, h;
    calcPSF(h, roi.size(), R);
    calcWnrFilter(h, Hw, 1.0 / double(snr));

    filter2DFreq(img(roi), dst, Hw);

    dst.convertTo(dst, CV_8U);
    normalize(dst, dst, 0, 255, NORM_MINMAX);
    imshow("src: ", img);
    imshow("DeBlur: ", dst);
    waitKey(0);
    return 0;
}