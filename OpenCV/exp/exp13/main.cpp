#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

Mat src, dst;
int top, bottom, l, r;
int border_type = BORDER_CONSTANT;
const char* winname = "Padding";
RNG rng(12345);
Scalar value = Scalar(120, 78, 26);


int main(int argc, char** argv) {
    const char* img_path = argc >=2 ? argv[1] : "/home/dnq/Downloads/car_1.jpg";
    src = imread(samples::findFile(img_path), IMREAD_COLOR);

    if (src.empty()) {
        cout << "Cann't read image: " << img_path << "\n";
        return -1;
    }

    cout << "Padding: \n";
    cout << "Press 'c': random constant value\n";
    cout << "Press 'r': replicated\n";
    cout << "Press 'q': quit\n";

    namedWindow(winname, WINDOW_AUTOSIZE);
    top = (int) (0.05 * src.rows); 
    bottom = top;
    l = (int)(0.05 * src.cols); r = l;

    for (;;) {
        copyMakeBorder(src, dst, top, bottom, l, r, border_type, value);
        imshow(winname, dst);
        int c1 = (int)waitKey(0);
        if (c1 == 113) break;
        else if (c1 == 99) {
            cout << c1 << "\n";
            value = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
            border_type = BORDER_CONSTANT;
        }
        else if (c1 == 114) {
            border_type = BORDER_REPLICATE;
        }
    }
    return 0;
}

