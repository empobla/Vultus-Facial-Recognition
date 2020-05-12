#define CVUI_IMPLEMENTATION

# define WINDOW2_NAME "Window 2"
#include "Screens.h"

Screens::Screens() {

}

void CaptureFrame(int i, cv::Mat frame){
    char filename[80];
    sprintf(filename,"/root/workspace/GraphicInterface/test_%d.png",i);
    imwrite(filename, frame);
    i++;
}

void Screens::FaceVerificationWindow() {
    cvui::init(WINDOW2_NAME);
    cv::Mat frame = cv::Mat(cv::Size(1280, 720), CV_8UC3);
    int count = 0;
    int i;
    while (true) {
        i = 0;

        cv::VideoCapture cap;
        cap = cv::VideoCapture(0);
        cap.open(0);
        cvui::text(frame, 10, 10, "FaceVerification");

        if (!cap.isOpened()){
            printf("--(!)Error opening video capture\n");
        }

        while (1){
            cap.read(frame);

            // Show a button at position (110, 80)
            if (cvui::button(frame, 500, 80, "Face verification")) {
                // The button was clicked, so let's increment our counter.
                CaptureFrame(i, frame);
            }
            if (cvui::button(frame, 500, 160, "Face identification")) {
                // The button was clicked, so let's increment our counter.
                CaptureFrame(i, frame);
            }
            if (cvui::button(frame, 500, 240, "Enroll a student")) {
                // The button was clicked, so let's increment our counter.
            }
            
            cv::imshow(WINDOW2_NAME, frame);
            if (cv::waitKey(20) == 27) {
                break;
            }
        }

        if (cv::waitKey(20) == 27) {
            break;
        }
    }
}