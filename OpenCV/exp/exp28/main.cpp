#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

Mat gray;
int thresh = 100;
const int max_thresh = 255;
RNG rng(12345);
const char* winname = "Src";

void thresh_callback(int, void*) {
    Mat canny_out;
    Canny(gray, canny_out, thresh, thresh*2);

    vector<vector<Point>> contours;
    vector<Vec4i> hierachy;
    findContours(canny_out, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    Mat drawing = Mat::zeros(canny_out.size(), CV_8UC3);
    for (size_t i=0; i < contours.size(); i++) {
        Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        drawContours(drawing, contours, (int) i, color, 2, LINE_8, hierachy, 0);
    }
    if (thresh >= 100) {
        imshow(winname, drawing);
    }
    else if (thresh < 100 && thresh > 50) {
        imshow(winname, canny_out);
    }
    else {
        imshow(winname, gray);
    }
}

int main(int argc, char** argv) {
    const char* default_path = "../test_img/car_1.jpg";
    const char* img_path = argc >= 2 ? argv[1] : default_path;
    Mat src = imread(samples::findFile(img_path));
    if (src.empty()) {
        cout << "Error opening image: " << img_path << "\n";
        return EXIT_FAILURE;
    }
    cvtColor(src, gray, COLOR_BGR2GRAY);
    blur(gray, gray, Size(3, 3));

    namedWindow(winname);
    imshow(winname, src);

    createTrackbar("Canny thresh: ", winname, &thresh, max_thresh, thresh_callback);
    thresh_callback(0, 0);

    waitKey(0);
    return 0;

}