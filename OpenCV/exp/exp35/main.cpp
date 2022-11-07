#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

const String keys = 
"{help h usage ? |          | print this message}"
"{image          |../test_img/motion_car_1.jpg | input image }"
"{LEN            | 125              | length of a motion}"
"{THETA          | 0                | angle of a motion in degrees}"
"{SNR            |700               | signal to noise ratio}";

void calc_psf(Mat& out_img, Size filter_size, int len, double theta) {
    Mat h(filter_size, CV_32F, Scalar(0));
    Point point(filter_size.width / 2, filter_size.height / 2);
    ellipse(h, point, Size(0, cvRound(float(len) / 2.0)), 90.0 - theta, 0, 360, Scalar(255), FILLED);
    Scalar summa = sum(h);
    out_img = h / summa[0];
} 

void fftshift(const Mat& in_img, Mat& out_img) {
    out_img = in_img.clone();
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

void calc_wnr_filter(const Mat& input_h_psf, Mat& output_G, double nsr) {
    Mat h_psf_shifted;
    fftshift(input_h_psf, h_psf_shifted);
    Mat planes[2] = {Mat_<float>(h_psf_shifted.clone()), Mat::zeros(h_psf_shifted.size(), CV_32F)};
    Mat complexi;
    merge(planes, 2, complexi);
    dft(complexi, complexi);
    split(complexi, planes);
    Mat denom;
    pow(abs(planes[0]), 2, denom);
    denom += nsr;
    divide(planes[0], denom, output_G);
}

void edgetaper(const Mat& in_img, Mat& out_img, double gamma, double beta) {
    int Nx = in_img.cols;
    int Ny = in_img.rows;
    Mat w1(1, Nx, CV_32F, Scalar(0));
    Mat w2(Ny, 1, CV_32F, Scalar(0));

    float* p1 = w1.ptr<float>(0);
    float* p2 = w2.ptr<float>(0);
    float dx = float(2.0 * CV_PI / Nx);
    float x = float(-CV_PI);
    for (int i=0; i < Nx; i++) {
        p1[i] = float(0.5 * (tanh((x + gamma / 2) / beta) - tanh((x - gamma / 2) / beta)));
        x += dx;
    }

    float dy = float(2.0 * CV_PI / Ny);
    float y = float(-CV_PI);
    for (int i=0; i < Ny; i++) {
        p2[i] = float(0.5 *(tanh((y+ gamma / 2) / beta) - tanh((y - gamma / 2) / beta)));
        y += dy;
    }
    Mat w = w2 * w1;
    multiply(in_img, w, out_img);
}

void filter2DFreq(const Mat& in_img, Mat& out_img, const Mat& H) {
    Mat planes[2] = {Mat_<float>(in_img.clone()), Mat::zeros(in_img.size(), CV_32F)};
    Mat complex_i;
    merge(planes, 2, complex_i);
    dft(complex_i, complex_i, DFT_SCALE);

    Mat planesh[2] = {Mat_<float>(H.clone()), Mat::zeros(H.size(), CV_32F)};
    Mat complex_h;
    merge(planesh, 2, complex_h);
    Mat complex_ih;
    mulSpectrums(complex_i, complex_h, complex_ih, 0);

    idft(complex_ih, complex_ih);
    split(complex_ih, planes);
    out_img = planes[0];

}

void edgetaper(const Mat& in_img, Mat& out_img, double gamma = 5.0, double beta = 0.2);

int main(int argc, char** argv) {
    CommandLineParser parser(argc, argv, keys);
    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }

    int len = parser.get<int>("LEN");
    double theta = parser.get<double>("THETA");
    int snr = parser.get<int>("SNR");
    string img_path = parser.get<String>("image");

    if (!parser.check()) {
        parser.printErrors();
        return 0;
    }

    Mat img = imread(img_path, IMREAD_GRAYSCALE);
    if (img.empty()) {
        cout << "Error opening image" << endl;
        return EXIT_FAILURE;
    }
    
    Mat dst;
    Rect roi = Rect(0, 0, img.cols & -2, img.rows & -2);

    Mat Hw, h;
    calc_psf(h, roi.size(), len, theta);
    calc_wnr_filter(h, Hw, 1.0 / double(snr));

    img.convertTo(img, CV_32F);
    edgetaper(img, img);

    filter2DFreq(img(roi), dst, Hw);

    dst.convertTo(dst, CV_8U);
    normalize(dst, dst, 0, 255, NORM_MINMAX);
    imshow("Src: ", img);
    imshow("Motion DeBlur Filter: ", dst);
    waitKey(0);
    return 0;
}