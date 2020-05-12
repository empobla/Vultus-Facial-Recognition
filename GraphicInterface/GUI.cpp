#include "Screens.h"

#define WINDOW1_NAME "Window 1"

using namespace std;

int main() {
    Screens * wOpener = new Screens();

    cvui::init(WINDOW1_NAME);
    cv::Mat frame = cv::Mat(cv::Size(1280, 720), CV_8UC3);
    int count = 0;
    while (true) {
        frame = cv::Scalar(100, 100, 100);
        cvui::text(frame, 10, 10, "VULTUS software");
        // Show a button at position (110, 80)
        if (cvui::button(frame, 500, 80, "Face verification")) { // To manually verify an unauthorized access
            //wFaceVerification.OpenWindow();
            count++;
            cout << count << endl;
            wOpener -> FaceVerificationWindow();
            // The button was clicked, so let's increment our counter.

        }
        if (cvui::button(frame, 500, 160, "Face identification")) { // Detects the 10 closest matches to the faces database
            // The button was clicked, so let's increment our counter.

        }
        if (cvui::button(frame, 500, 240, "Enroll a student")) { // To feed the database with new values
            // The button was clicked, so let's increment our counter.

        }
        cvui::imshow(WINDOW1_NAME, frame);
        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;

}