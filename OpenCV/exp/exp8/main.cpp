#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

const char* winname = "Pyramid Demo";

int main(int argc, char** argv) {
    cout << "\nZoom In-Out demo\n"
            "------------------\n"
            " * [i] -> Zoom in  \n"
            " * [o] -> Zoom out \n"
            " * [ESC] -> Close program \n" << endl;
    const char* filename = argc >= 2 ? argv[1] : "/home/dnq/Downloads/car_1.jpg";
    // Loads and image 
    Mat src = imread(samples::findFile(filename));
    if (src.empty()) {
        cout << "Error opening image\n";
        return EXIT_FAILURE;
    }

    for (;;) {
        imshow(winname, src);
        int c = (int)waitKey(0);
        // cout << "c: " << c << endl;

        if (c == 113) {
            break;
        }
        else if (c == 105) {
            pyrUp(src, src, Size(src.cols * 2, src.rows * 2));
            cout << "Zoom In ++" << src.cols * 2 << ", " << src.rows * 2 << "\n";
        }
        else if (c == 111) {
            pyrDown(src, src, Size(src.cols / 2, src.rows / 2));
            cout << "Zoom Out --" << src.cols / 2 << ", " << src.rows / 2 << "\n";
        }
    }
    return EXIT_SUCCESS;

}