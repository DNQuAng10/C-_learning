#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    const char* default_img_path = "../test_img/car_1.jpg";
    const char* img_path = argc >= 2 ? argv[1] : default_img_path;

    Mat src = imread(samples::findFile(img_path));
    if (src.empty()) {
        cout << "Error opening image: " << img_path << "\n";
        return EXIT_FAILURE;
    }

    vector<Mat> bgr_planes;
    split(src, bgr_planes);

    int histSize = 256;
    // the upper boundary is exclusive
    float range[] = {0, 256};
    const float* histRange[] = {range};

    bool uniform = true, accumulate = false;

    Mat b_hist, g_hist, r_hist;
    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, histRange, uniform, accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, histRange, uniform, accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, histRange, uniform, accumulate);

    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double) hist_w / histSize);

    Mat hist_img(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

    normalize(b_hist, b_hist, 0, hist_img.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, hist_img.rows, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, hist_img.rows, NORM_MINMAX, -1, Mat());

    for (int i=1; i < histSize; i++) {
        line(hist_img, 
            Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))), 
            Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), 
            Scalar(255, 0, 0), 2, 8, 0);
        line(hist_img, 
            Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))), 
            Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))), 
            Scalar(0, 255, 0), 2, 8, 0);
        line(hist_img,
            Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))), 
            Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))), 
            Scalar(0, 0, 255), 2, 8, 0);
    }
    imshow("Src image: ", src);
    imshow("calcHist Demo: ", hist_img);
    waitKey(0);
    return 0;

}