#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int const max_H_vl = 360 / 2;
int const max_vl = 255;
const String win_cap_name = "Video Capture";
const String win_detect_name = "Object Detection";

int low_H = 0, low_S = 0, low_V = 0;
int high_H = max_H_vl, high_S = max_vl, high_V = max_vl;

static void on_low_H_thresh_trackbar(int, void*) {
    low_H = min(high_H - 1, low_H);
    setTrackbarPos("Low H", win_detect_name, low_H);
}

static void on_high_H_thresh_trackbar(int, void*) {
    high_H = max(high_H, low_H + 1);
    setTrackbarPos("High H", win_detect_name, high_H);
}

static void on_low_S_thresh_trackbar(int, void*) {
    low_S = min(high_S - 1, low_S);
    setTrackbarPos("Low S", win_detect_name, low_S);
}

static void on_high_S_thresh_trackbar(int, void*) {
    high_S = max(high_S, low_S + 1);
    setTrackbarPos("High S", win_detect_name, high_S);
}

static void on_low_V_thresh_trackbar(int, void*) {
    low_V = min(high_V - 1, low_V);
    setTrackbarPos("Low V", win_detect_name, low_V);
}

static void on_high_V_thresh_trackbar(int, void*) {
    high_V = max(high_V, low_V + 1);
    setTrackbarPos("High V", win_detect_name, high_V);
}

int main(int argc, char** argv) {
    CommandLineParser parser(argc, argv, "{@input | /home/dnq/Downloads/out_1.mp4 | video path}");
    // if (argc != 2) {
    //     cout << "Enter video path\n";
    //     return -1;
    // }
    VideoCapture cap(samples::findFile(parser.get<String>("@input")), IMREAD_COLOR);

    namedWindow(win_cap_name);
    namedWindow(win_detect_name);

    // Trackbars to set threshold for HSV values
    createTrackbar("Low H", win_detect_name, &low_H, max_H_vl, on_low_H_thresh_trackbar);
    createTrackbar("High H", win_detect_name, &high_H, max_H_vl, on_high_H_thresh_trackbar);
    createTrackbar("Low S", win_detect_name, &low_S, max_vl, on_low_S_thresh_trackbar);
    createTrackbar("High S", win_detect_name, &high_S, max_vl, on_high_S_thresh_trackbar);
    createTrackbar("Low V", win_detect_name, &low_V, max_vl, on_low_V_thresh_trackbar);
    createTrackbar("High V", win_detect_name, &high_V, max_vl, on_high_V_thresh_trackbar);

    Mat frame, frame_HSV, frame_thresh;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }

        cvtColor(frame, frame_HSV, COLOR_BGR2HSV);
        // Detect the object based on HSV range values
        inRange(frame_HSV, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), frame_thresh);

        imshow(win_cap_name, frame);
        imshow(win_detect_name, frame_thresh);

        char key = (char)waitKey(30);
        if (key == 113) break;
    }
    return 0;
} 

