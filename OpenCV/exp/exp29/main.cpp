#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

Mat src, gray;
int thresh = 100;
const int max_thresh = 255;
const char* winname = "Convex Hull";
RNG rng(12345);

void thresh_callback(int, void*) {
    Mat canny_output;
    Canny(gray, canny_output, thresh, thresh*2);

    vector<vector<Point>> contours;
    findContours(canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> hull(contours.size());
    for (size_t i=0; i < contours.size(); i++) {
        convexHull(contours[i], hull[i]);
    }

    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    for (size_t i=0; i < contours.size(); i++) {
        Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        drawContours(drawing, contours, (int)i, color);
        drawContours(drawing, hull, (int)i, color);
    }
    if (thresh == 0) {
        imshow(winname, src);
    }
    else {
        imshow(winname, drawing);
    }
}

int main(int argc, char** argv) {
    const char* default_img_path = "../test_img/face.jpg";
    const char* img_path = argc >= 2 ? argv[1] : default_img_path;

    src = imread(samples::findFile(img_path));
    if (src.empty()) {
        cout << "Error opening image: " << img_path << "\n";
        return EXIT_FAILURE;
    }

    resize(src, src, Size(500, 500));
    cvtColor(src, gray, COLOR_BGR2GRAY);
    blur(gray, gray, Size(3, 3));

    namedWindow(winname);
    createTrackbar("Canny thresh: ", winname, &thresh, max_thresh, thresh_callback);
    thresh_callback(0, 0);

    waitKey();
    return 0;
    
}