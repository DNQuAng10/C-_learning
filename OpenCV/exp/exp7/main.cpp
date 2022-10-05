#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

void show_wait_destroy(const char* winname, cv::Mat img);

int main(int argc, char** argv) {
    CommandLineParser parser(argc, argv, "{@input | /home/dnq/Downloads/src.png | input image}");
    if (argc != 2) {
        cout << "Usage: Path to image\n";
    }

    Mat src = imread(samples::findFile(parser.get<String>("@input")), IMREAD_COLOR);
    if (src.empty()) {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <input image>" << endl;
    }

    imshow("src", src);

    // Transform source image to gray if it is not already
    Mat gray;
    if (src.channels() == 3) {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    } 
    else {
        gray = src;
    }
    show_wait_destroy("gray", gray);

    // Apply adaptiveThreshold at the bitwise_not of gray, notice the ~ symbol
    Mat bw;
    adaptiveThreshold(~gray, bw, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
    show_wait_destroy("binary", bw);

    // Create the images that will use to extract the horizontal and vertical lines
    Mat horizontal = bw.clone();
    Mat vertical = bw.clone();
    // Specify size on horizontal axis
    int horizontal_size = horizontal.cols / 30;
    // Create structure element fo extracting horizontal lines through morphology operations
    Mat horizontal_structure = getStructuringElement(MORPH_RECT, Size(horizontal_size, 1));

    // Apply morphology operations
    erode(horizontal, horizontal, horizontal_structure, Point(-1, -1));
    dilate(horizontal, horizontal, horizontal_structure, Point(-1, -1));

    // Show extracted horizontal lines
    show_wait_destroy("horizontal", horizontal);

    // Specify size on vertical axis 
    int vertical_size = vertical.rows / 30;
    // Create structure element for extracting vertical lines through morphology operations
    Mat vertical_structure = getStructuringElement(MORPH_RECT, Size(1, vertical_size));
    // Apply morphology operations
    erode(vertical, vertical, vertical_structure, Point(-1, -1));
    dilate(vertical, vertical, vertical_structure, Point(-1, -1));
    show_wait_destroy("vertical", vertical);
    // Inverse vertical image
    bitwise_not(vertical, vertical);
    show_wait_destroy("vertical_bit", vertical);

    // Extract edges and smooth image according to the logic
    // 1. extract edges
    // 2. dilate edges
    // 3. src.copyTo(smooth)
    // 4. blur smooth image
    // 5. smooth.copyTo(src, edges)

    // step 1.
    Mat edges;
    adaptiveThreshold(vertical, edges, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, -2);
    show_wait_destroy("edges", edges);
    // step 2.
    Mat kernel = Mat::ones(2, 2, CV_8UC1);
    dilate(edges, edges, kernel);
    show_wait_destroy("dilate", edges);
    // step 3.
    Mat smooth;
    vertical.copyTo(smooth);
    // step 4
    blur(smooth, smooth, Size(2, 2));
    // step
    smooth.copyTo(vertical, edges);
    // Show final result 
    show_wait_destroy("smooth - final", vertical);
    return 0;
}

void show_wait_destroy(const char* winname, cv::Mat img) {
    imshow(winname, img);
    moveWindow(winname, 500, 0);
    waitKey(0);
    destroyAllWindows();

}