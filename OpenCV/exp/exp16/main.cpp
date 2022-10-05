#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

Mat src, gray, hsv;
Mat dst, detected_edges;
int low_thresh = 0;
const int max_thresh = 100;
const int rate = 3;
const int ksize = 3;
const char* winname = "edge map";

static void canny_thresh(int, void*) {
    blur(gray, detected_edges, Size(3, 3));
    Canny(detected_edges, detected_edges, low_thresh, low_thresh * rate, ksize);
    dst = Scalar::all(0);
    // src.copyTo(dst, detected_edges);
    // gray.copyTo(dst, detected_edges);
    hsv.copyTo(dst, detected_edges);
    imshow(winname, dst);
}

int main(int argc, char** argv) {
    CommandLineParser parser(argc, argv, "{@input | /home/dnq/Downloads/car_1.jpg | input image}");
    src = imread(samples::findFile(parser.get<String>("@input")));

    if (src.empty()) {
        cout << "Error opening image " << parser.get<String>("@input") << "\n";
        return EXIT_FAILURE;
    }
    dst.create(src.size(), src.type());
    cvtColor(src, gray, COLOR_BGR2GRAY);
    cvtColor(src, hsv, COLOR_BGR2HSV);
    namedWindow(winname, WINDOW_AUTOSIZE);
    createTrackbar("Min Threshold: ", winname, &low_thresh, max_thresh, canny_thresh);
    canny_thresh(0, 0);
    waitKey(0);
    return 0;
}