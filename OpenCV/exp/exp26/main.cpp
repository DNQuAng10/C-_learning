#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

Mat src, hue, hsv;
Mat backproject;
int min = 25;
int bins = 25;
const char* winname = "Source image";    

void hist_and_backproject(int, void*) {
    int hist_size = MAX(bins, 2);
    float hue_range[] = {0, 180};
    const float* ranges[] = {hue_range};

    Mat hist;
    calcHist(&hue, 1, 0, Mat(), hist, 1, &hist_size, ranges, true, false);
    normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

    
    calcBackProject(&hue, 1, 0, hist, backproject, ranges, 1, true);
    
    if (bins <= 25 && bins >= 10) {
        imshow(winname, src);
    }
    else if (bins < 10) {
        imshow(winname, hsv);
    }
    else {
        imshow(winname, backproject);
    }

    int w = 400, h = 400;
    int bin_w = cvRound((double) w / hist_size);
    Mat hist_img = Mat::zeros(h, w, CV_8UC3);

    for (int i=0; i < bins; i++) {
        rectangle(
            hist_img, 
            Point(i * bin_w, h), 
            Point((i + 1) * bin_w, h - cvRound(hist.at<float>(i) * h / 255.)), 
            Scalar(0, 0, 255), FILLED);
    }
    imshow("Histogram: ", hist_img);
}

int main(int argc, char** argv) {
    const char* default_img = "../test_img/car_1.jpg";
    const char* img_path = argc >= 2 ? argv[1] : default_img;

    src = imread(samples::findFile(img_path));
    if (src.empty()) {
        cout << "Error opening image: " << img_path << "\n";
        return EXIT_FAILURE;
    }

    
    cvtColor(src, hsv, COLOR_BGR2HSV);

    hue.create(hsv.size(), hsv.depth());
    int ch[] = {0, 0};
    mixChannels(&hsv, 1, &hue, 1, ch, 1);

    // const char* winname = "Source image";
    // imshow("src", src);
    // imshow("HSV", hsv);
    namedWindow(winname);
    createTrackbar("* Hue bins: ", winname, &bins, 180, hist_and_backproject);
    hist_and_backproject(0, 0);

    imshow(winname, src);
    waitKey(0);
    return 0;
}