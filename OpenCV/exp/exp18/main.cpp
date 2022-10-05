#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    const char* default_img = "/home/dnq/Downloads/ball_1.jpg";
    const char* img_path = argc >=2 ? argv[1] : default_img;

    Mat src = imread(samples::findFile(img_path));
    if (src.empty()) {
        cout << "Error opening image: " << img_path << "\n";
        return -1;
    }

    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    medianBlur(gray, gray, 5);

    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                gray.rows / 2, // change this value to detect circles with different distances to each other
                100, 30, 10, 100 // change the last two parameters (min-max radius) to detect larger circles
    );

    for (size_t i = 0; i < circles.size(); i++) {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        circle(src, center, 1, Scalar(0, 0, 255), 3, LINE_AA);
        int radius = c[2];
        circle(src, center, radius, Scalar(128, 78, 166), 3, LINE_AA);
    }
    imshow("detected circles: ", src);
    waitKey(0);
    return EXIT_SUCCESS;
}