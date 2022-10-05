#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 51;

Mat src; Mat dst;
char window_name[] = "Smoothing";

int display_caption(const char* caption);
int display_dst(int delay);

int main(int argc, char** argv) {
    namedWindow(window_name, WINDOW_AUTOSIZE);
    const char* img_path = argc >= 2 ? argv[1]: "/home/dnq/Downloads/car_1.jpg";

    src = imread(samples::findFile(img_path), IMREAD_COLOR);
    if (src.empty()) {
        cout << "Error opening image\n";
        cout << "Usage:\n" << argv[0] << "[image_name --default car_1.jpg] \n";
        return EXIT_FAILURE;
    }
    if (display_caption("Original Image") != 0) return 0;
    dst = src.clone();
    if (display_dst(DELAY_CAPTION) != 0) return 0;
    if (display_caption("Homogeneous Blur") != 0) return 0;
    
    for (int i=1; i < MAX_KERNEL_LENGTH; i=i+2) {
        blur(src, dst, Size(i, i), Point(-1, -1));
        if (display_dst(DELAY_BLUR) != 0) return 0;
    }

    if (display_caption("Gaussian Blur") != 0) return 0;
    for (int i=1; i < MAX_KERNEL_LENGTH; i=i + 2) {
        GaussianBlur(src, dst, Size(i, i), (0, 0));
        if (display_dst(DELAY_BLUR) != 0) return 0;
    }

    if (display_caption("Median_Blur") != 0) return 0;
    for (int i=1; i < MAX_KERNEL_LENGTH; i = i + 2) {
        medianBlur(src, dst, i);
        if (display_dst(DELAY_BLUR) != 0) return 0;
    }

    // if (display_caption("Bilateral Blur") != 0) return 0;
    // for (int i=1; i < MAX_KERNEL_LENGTH; i = i + 2) {
    //     bilateralFilter(src, dst, i, i*2, i*2);
    //     if (display_dst(DELAY_BLUR) != 0) return 0;
    // }
    display_caption("DONE...");
    return 0;
}

int display_caption(const char* caption) {
    dst = Mat::zeros(src.size(), src.type());
    putText(dst, caption, Point(src.cols/4, src.rows/2), FONT_ITALIC,  1, Scalar(0, 244, 127));
    return display_dst(DELAY_CAPTION);
}

int display_dst(int delay) {
    imshow(window_name, dst);
    int c = waitKey(delay);
    if (c >= 0) return -1;
    return 0;
}