#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    Mat src, gray, dst;
    int ksize = 3;
    int scale = 1;
    int delta = 0;
    int depth = CV_16S;
    const char* winname = "Laplace Edge Detection";
    const char* img_path = argc >= 2 ? argv[1] : "/home/dnq/Downloads/car_1.jpg";
    src = imread(samples::findFile(img_path));
    if (src.empty()) {
        cout << "Error opening image " << img_path << "\n";
        return -1;
    }

    // Reduce noise by blurring with a Gaussian filter (3x3)
    GaussianBlur(src, src, Size(ksize, ksize), 0, 0, BORDER_DEFAULT);
    cvtColor(src, gray, COLOR_BGR2GRAY);

    cout << "press 'k' to increase kernel size value\n";
    cout << "press 's' to increase scale value\n";
    cout << "press 'r' to reset all value\n";
    for (;;) {
        Mat abs_dst;

        Laplacian(gray, dst, depth, ksize, scale, delta, BORDER_DEFAULT);
        // Converting back to CV_8U
        convertScaleAbs(dst, abs_dst);
        imshow(winname, abs_dst);
        char c = (char)waitKey(0);
        if (c == 113) {
            destroyAllWindows();
            break;
        }
        else if (c == 107) {
            ksize = ksize < 30 ? ksize + 2 : -1;
        }
        else if (c == 115) {
            scale++;
        }
        else if (c == 114) {
            scale = 1;
            ksize = 3;
        }
        cout << "ksize: " << ksize << " scale: " << scale << "\n";
    }
    return 0;
}