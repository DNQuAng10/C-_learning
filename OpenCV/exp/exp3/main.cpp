#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;

const int NUMBER = 100;
const int DELAY = 10;

const int window_w = 900;
const int window_h = 600;
int x_1 = -window_w / 2;
int x_2 = window_w * 3 / 2;
int y_1 = -window_w / 2;
int y_2 = window_w * 3 / 2;

///Function headers
static Scalar randomColor( RNG& rng);
int Drawing_Random_Lines(Mat image, char* window_name, RNG rng);
int Drawing_Random_Rectangles(Mat image, char* window_name, RNG rng);
int Drawing_Random_Ellipses(Mat image, char* window_name, RNG rng);
int Drawing_Polylines(Mat image, char* window_name, RNG rng);

int main(void) {
    int c;
    char window_name[] = "Drawing random";

    /// Create a random object (RNG)
    RNG rng(0xFFFFFFFF);

    /// Initialize a matrix filled with zeros
    Mat img = Mat::zeros(window_h, window_w, CV_8UC3);

    imshow(window_name, img);
    waitKey(DELAY);

    /// Now let's draw some lines
    c = Drawing_Random_Lines(img, window_name, rng);
    if (c != 0) return 0;

    c = Drawing_Random_Rectangles(img, window_name, rng);
    if (c != 0) return 0;
    waitKey(0);
    return 0;
}

/// Function definitions

static Scalar randomColor(RNG& rng) {
    int icolor = (unsigned) rng;
    return Scalar( icolor&255, (icolor>>8)&255, (icolor>>16)&255);
}

int Drawing_Random_Lines(Mat img, char* window_name, RNG rng) {
    Point pt1, pt2;
    for (int i=0; i < NUMBER; i++) {
        pt1.x = rng.uniform(x_1, x_2);
        pt1.y = rng.uniform(y_1, y_2);
        pt2.x = rng.uniform(x_1, x_2);
        pt2.y = rng.uniform(y_1, y_2);

        // cout << "pt1.x: " << pt1.x << "\n";
        // cout << "pt2.x: " << pt2.x << "\n";
        // cout << "pt1.y: " << pt1.y << "\n";
        // cout << "pt2.y: " << pt2.y << "\n";

        line(img, pt1, pt2, randomColor(rng), rng.uniform(1, 10), 8);
        imshow(window_name, img);
        if (waitKey(DELAY) >= 0) return -1;
    }
    return 0;
}

int Drawing_Random_Rectangles(Mat img, char* window_name, RNG rng) {
    Point pt1, pt2;
    int lineType = 8;
    int thickness = rng.uniform(-3, 10);

    for (int i=0; i < NUMBER; i++) {
        pt1.x = rng.uniform(x_1, x_2);
        pt1.y = rng.uniform(y_1, y_2);
        pt2.x = rng.uniform(x_1, x_2);
        pt2.y = rng.uniform(y_1, y_2);

        rectangle(img, pt1, pt2, randomColor(rng), MAX(thickness, -1), lineType);
        imshow(window_name, img);
        if (waitKey(DELAY) >= 0) return -1;
    }

    return 0;
}