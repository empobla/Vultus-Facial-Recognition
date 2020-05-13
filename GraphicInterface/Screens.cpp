#define CVUI_IMPLEMENTATION

# define WINDOW2_NAME "Window 2"
# define WINDOW3_NAME "Window 3"
#include "Screens.h"

Screens::Screens() {

}

void CaptureFrame(cv::Mat frame){
    char filename[80];
    sprintf(filename,"/root/workspace/GraphicInterface/test_0.png");
    imwrite(filename, frame);
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
                CaptureFrame(frame);
            }
            if (cvui::button(frame, 500, 160, "Face identification")) {
                // The button was clicked, so let's increment our counter.
                CaptureFrame(frame);
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

void Screens::FaceIdentificationWindow() {
    cvui::init(WINDOW3_NAME);
    cv::Mat frame = cv::Mat(cv::Size(1280, 720), CV_8UC3);
    int count = 0;
    int i;
    std::list<cv::Mat>::iterator it;

    while (true) {
        i = 0;

        cv::VideoCapture cap;
        cap = cv::VideoCapture(0);
        cap.open(0);
        cvui::text(frame, 10, 10, "FaceIdentification");

        if (!cap.isOpened()){
            printf("--(!)Error opening video capture\n");
        }

        while (1){
            cap.read(frame);
            // Show a button at position (110, 80)
            if (cvui::button(frame, 500, 80, "Calculate")) {
                // The button was clicked, so let's increment our counter.
                CaptureFrame(frame);
                cv::Mat screenshot = cv::imread("test_0.png", 1);
                FaceIdentificationMethod(screenshot);
            }
            
            cv::imshow(WINDOW3_NAME, frame);
            if (cv::waitKey(20) == 27) {
                break;
            }
        }

        if (cv::waitKey(20) == 27) {
            break;
        }
    }
}

//Metodos para probar GUI
void Screens::FaceIdentificationMethod(cv::Mat img){
    cv::Mat input1 = cv::imread("Test_images/img1.png", 1);
    cv::Mat input2 = cv::imread("Test_images/img2.png", 1);
    cv::Mat input3 = cv::imread("Test_images/img3.png", 1);
    cv::Mat input4 = cv::imread("Test_images/img4.jpg", 1);
    cv::Mat input5 = cv::imread("Test_images/img5.jpg", 1);
    AprovedStudentIdentification(0, input1, input2, input3, input4, input5);
}


void Screens::AprovedStudentIdentification(int aproved, cv::Mat dbImg1, cv::Mat dbImg2, cv::Mat dbImg3, cv::Mat dbImg4, cv::Mat dbImg5){
    cv::Mat acceptedFrame = cv::Mat(cv::Size(1280, 720), CV_8UC3);
    cv::Mat deniedFrame = cv::Mat(cv::Size(1280, 720), CV_8UC3);
        while(true){
            cv::Mat screenshot = cv::imread("test_0.png", 1);
            cv::Mat screenshot2 = cv::imread("Test_images/img1.png", 1);
            if (aproved==0){
                screenshot.copyTo(deniedFrame(cv::Rect(0, 0, 640, 480)));
                cvui::text(deniedFrame, 640, 700, "Not a match, please aprove manually");

                if (cvui::button(deniedFrame, 700, 160, "Accept")) { 
                    aproved=1;
                    std::cout<<"entre aqui"<<std::endl;
                    //cvui::text(acceptedFrame, 900, 700, "Go ahead!");
                }                
                cvui::update("Images");
            }
            if(aproved==1){
                
                screenshot.copyTo(acceptedFrame(cv::Rect(0, 0, 640, 480)));
                dbImg1.copyTo(acceptedFrame(cv::Rect(650, 0, 150, 150)));
                dbImg2.copyTo(acceptedFrame(cv::Rect(650, 150, 150, 150)));
                dbImg3.copyTo(acceptedFrame(cv::Rect(650, 300, 150, 150)));
                dbImg4.copyTo(acceptedFrame(cv::Rect(650, 450, 226, 226)));
                dbImg5.copyTo(acceptedFrame(cv::Rect(800, 0, 200, 200)));
                cvui::text(acceptedFrame, 640, 700, "Match, go ahead!");
            }
            if(aproved==0){
                cv::imshow("Images", deniedFrame);
            }
            else{
                cv::imshow("Images", acceptedFrame);
            }
            
            
            if (cv::waitKey(20) == 27) {
                break;
            }
        }
}
