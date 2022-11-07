#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

static Scalar random_color(RNG& rng) {
    int icolor = (unsigned) rng;
    return Scalar(icolor&255, (icolor>>8)&255, (icolor>>16)&255);
}

// int draw_random_rectangles(Mat img, char* winname, RNG rng) {
    
// }

int main(int argc, char** argv) {
    const char* default_img = "/home/dnq/Downloads/car_1.jpg";
    const char* img_path = argc > 2 ? argv[1] : default_img;

    Mat src = imread(samples::findFile(img_path));
    if (src.empty()) {
        cout << "Error opening image: " << img_path << "\n";
        return EXIT_FAILURE;
    }

    int height = src.cols;
    int width = src.rows;

    cout << height << width << "\n";

    int x_min = -width / 2;
    int x_max = width * 3 / 2;
    int y_min = -width / 2;
    int y_max = width * 3 / 2;

    RNG rng(0xFFFFFFFF);
    const String winname = "Draw Rectangle";
    Mat dst = src.clone();
    int num = 0;
    for (;;) {
        Point pt1, pt2, center;
        int lineType = 8;
        imshow(winname, dst);
        int c = (int)waitKey(0);
        // Press 'a'
        if (c == 97) {
            int thickness = rng.uniform(-3, 10);
            pt1.x = rng.uniform(x_min, x_max);
            pt1.y = rng.uniform(y_min, y_max);
            pt2.x = rng.uniform(x_min, x_max);
            pt2.y = rng.uniform(y_min, y_max);
            
            if (num % 2 == 0) {
                rectangle(dst, pt1, pt2, random_color(rng), MAX(thickness, -1), lineType);
            }
            else if (num % 2 == 1) {
                int thickness = rng.uniform(1, 4);

                center.x = rng.uniform(10, width);
                center.y = rng.uniform(10, height);
                int r = rng.uniform(0, width / 2);
                circle(dst, pt1, r, random_color(rng), MAX(thickness, 1), lineType);
            }
            num ++;
        }
        // Press 'r'
        else if (c == 114) {
            dst = src.clone();
        }
        //Press 'q'
        else if (c == 113) {
            destroyAllWindows();
            break;
        }
        cout << c << "\n";

    }
    return 0;
}