#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    const char* img_path_0 = "../test_img/car.jpg";
    const char* img_path_1 = "../test_img/car_1.jpg";
    const char* img_path_2 = "../test_img/co_vang_gray.jpg";

    Mat src_base = imread(samples::findFile(img_path_0));
    Mat src_1 = imread(samples::findFile(img_path_1));
    Mat src_2 = imread(samples::findFile(img_path_2));
    if (src_base.empty() || src_1.empty() || src_2.empty()) {
        cout << "Could not opening image: " << "\n";
        return EXIT_FAILURE;
    }

    Mat hsv_base, hsv_1, hsv_2;
    cvtColor(src_base, hsv_base, COLOR_BGR2HSV);
    cvtColor(src_1, hsv_1, COLOR_BGR2HSV);
    cvtColor(src_2, hsv_2, COLOR_BGR2HSV);

    Mat hsv_half_down = hsv_base(Range(hsv_base.rows / 2, hsv_base.rows), Range(0, hsv_base.cols));
    int h_bins = 50, s_bins = 60;
    int hist_size[] = {h_bins, s_bins};

    float h_ranges[] = {0, 180};
    float s_ranges[] = {0, 256};

    const float* ranges[] = {h_ranges, s_ranges};

    int channels[] = {0, 1};
    Mat hist_base, hist_half_down, hist_1, hist_2;
    calcHist(&hsv_base, 1, channels, Mat(), hist_base, 2, hist_size, ranges, true, false);
    normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());

    calcHist(&hsv_half_down, 1, channels, Mat(), hist_half_down, 2, hist_size, ranges, true, false);
    normalize(hist_half_down, hist_half_down, 0, 1, NORM_MINMAX, -1, Mat());

    calcHist(&hsv_1, 1, channels, Mat(), hist_1, 2, hist_size, ranges, true, false);
    normalize(hist_1, hist_1, 0, 1, NORM_MINMAX, -1, Mat());

    calcHist(&hsv_2, 1, channels, Mat(), hist_2, 2, hist_size, ranges, true, false);
    normalize(hist_2, hist_2, 0, 1, NORM_MINMAX, -1, Mat());

    for (int compare_method=0; compare_method < 4; compare_method++) {
        double base_base = compareHist(hist_base, hist_base, compare_method);
        double base_half = compareHist(hist_base, hist_half_down, compare_method);
        double base_1 = compareHist(hist_base, hist_1, compare_method);
        double base_2 = compareHist(hist_base, hist_2, compare_method);
        cout << "Method " << compare_method << " Perfect, Base-Half, Base-Test 1, Base-Test2: " << base_base << "/" << base_half << "/" << base_1 << "/" << base_2 << "\n";
    }
    cout << "DONE..." << "\n";
    return 0;
}