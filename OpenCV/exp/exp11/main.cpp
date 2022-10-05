#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

int main(int argc, char ** argv) {
    CommandLineParser parser(argc, argv, "{@input | /home/dnq/Downloads/ds_triton_yolov5_trt_out.mp4 | video_path}");

    String input = samples::findFile(parser.get<String>("@input"));
    cout << "Input: " << input << "\n";
    VideoCapture cap(input);
    if (!cap.isOpened()) {
        cout << "Error opening video\n";
        return -1;
    }

    Mat frame, gray_frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            cout << "Cann't read frame.\n" << endl;
            break;
        }
        cvtColor(frame, gray_frame, COLOR_BGR2GRAY);
        imshow("video:", gray_frame);
        char key = (char)waitKey(30);
        if (key == 113) break;
    }
    cap.release();
    destroyAllWindows();
    return 0;
}