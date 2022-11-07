#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <string.h>

using namespace cv;
using namespace std;

// Mat src;

void update_map(int &ind, Mat &map_x, Mat &map_y) {
    for (int i = 0; i < map_x.rows; i++) {
        for (int j = 0; j < map_x.cols; j++) {
            switch(ind) {
                case 0:
                    if (j > map_x.cols * 0.25 && j < map_x.cols * 0.75 && i > map_x.rows * 0.25 && i < map_x.rows * 0.75) {
                        map_x.at<float>(i, j) = 2 * (j - map_x.cols * 0.25f) + 0.5f;
                        map_y.at<float>(i, j) = 2 * (i - map_x.rows * 0.25f) + 0.5f;
                    }
                    else {
                        map_x.at<float>(i, j) = 0;
                        map_y.at<float>(i, j) = 0;
                    }
                    break;
                case 1:
                    map_x.at<float>(i, j) = (float)j;
                    map_y.at<float>(i, j) = (float)(map_x.rows - i);
                    break;
                case 2:
                    map_x.at<float>(i, j) = (float)(map_x.cols - j);
                    map_y.at<float>(i, j) = (float)i;
                    break;
                case 3:
                    map_x.at<float>(i, j) = (float)(map_x.cols - j);
                    map_y.at<float>(i, j) = (float)(map_x.rows - i);
                    break;
                default:
                    break;
            }
        }
    }
    ind = (ind + 1) % 4;
}

int main(int argc, char** argv) {
    CommandLineParser parser(argc, argv, "{@input | ../test_img/car_1.jpg | image path}");
    string img_path = parser.get<string>("@input");
    Mat src = imread(samples::findFile(img_path));
    if (src.empty()) {
        cout << "Error opening image: " << img_path << "\n";
        return EXIT_FAILURE;
    }
    Mat dst(src.size(), src.type());
    Mat map_x(src.size(), CV_32FC1);
    Mat map_y(src.size(), CV_32FC1);

    const char* winname = "Remapping";
    namedWindow(winname, WINDOW_AUTOSIZE);

    int ind = 0;
    for (;;) {
        update_map(ind, map_x, map_y);
        remap(src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
        putText(dst, to_string(ind), Point(50, 50), FONT_ITALIC, 2, Scalar(244, 255, 0), 2);

        imshow(winname, dst);
        int c = (int)waitKey(1000);
        if (c == 113) {
            destroyAllWindows();
            break;
        }
    }
    return 0;
}