#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

Mat src, dst;
int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;
int const max_operator = 4;
int const max_elem = 2;
int const max_kernel_size = 21;

const char* window_name = "Morphology Transformations Demo";
void Morphology_oper(int, void*);
int main(int argc, char** argv) {
    CommandLineParser parser(argc, argv, "{@input | /home/dnq/Downloads/car_1.jpg | input image}");
    src = imread(samples::findFile(parser.get<String>("@input")), IMREAD_COLOR);
    if (src.empty()) {
        cout << "Could not open or find the input image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return EXIT_FAILURE;
    }

    namedWindow(window_name, WINDOW_AUTOSIZE);
    createTrackbar(
        "Operator:\n 0: Opening - 1: Closing \n 2: Gradient - 3: TopHat \n 4: BlackHat", 
        window_name, &morph_elem, max_elem, Morphology_oper);
    createTrackbar("Kernel size:\n 2n + 1", window_name, &morph_size, max_kernel_size, Morphology_oper);

    Morphology_oper(0, 0);
    waitKey(0);
    return 0;
} 

void Morphology_oper(int, void*) {
    int oper = morph_operator + 2;
    Mat element = getStructuringElement(
        morph_elem, 
        Size(2 * morph_size + 1, 2 * morph_size + 1), 
        Point(morph_size, morph_size));
    
    morphologyEx(src, dst, oper, element);
    imshow(window_name, dst);
}
