#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int w = 52;
double c_thresh = 0.43;
const int max_w = 100;
int low_thresh = 35;
const int max_low_thresh = 180;
int high_thresh = 57;
const int max_high_thresh = 180;
const char* winname = "thresh";

Mat src, coherency_img, orient_img, coherency_bin_img, orient_bin_img, bin_img;

void cal_gst(int, void*) {
    Mat img;
    src.convertTo(img, CV_32F);

    // GST components calculation (start)
    // J = (J11 J12; J12 J22) - GST
    Mat diff_x, diff_y, diff_xy;
    Sobel(img, diff_x, CV_32F, 1, 0, 3);
    Sobel(img, diff_y, CV_32F, 0, 1, 3);
    multiply(diff_x, diff_y, diff_xy);

    Mat diff_xx, diff_yy;
    multiply(diff_x, diff_x, diff_xx);
    multiply(diff_y, diff_y, diff_yy);

    Mat J11, J22, J12; //J11, J22, J12 are GST components
    if (w < 10) {
        w = 10;
    }
    boxFilter(diff_xx, J11, CV_32F, Size(w, w));
    boxFilter(diff_yy, J22, CV_32F, Size(w, w));
    boxFilter(diff_xy, J12, CV_32F, Size(w, w));

    // GST components calculation (Stop)
    // eigenvalue calculation (start)
    // lambda1 = 0.5 * (J11 + J22 + sqrt((J11 - J22)^2 + 4 * J12^2))
    // lambda2 = 0.5 * (J11 + J22 - sqrt((J11 - J22)^2 + 4 * J12^2))
    Mat tmp1, tmp2, tmp3, tmp4;
    tmp1 = J11 + J22;
    tmp2 = J11 + J22;
    multiply(tmp2, tmp2, tmp2);
    multiply(J12, J12, tmp3);
    sqrt(tmp2 + 4.0 * tmp3, tmp4);

    Mat lambda1, lambda2;
    lambda1 = tmp1 + tmp4;
    lambda1 = 0.5 * lambda1; // biggest eigenvalue
    lambda2 = tmp1 - tmp4;
    lambda2 = 0.5 * lambda2; // smallest eigenvalue
    // eigenvalue calculation (stop)

    // Coherency calculation (start)
    // Coherency = (lambda1 - lambda2) / (lambda1 + lambda2) - measure of anisotropism
    // Coherency is anisotropy degree (consistency of local orientation)
    divide(lambda1 - lambda2, lambda1 + lambda2, coherency_img);
    // Coherency calculation (stop)

    // orientation angle calculation (start)
    //tan(2 * alpha) = 2 * J12 / (J22 - J11)
    // alpha = 0.5 atan2(2 * J12 / (J22 - J11))
    phase(J22 - J11, 2.0 * J12, orient_img, true);
    orient_img = 0.5 * orient_img;
    // orientation angle calculation (stop)

    coherency_bin_img = coherency_img > c_thresh;
    inRange(orient_img, Scalar(low_thresh), Scalar(high_thresh), orient_bin_img);

    bin_img = coherency_bin_img & orient_bin_img;

    normalize(coherency_img, coherency_img, 0, 255, NORM_MINMAX);
    normalize(orient_img, orient_img, 0, 255, NORM_MINMAX);

    imshow(winname, src);
    imshow("result: ", 0.5 * (src + bin_img));
    imshow("coherency: ", coherency_img);
    imshow("orientation: ", orient_img);

}

int main(int argc, char** argv) {
    const char* default_img_path = "../test_img/anis.jpg";
    const char* img_path = argc >= 2 ? argv[1] : default_img_path;
    src = imread(samples::findFile(img_path), IMREAD_GRAYSCALE);
    if (src.empty()) {
        cout << "Error opening image " << img_path << "\n";
        return EXIT_FAILURE;
    }
    namedWindow(winname, WINDOW_AUTOSIZE);
    createTrackbar("window size", winname, &w, max_w, cal_gst);
    createTrackbar("low threshold", winname, &low_thresh, max_low_thresh, cal_gst);
    createTrackbar("high threshold", winname, &high_thresh, max_high_thresh, cal_gst);
    cal_gst(0, 0);
    waitKey(0);
    return 0;

}