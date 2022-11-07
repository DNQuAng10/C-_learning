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
const char* winname = "Bounding Rect Circle";
RNG rng(12345);

void thresh_callback(int, void*) {
    Mat canny_out;
    Canny(gray, canny_out, thresh, thresh*2);

    vector<vector<Point>> contours;
    findContours(canny_out, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> contours_poly(contours.size());
    vector<Rect> bound_rect(contours.size());
    vector<Point2f> centers(contours.size());
    vector<float> radius(contours.size());

    for(size_t i=0; i < contours.size(); i++) {
        approxPolyDP(contours[i], contours_poly[i], 3, true);
        bound_rect[i] = boundingRect(contours_poly[i]);
        minEnclosingCircle(contours_poly[i], centers[i], radius[i]);
    }

    Mat drawing = Mat::zeros(canny_out.size(), CV_8UC3);

    for(size_t i=0; i < contours.size(); i++) {
        Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        drawContours(drawing, contours_poly, (int)i, color);
        rectangle(drawing, bound_rect[i].tl(), bound_rect[i].br(), color, 2);
        circle(drawing, centers[i], (int)radius[i], color, 2);
    }
    imshow(winname, drawing);
}

int main(int argc, char** argv) {
    const char* default_img_path = "../test_img/ball.png";
    const char* img_path = argc >= 2 ? argv[1] : default_img_path;
    src = imread(samples::findFile(img_path));
    if (src.empty()) {
        cout << "Error opening image: " << img_path << "\n";
        return EXIT_FAILURE;
    }

    cvtColor(src, gray, COLOR_BGR2GRAY);
    blur(gray, gray, Size(3, 3));

    namedWindow(winname, WINDOW_AUTOSIZE);
    createTrackbar("Canny thresh: ", winname, &thresh, max_thresh, thresh_callback);
    thresh_callback(0, 0);
    waitKey();
    return 0;
}