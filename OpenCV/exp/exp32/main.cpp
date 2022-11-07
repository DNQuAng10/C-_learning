#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(void) {
    const int r = 100;
    Mat src = Mat::zeros(Size(4*r, 4*r), CV_8U);

    vector<Point2f> vert(6);
    vert[0] = Point(3*r/2, static_cast<int>(1.34*r));
    vert[1] = Point(1*r, 2*r);
    vert[2] = Point(3*r/2, static_cast<int>(2.866*r));
    vert[3] = Point(5*r/2, static_cast<int>(2.866*r));
    vert[4] = Point(3*r, 2*r);
    vert[5] = Point(5*r/2, static_cast<int>(1.34*r));

    for(int i=0; i < 6; i++) {
        line(src, vert[i], vert[(i + 1) % 6], Scalar(255), 3);
    }

    vector<vector<Point>> contours;
    findContours(src, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

    Mat raw_dist(src.size(), CV_32F);
    for(int i=0; i < src.rows; i++) {
        for (int j=0; j < src.cols; j++) {
            raw_dist.at<float>(i, j) = (float)pointPolygonTest(contours[0], Point2f((float)j, (float)j), true);
        }
    }

    double min_val, max_val;
    Point maxDistPt; //inscribed circle center
    minMaxLoc(raw_dist, &min_val, &max_val, NULL, &maxDistPt);
    min_val = abs(min_val);
    max_val = abs(max_val);

    Mat draw = Mat::zeros(src.size(), CV_8UC3);
    for (int i=0; i < src.rows; i++) {
        for(int j=0; j < src.cols; j++) {
            if (raw_dist.at<float>(i, j) < 0) {
                draw.at<Vec3b>(i, j)[0] = (char)(255 - abs(raw_dist.at<float>(i, j)) * 255 / min_val);
            }
            else if (raw_dist.at<float>(i, j) > 0) {
                draw.at<Vec3b>(i, j)[2] = (char)(255 - raw_dist.at<float>(i, j) * 255 / max_val);
            }
            else {
                draw.at<Vec3b>(i, j)[0] = 255;
                draw.at<Vec3b>(i, j)[1] = 255;
                draw.at<Vec3b>(i, j)[2] = 255;
            }
        }
    }
    circle(draw, maxDistPt, (int)max_val, Scalar(255, 255, 255));

    imshow("Source: ", src);
    imshow("Distance and inscribed circle: ", draw);
    waitKey();
    return 0;
}