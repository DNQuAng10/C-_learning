#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    CommandLineParser parser(argc, argv, "{@input | ../test_img/car_1.jpg | image path}");
    String img_path = parser.get<string>("@input");

    Mat src = imread(samples::findFile(img_path));
    if (src.empty()) {
        cout << "Error opening image: " << img_path << "\n";
        return EXIT_FAILURE;
    }

    Point2f srcTri[3];
    srcTri[0] = Point2f(0.f, 0.f);
    srcTri[1] = Point2f(src.cols - 1.f, 0.f);
    srcTri[2] = Point2f(0.f, src.rows - 1.f);

    Point2f dstTri[3];
    dstTri[0] = Point2f(0.f, src.rows * 0.33f);
    dstTri[1] = Point2f(src.cols * 0.85f, src.rows * 0.25f);
    dstTri[2] = Point2f(src.cols * 0.15f, src.rows * 0.7f);

    Mat warp_mat = getAffineTransform(srcTri, dstTri);
    Mat warp_dst = Mat::zeros(src.rows, src.cols, src.type());

    warpAffine(src, warp_dst, warp_mat, warp_dst.size());
    putText(warp_dst, "Affine Transform: srcTri ==> dstTri", Point (50, 50), FONT_ITALIC, 2, Scalar(0, 0, 255), 2);
    
    imshow("Src image: ", src);
    imshow("Warp Affine: ", warp_dst);
    waitKey(0);
    
    int angle = 0;
    double scale = 0.7;
    for (;;) {
        cout << "angle: " << angle << "\n";
        Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
        
        Mat rot_mat = getRotationMatrix2D(center, angle, scale);
        Mat warp_rotate_dst;
        warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());
        putText(warp_rotate_dst, to_string(angle), Point(100, 100), FONT_ITALIC, 2, Scalar(0, 255, 9), 2);
    
        imshow("Warp Rotate Affined: ", warp_rotate_dst);
        int c = (int)waitKey(1000);
        if (c == 113) {
            destroyAllWindows();
            break;
        }
        angle = angle + 10;
        angle = angle % 180;
    }

    return 0;
}

