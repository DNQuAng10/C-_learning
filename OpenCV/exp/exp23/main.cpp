#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    CommandLineParser parser(argc, argv, "{@input | ../test_img/car_1.jpg | input image}");
    String img_path = parser.get<String>("@input");
    Mat src = imread(samples::findFile(img_path));
    if (src.empty()) {
        cout << "Error opening image: " << img_path << "\n";
        return EXIT_FAILURE;
    }
    cvtColor(src, src, COLOR_BGR2GRAY);

    Mat equal_dst;
    equalizeHist(src, equal_dst);

    // Mat resconstruct_dst;
    // cvtColor(equal_dst, resconstruct_dst, COLOR_GRAY2BGR);

    imshow("Src: ", src);
    imshow("Equalized: ", equal_dst);
    // imshow("Resconstruct: ", resconstruct_dst);
    waitKey(0);
    return 0;
}