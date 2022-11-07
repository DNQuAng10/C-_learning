#include <iostream>
#include <iomanip>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

Mat src, gray;
int thresh = 100;
const int max_thresh = 255;
const char* winname = "Moment";
RNG rng(12345);

void thresh_callback(int, void*) {
    if (thresh >= 100) {
        Mat canny_out;
        Canny(gray, canny_out, thresh, thresh*2, 3);
        vector<vector<Point>> contours;
        findContours(canny_out, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

        vector<Moments> mu(contours.size());
        for (size_t i=0; i < contours.size(); i++) {
            mu[i] = moments(contours[i]);
        }

        vector<Point2f> mc(contours.size());
        for(size_t i=0; i < contours.size(); i++) {
            //add 1e-5 to avoid division by zero
            mc[i] = Point2f(static_cast<float>(mu[i].m10 / (mu[i].m00 + 1e-5)), 
                            static_cast<float>(mu[i].m01 / (mu[i].m00 + 1e-5)));
            cout << "mc[" << i << "]=" << mc[i] << "\n";
        }

        Mat draw = Mat::zeros(canny_out.size(), CV_8UC3);
        for(size_t i=0; i < contours.size(); i++) {
            Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
            drawContours(draw, contours, (int)i, color, 2);
            circle(draw, mc[i], 4, color, -1);
        }
        
        imshow(winname, draw);
        cout << "\t Info: Area and Contour Length \n";
        for (size_t i=0; i < contours.size(); i++) {
            cout << " * Contour[" << i << "] - Area (M_00) = " << fixed << std::setprecision(2) << mu[i].m00 
                << " - Area OpenCV: " << contourArea(contours[i]) << " - Length: " << arcLength(contours[i], true) << "\n"; 
        }
    }
    else {
        imshow(winname, src);
    }
}

int main(int argc, char** argv) {
    const char* default_img_path = "../test_img/draw.jpg";
    const char* img_path = argc >= 2 ? argv[1] : default_img_path;
    src = imread(samples::findFile(img_path));
    if (src.empty()) {
        cout << "Error opening image: " << img_path << "\n";
        return EXIT_FAILURE;
    }

    cvtColor(src, gray, COLOR_BGR2GRAY);
    blur(gray, gray, Size(3, 3));
    namedWindow(winname, WINDOW_AUTOSIZE);
    
    createTrackbar("Canny thresh: ", winname, &thresh, max_thresh, thresh_callback);
    thresh_callback(0, 0);
    waitKey();
    return 0;
}