#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>

using namespace cv;
using namespace std;

const string keys = 
"{help  h           |            | Print this message}"
"{image1 i1         |../test_img/harry1.jpg            | Path to the input image1. Omit for detecting through VideoCapture}"
"{image2 i2         |../test_img/harry5.jpg            | Path to the input image2. When image1 and image2 parameters given then the program try to find a face on both images and runs face recognition algorithm}"
"{video v           | 0          | Path to the input video}"
"{scale sc          | 1.0        | Scale factor used to resize input video frames}"
"{fd_model fd       | ./models/face_detection_yunet_2022mar.onnx| Path to the model. Download yunet.onnx in https://github.com/opencv/opencv_zoo/tree/master/models/face_detection_yunet}"
"{fr_model fr       | ./models/face_recognition_sface_2021dec.onnx | Path to the face recognition model. Download the model at https://github.com/opencv/opencv_zoo/tree/master/models/face_recognition_sface}"
"{score_threshold   | 0.9        | Filter out faces of score < score_threshold}"
"{nms_threshold     | 0.3        | Suppress bounding boxes of iou >= nms_threshold}"
"{top_k             | 5000       | Keep top_k bounding boxes before NMS}"
"{save s            | false      | Set true to save results. This flag is invalid when using camera}";


static
void visualize (Mat& input, int frame, Mat& faces, double fps, int thickness=2) {
    string fps_string = format("FPS: %.2f", (float)fps);
    if (frame >= 0) {
        cout << "Frame " << frame << ", ";
    }
    cout << "FPS: " << fps_string << endl;
    for (int i=0; i < faces.rows; i++) {
        cout << "Face " << i 
             << ", top-left coordinate: (" << faces.at<float>(i, 0) << ", " << faces.at<float>(i, 1) << "), "
             << "score: " << format("%.2f", faces.at<float>(i, 14))
             << endl;

        rectangle(input, Rect2i(int(faces.at<float>(i, 0)), int(faces.at<float>(i, 1)), int(faces.at<float>(i, 2)), int(faces.at<float>(i, 3))), Scalar(0, 255, 0), thickness);
        circle(input, Point2i(int(faces.at<float>(i, 4)), int(faces.at<float>(i, 5))), 2, Scalar(255, 0, 0), thickness);
        circle(input, Point2i(int(faces.at<float>(i, 6)), int(faces.at<float>(i, 7))), 2, Scalar(0, 0, 255), thickness);
        circle(input, Point2i(int(faces.at<float>(i, 8)), int(faces.at<float>(i, 9))), 2, Scalar(0, 255, 0), thickness);
        circle(input, Point2i(int(faces.at<float>(i, 10)), int(faces.at<float>(i, 11))), 2, Scalar(255, 0, 255), thickness);
        circle(input, Point2i(int(faces.at<float>(i, 12)), int(faces.at<float>(i, 13))), 2, Scalar(0, 255, 255), thickness);
    }
    putText(input, fps_string, Point(0, 15), FONT_ITALIC, 0.5, Scalar(0, 255, 0), 2);
}


int main(int argc, char** argv) {
    CommandLineParser parser(argc, argv, keys);
    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }

    String face_detect_model_path = parser.get<String>("fd_model");
    String face_recognition_model_path = parser.get<String>("fr_model");
    float score_thresh = parser.get<float>("score_threshold");
    float nms_thresh = parser.get<float>("nms_threshold");
    int top_k = parser.get<int>("top_k");

    bool save = parser.get<bool>("save");
    float scale = parser.get<float>("scale");

    double cosine_similar_thresh = 0.363;
    double l2_norm_similar_thresh = 1.128;

    // initialize face detection 
    Ptr<FaceDetectorYN>detector = FaceDetectorYN::create(
        face_detect_model_path, "", Size(320, 320), 
        score_thresh, nms_thresh, top_k);
    TickMeter tm;

    // Image Input
    if (parser.has("image1")) {
        String input1 = parser.get<String>("image1");
        Mat img1 = imread(samples::findFile(input1));
        if (img1.empty()) {
            cerr << "Error opening image 1 " << input1 << "\n";
            return 2;
        }
        int img_widht = int(img1.cols * scale);
        int img_height = int(img1.rows * scale);
        resize(img1, img1, Size(img_widht, img_height));
        tm.start();

        // Set input size before inference
        detector->setInputSize(img1.size());

        Mat faces1;
        detector->detect(img1, faces1);
        if (faces1.rows < 1) {
            cerr << "Cannot find a face in " << input1 << endl;
            return 1;
        }
        tm.stop();

        // Draw result on input image
        visualize(img1, -1, faces1, tm.getFPS());

        if (save) {
            cout << "Saving result.jpg...\n";
            imwrite("face_detect_result.jpg", img1);
        }

        imshow("image 1: ", img1);
        pollKey(); // handle UI events to show content;

        if (parser.has("image2")) {
            String input2 = parser.get<String>("image2");
            Mat img2 = imread(samples::findFile(input2));
            if (img2.empty()) {
                cerr << "Error opening image2: " << input2 << endl;
                return 2;
            }
            tm.reset();
            tm.start();
            detector->setInputSize(img2.size());

            Mat faces2;
            detector->detect(img2, faces2);
            if (faces2.rows < 1) {
                cerr << "Cannot find a face in " << input2 << endl;
                return 1;
            }
            tm.stop();
            visualize(img2, -1, faces2, tm.getFPS());
            if (save) {
                cout << "Saving face detection image 2..\n";
                imwrite("result2.jpg", img2);
            }
            imshow("image2", img2);
            pollKey();

            // initialize FaceRecognizerSF
            Ptr<FaceRecognizerSF> face_recognizer = FaceRecognizerSF::create(face_recognition_model_path, "");

            // aligning and cropping facial image through the first face of faces detected
            Mat aligned_face1, aligned_face2;
            face_recognizer->alignCrop(img1, faces1.row(0), aligned_face1);
            face_recognizer->alignCrop(img2, faces2.row(0), aligned_face2);

            // run feature extraction with given aligned_face
            Mat feature1, feature2;
            face_recognizer->feature(aligned_face1, feature1);
            feature1 = feature1.clone();
            face_recognizer->feature(aligned_face2, feature2);
            feature2 = feature2.clone();

            double cos_score = face_recognizer-> match(feature1, feature2, FaceRecognizerSF::DisType::FR_COSINE);
            double L2_score = face_recognizer->match(feature1, feature2, FaceRecognizerSF::DisType::FR_NORM_L2);

            if (cos_score >= cosine_similar_thresh) {
                cout << "Same identity\n";
            }
            else {
                cout << "Different identities\n";
            }
            cout << "Cosine similarity: " << cos_score << ", threshold: " << cosine_similar_thresh << ". (higher value means higher similarity, max 1.0)\n";

            if (L2_score <= l2_norm_similar_thresh) {
                cout << "Same identity\n";
            }
            else {
                cout << "Different identities\n";
            }
            cout << "NormL2 distance: " << L2_score << ", threshold: " << l2_norm_similar_thresh << ". (lower value means higher similarity, min 0.0)\n";
        }
        cout << "Press any key to exit ..." << endl;
        waitKey(0);
    }
    else {
        cout << "Video Process is developing...\n";
        cout << "Coming Soon.......\n";
    }
    cout << "Done..." << endl;
    return 0;
}