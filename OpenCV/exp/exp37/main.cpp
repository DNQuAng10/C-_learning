#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;


// Function calculates PSD (Power Spectrum Density) by fft with two flags
// flag = 0 means to return PSD
// flag = 1 means to return log(PSD)
void cal_psd(const Mat& in_img, Mat& out_img, int flag=0) {
    Mat planes[2] = {Mat_<float>(in_img.clone()), Mat::zeros(in_img.size(), CV_32F)};
    Mat complex_i;
    merge(planes, 2, complex_i);
    dft(complex_i, complex_i);
    split(complex_i, planes); //planes[0] = Re(DFT(I)), planes[1] = Im(DFT(I))

    planes[0].at<float>(0) = 0;
    planes[1].at<float>(0) = 0;

    // Compute the PSD = sqrt(Re(DFT(I))^2 + Im(DFT(I))^2)^2
    Mat psd_img;
    magnitude(planes[0], planes[1], psd_img);  // psd_img = sqrt(Power spectrum density)
    pow(psd_img, 2, psd_img);
    out_img = psd_img;

    // log_psd = log(1 + PSD)
    if (flag) {
        Mat psd_log_img;
        psd_log_img = psd_img + Scalar::all(1);
        log(psd_log_img, psd_log_img);
        out_img = psd_log_img;
    }
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

void synthesize_filter_H(Mat& in_out_H, Point c, int r) {
    Point c2 = c, c3 = c, c4 = c;
    c2.y = in_out_H.rows - c.y;
    c3.x = in_out_H.cols - c.x;
    c4 = Point(c3.x, c2.y);
    circle(in_out_H, c, r, 0, -1, 8);
    circle(in_out_H, c2, r, 0, -1, 8);
    circle(in_out_H, c3, r, 0, -1, 8);
    circle(in_out_H, c4, r, 0, -1, 8);
}

void filter2DFreq(const Mat& in_img, Mat& out_img, const Mat& H) {
    Mat planes[2] = {Mat_<float>(in_img.clone()), Mat::zeros(in_img.size(), CV_32F)};
    Mat complex_i;
    merge(planes, 2, complex_i);
    dft(complex_i, complex_i, DFT_SCALE);

    Mat planes_h[2] = {Mat_<float>(H.clone()), Mat::zeros(H.size(), CV_32F)};
    Mat complex_h;
    merge(planes_h, 2, complex_h);
    Mat complex_ih;
    mulSpectrums(complex_i, complex_h, complex_ih, 0);

    idft(complex_ih, complex_ih);
    split(complex_ih, planes);
    out_img = planes[0];
}

int main(int argc, char** argv) {
    const char* default_img_path = "../test_img/period.jpg";
    const char* img_path = argc >= 2 ? argv[1] : default_img_path;
    Mat img = imread(samples::findFile(img_path), IMREAD_GRAYSCALE);
    if (img.empty()) {
        cout << "Error opening image " << img_path << "\n";
        return EXIT_FAILURE;
    } 
    Mat in_img;
    in_img = img.clone();
    in_img.convertTo(in_img, CV_32F);
    Rect roi = Rect(0, 0, in_img.cols & -2, in_img.rows & -2);
    in_img = in_img(roi);

    Mat psd_img;
    cal_psd(in_img, psd_img);
    fftshift(psd_img, psd_img);
    normalize(psd_img, psd_img, 0, 255, NORM_MINMAX);

    Mat H = Mat(roi.size(), CV_32F, Scalar(1));
    const int r = 21;
    synthesize_filter_H(H, Point(705, 458), r);
    synthesize_filter_H(H, Point(850, 391), r);
    synthesize_filter_H(H, Point(993, 325), r);

    Mat out_img;
    fftshift(H, H);
    filter2DFreq(in_img, out_img, H);

    imshow("src: ", img);
    out_img.convertTo(out_img, CV_8U);
    normalize(out_img, out_img, 0, 255, NORM_MINMAX);
    imshow("result: ", out_img);
    imshow("psd: ", psd_img);
    fftshift(H, H);
    normalize(H, H, 0, 255, NORM_MINMAX);
    imshow("filter: ", H);
    waitKey(0);
    return 0;
}