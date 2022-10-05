#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    CommandLineParser parser(argc, argv,    "{@input | /home/dnq/Downloads/car_1.jpg | input image}"
                                            "{ksize k| 1 |ksize (hit 'k' to increase value))}"
                                            "{scale s| 1 |scale (hit 's' to increase value)}"
                                            "{delta d| 0 |delta (hit 'd' to increase value)}"
                                            "{help h| false | show help message}");
    cout << "Uses Sobel or Scharr for edge detection\n";
    parser.printMessage();
    cout << "\nPress 'q' to exit. \nPress 'r' to reset values (ksize will be -1 equal to Scharr function)";

    Mat img, src, gray;
    Mat grad;
    const String winname = "Sobel - Edge Detector\n";
    int ksize = parser.get<int>("ksize");
    int scale = parser.get<int>("scale");
    int delta = parser.get<int>("delta");
    int depth = CV_16S;

    String img_path = parser.get<String>("@input");
    img = imread(samples::findFile(img_path));
    if (img.empty()) {
        printf("Cann't read image: %s\n", img_path.c_str());
        return EXIT_FAILURE;
    }
    for (;;) {
        // Remove noise by blurring with a Gaussian filter (3x3)
        GaussianBlur(img, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

        cvtColor(src, gray, COLOR_BGR2GRAY);

        Mat grad_x, grad_y;
        Mat abs_grad_x, abs_grad_y;

        Sobel(gray, grad_x, depth, 1, 0, ksize, scale, delta, BORDER_DEFAULT);
        Sobel(gray, grad_y, depth, 0, 1, ksize, scale, delta, BORDER_DEFAULT);

        // converting back to CV_8U
        convertScaleAbs(grad_x, abs_grad_x);
        convertScaleAbs(grad_y, abs_grad_y);

        addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
        imshow(winname, grad);
        int c = (int)waitKey(0);
        if (c == 113) break;
        else if (c == 107) {
            ksize = ksize < 30 ? ksize + 2 : -1;
        }
        else if (c == 115) {
            scale ++;
        }
        else if (c == 100) {
            delta++;
        }
        else if (c == 114) {
            scale = 1;
            ksize = -1;
            delta = 0;
        }
        // cout << c << "\n";
        cout << "ksize: " << ksize << " scale: " << scale << " delta: " << delta << "\n";
    }
    return EXIT_SUCCESS;
}