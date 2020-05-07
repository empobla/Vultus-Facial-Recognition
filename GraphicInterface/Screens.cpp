
#include <opencv2/opencv.hpp>
   #define CVUI_IMPLEMENTATION
   #include "cvui.h"
   #define WINDOW2_NAME "Window 2"
   #include "Screens.h"
   #include <opencv2/videoio.hpp>


    Screens :: Screens(){


    }

    void Screens :: FaceVerificationWindow(){
        cvui::init(WINDOW2_NAME);
        cv::Mat frame = cv::Mat(cv::Size(1280, 720), CV_8UC3);
        int count = 0;   
        while(true) {
        cv::VideoCapture cap;
        cap = cv::VideoCapture(0);
        frame = cv::Scalar(100, 100, 100);
        cvui::text(frame, 10, 10, "FaceVerification");
        // Show a button at position (110, 80)
            if (cvui::button(frame, 500, 80, "Face verification")) {
            // The button was clicked, so let's increment our counter.
            
            }
            if (cvui::button(frame, 500, 160, "Face identification")) {
            // The button was clicked, so let's increment our counter.
            
            }
            if (cvui::button(frame, 500, 240, "Enroll a student")) {
            // The button was clicked, so let's increment our counter.
            
            }
        cvui::imshow(WINDOW2_NAME, frame);
        if (cv::waitKey(20) == 27) {
            break;
        }
        }
  }