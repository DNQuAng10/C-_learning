#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int thresh_vl = 0;
int thresh_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;

Mat src, gray, dst;
const char* winname = "Threshold Demo";
const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_vl = "value";

static void Thresh_Demo(int, void*) {
    /*
    0: Binary
    1: Binary Inverted
    2: Threshold Truncate
    3: Threshold to Zero
    4: Threshold to Zero Inverted 
    */
   cout << "Threshold value: " << thresh_vl << "\n";
   threshold(gray, dst, thresh_vl, max_binary_value, thresh_type);
   imshow(winname, dst);
}

int main(int argc, char** argv) {
    String imageName("/home/dnq/Downloads/car_1.jpg"); // DEFAULT
    if (argc > 1) {
        imageName = argv[1];
    }
    src = imread(samples::findFile(imageName), IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cannot read the image " << imageName << endl;
        return -1;
    }
    cvtColor(src, gray, COLOR_BGR2GRAY);
    namedWindow(winname, WINDOW_AUTOSIZE);
    createTrackbar(trackbar_type, winname, &thresh_type, max_type, Thresh_Demo);
    createTrackbar(trackbar_vl, winname, &thresh_vl, max_value, Thresh_Demo);
    Thresh_Demo(0, 0);
    waitKey(0);
    return 0;
}