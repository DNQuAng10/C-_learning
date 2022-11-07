#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    const char* default_img_path = "../test_img/la_bai_1.jpeg";
    const char* img_path = argc >= 2 ? argv[1] : default_img_path;
    Mat src = imread(samples::findFile(img_path));
    if (src.empty()) {
        cout << "Error opening image: " << img_path << "\n";
        return EXIT_FAILURE;
    }

    imshow("0-Src: ", src);

    // change the background from white to black, 
    // since that will help later to extract
    // better results during the use of Distance Transform
    Mat mask;
    inRange(src, Scalar(255, 255, 255), Scalar(255, 255, 255), mask);
    src.setTo(Scalar(0, 0, 0), mask);

    imshow("1-Black Background Image: ", src);

    // Create a kernel that we will use to sharpen our image
    // an approximation of second derivative a quite strong kernel
    Mat kernel = (Mat_<float>(3, 3) <<  1, 1, 1,
                                        1, -8, 1, 
                                        1, 1, 1); 
    // do the laplacian filtering as it is
    // well, we need to convert everything in something more deeper then CV_8U
    // because the kernel has some negative values,
    // and we can expect in general to have a Laplacian image with negative values
    // BUT a 8bits unsigned int (the one we are working with) can contain values from 0 to 255
    // so the possible negative number will be truncated
    Mat laplace_img;
    filter2D(src, laplace_img, CV_32F, kernel);
    Mat sharp;
    src.convertTo(sharp, CV_32F);
    Mat res_img = sharp - laplace_img;

    // convert back to 8bits gray scale
    res_img.convertTo(res_img, CV_8UC3);
    laplace_img.convertTo(laplace_img, CV_8UC3);
    imshow("2-New Sharped Image: ", res_img);

    // Create binary image from source image
    Mat bw;
    cvtColor(res_img, bw, COLOR_BGR2GRAY);
    threshold(bw, bw, 40, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("3-Binary Image: ", bw);

    // Perform the distance transform algorithm
    Mat dist;
    distanceTransform(bw, dist, DIST_L2, 3);

    // Normalize the distance image for range = {0.0, 1.0}
    // so we can visualize and threshold it
    normalize(dist, dist, 0, 1.0, NORM_MINMAX);
    imshow("4-Distance Transform Image: ", dist);

    // Threshold to obtain the peaks
    // This will be the markers for the foreground objects
    threshold(dist, dist, 0.4, 1.0, THRESH_BINARY);

    // Dilate a bit the dist image
    Mat kernel1 = Mat::ones(3, 3, CV_8U);
    dilate(dist, dist, kernel1);
    imshow("5-Peaks: ", dist);

    // Create the CV_8U version of the distance image
    // It is needed for findContours()
    Mat dist_8u;
    dist.convertTo(dist_8u, CV_8U);

    // Find total markers
    vector<vector< Point>> contours;
    findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Create the marker image for the watershed algorithm
    Mat markers = Mat::zeros(dist.size(), CV_32S);
    for (size_t i=0; i < contours.size(); i++) {
        drawContours(markers, contours, static_cast<int>(i), Scalar(static_cast<int>(i) + 1), -1);
    }

    circle(markers, Point(5, 5), 3, Scalar(255), -1);
    Mat marker8u;
    markers.convertTo(marker8u, CV_8U, 10);
    imshow("6-Markers: ", marker8u);
    // Perform the watershed algorithm
    watershed(res_img, markers);

    Mat mark;
    markers.convertTo(mark, CV_8U);
    bitwise_not(mark, mark);
    imshow("7-Marker_v2: ", mark);

    vector<Vec3b> colors;
    for (size_t i=0; i < contours.size(); i++) {
        int b = theRNG().uniform(0, 256);
        int g = theRNG().uniform(0, 256);
        int r = theRNG().uniform(0, 256);
        colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
    }

    Mat dst = Mat::zeros(markers.size(), CV_8UC3);
    //Fill labeled objects with random colors
    for (int i=0; i < markers.rows; i++) {
        for (int j=0; j < markers.cols; j++) {

            int index = markers.at<int>(i, j);
            if (index > 0 && index <= static_cast<int>(contours.size())) {
                dst.at<Vec3b>(i, j) = colors[index - 1];
            }
        }
    }
    imshow("8-Final result: ", dst);
    waitKey(0);
    return 0;
}