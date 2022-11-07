#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

Mat src, gray, dst;
int min_min_radius_value = 1;
int min_max_radius_value = 30;
int min_dis = 1;
const int max_min_radius_value = 100;
const int max_max_radius_value = 300;
const int max_dis = 10;

const char* winname = "Circle Detection";
const char* tbar_dis = "Distance: ";
const char* tbar_min_r = "MIN Radius: ";
const char* tbar_max_r = "MAX Radius: ";

static void circle_detection(int, void*) {
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                gray.rows / min_dis, // change this value to detect circles with different distances to each other
                100, 30, min_min_radius_value, min_max_radius_value // change the last two parameters (min-max radius) to detect larger circles
    );
    // cout << "Right...:" ;
    for (size_t i = 0; i < circles.size(); i++) {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        circle(dst, center, 1, Scalar(0, 0, 255), 3, LINE_AA);
        int radius = c[2];
        circle(dst, center, radius, Scalar(128, 0, 166), 3, LINE_AA);
    }
    imshow("detected circles: ", dst);
    // char c = (char)waitKey(0);
    // if (c == 114) {
    //     destroyAllWindows();
    //     imshow("detected circles: ", dst);
    // }
}

int main(int argc, char** argv) {
    const char* default_img = "/home/dnq/Downloads/ball_1.jpg";
    const char* img_path = argc >=2 ? argv[1] : default_img;

    Mat src = imread(samples::findFile(img_path));
    cout << src.rows << "\n";
    if (src.empty()) {
        cout << "Error opening image: " << img_path << "\n";
        return -1;
    }

    cvtColor(src, gray, COLOR_BGR2GRAY);
    medianBlur(gray, gray, 5);
    dst = src.clone();
    
    namedWindow(winname, WINDOW_AUTOSIZE);
    createTrackbar(tbar_dis, winname, &min_dis, max_dis, circle_detection);
    createTrackbar(tbar_min_r, winname, &min_min_radius_value, max_min_radius_value, circle_detection);
    createTrackbar(tbar_max_r, winname, &min_max_radius_value, max_max_radius_value, circle_detection);
    // createTrackbar(tbar_max_r, winname, nullptr, max_max_radius_value, circle_detection);
    // setTrackbarPos(tbar_max_r, winname, min_max_radius_value);
    circle_detection(0, 0);
    waitKey();
    return EXIT_SUCCESS;
}