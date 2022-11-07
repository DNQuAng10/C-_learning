#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

bool use_mask;
Mat img; Mat templ; Mat mask; Mat result;
const char* src_win = "Src image";
const char* res_win = "Result image";

int match_method;
int max_tbar = 5;

void matching_method(int, void*) {
    Mat display_img;
    img.copyTo(display_img);

    int result_cols = img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;

    result.create(result_rows, result_cols, CV_32FC1);

    bool method_accepts_mask = (TM_SQDIFF == match_method || match_method == TM_CCORR_NORMED);
    if (use_mask && method_accepts_mask) {
        matchTemplate(img, templ, result, match_method, mask);
    }
    else {
        matchTemplate(img, templ, result, match_method);
    }
    normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
    double min_val, max_val; Point min_loc, max_loc;
    Point match_loc;

    minMaxLoc(result, &min_val, &max_val, &min_loc, &max_loc, Mat());
    if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED) {
        match_loc = min_loc;
    }
    else {
        match_loc = max_loc;
    }

    rectangle(
        display_img, 
        match_loc, 
        Point(match_loc.x + templ.cols, match_loc.y + templ.rows), 
        Scalar(0, 255, 0), 2, 8, 0);
    rectangle(
        result, match_loc, 
        Point(match_loc.x + templ.cols, match_loc.y + templ.rows), 
        Scalar(0, 255, 0), 2, 8, 0);
    
    imshow(src_win, display_img);
    imshow(res_win, result);
    return ;
}

int main(int argc, char** argv) {
    const char* default_img_path = "../test_img/car_1.jpg";
    const char* img_path = argc >= 3 ? argv[1] : default_img_path;
    const char* default_templ_path = "../test_img/temple_car.jpg";
    const char* templ_path = argc >= 3 ? argv [2] : default_templ_path;

    img = imread(samples::findFile(img_path));
    templ = imread(samples::findFile(templ_path));
    if (img.empty() || templ.empty()) {
        cout << "Error opening image: " << img_path << " OR " << templ_path << "\n";
        return EXIT_FAILURE;
    }

    namedWindow(src_win, WINDOW_AUTOSIZE);
    namedWindow(res_win, WINDOW_AUTOSIZE);

    const char* tbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF_NORMED \n 2: TM_CCORR \n 3: TM_CCORR_NORMED \n 4: TM_COEFF \n 5: TM_COEFF_NORMED";
    createTrackbar(tbar_label, src_win, &match_method, max_tbar, matching_method);
    matching_method(0, 0);

    waitKey(0);
    return 0;
}