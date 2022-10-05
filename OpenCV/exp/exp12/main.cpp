#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <string>

using namespace cv;
using namespace std;

int main (int argc, char** argv) {
    Mat src, dst;
    Mat kernel;
    Point anchor;
    double delta;
    int depth;
    int kernel_size;
    const char* window_name = "filter2D Demo";
    const char* imageName = argc >= 2 ? argv[1] : "/home/dnq/Downloads/car_1.jpg";

    src = imread(samples::findFile(imageName), IMREAD_COLOR);
    if (src.empty()) {
        cout << "Cann't load image " << imageName << "\n";
        return EXIT_FAILURE;
    }

    anchor = Point(-1, -1);
    delta = 0;
    depth = -1;

    // Loop will filter the image with different kernel sizes each 0.5 sec
    int ind = 0;
    for (;;) {
        kernel_size = 3 + 2 * (ind%11);
        kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size * kernel_size);
        cout << kernel.size() << "\n";
        string text_size = "Kernel size: " + to_string(kernel.size[0]) + "x" + to_string(kernel.size[1]); 
        filter2D(src, dst, depth, kernel, anchor, delta, BORDER_DEFAULT);
        putText(dst, text_size, Point(50, 50), FONT_ITALIC, 1.5, Scalar(0, 255, 0), 2);
        imshow(window_name, dst);

        char c = (char)waitKey(500);
        if (c == 113) {
            break;
        }
        ind ++;
    }
    return EXIT_SUCCESS;
}