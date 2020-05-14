/*
This is a demo application to showcase keyboard shortcuts. 
Author: Pascal Thomet
*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_ENROLL	"Enroll Student"
#define WINDOW_CONFIRM "Confirmed"
void confirmationFrame(std::string name, std::string age, std::string id, std::string image, int confirmation) {
     // Create a frame where components will be rendered to.
	cv::Mat frame_confirm = cv::Mat(550, 500, CV_8UC3);

	// Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
	cvui::init(WINDOW_CONFIRM);



	while (true) {
		// Fill the frame with a nice color
		frame_confirm = cv::Scalar(245, 176, 66);

        if(confirmation == 1){
            	// Render UI components to the frame
		    cvui::text(frame_confirm, 80, 80, "STUDENT SAVED");
		    cvui::text(frame_confirm, 80, 120, "Nombre");
            cvui::text(frame_confirm, 80, 180, "Edad");
            cvui::text(frame_confirm, 80, 240, "Matricula");
            cvui::text(frame_confirm, 80, 300, "Foto path");

		    cvui::text(frame_confirm, 80, 140, name);
            cvui::text(frame_confirm, 80, 200, age);
            cvui::text(frame_confirm, 80, 260, id);
            cvui::text(frame_confirm, 80, 320, image);
        }else{
            cvui::text(frame_confirm, 80, 80, "UNABLE TO SAVE STUDENT:(");

        }



        if (cvui::button(frame_confirm, 80, 400, "DONE")) {
                break;
            }
            


		// Update cvui stuff and show everything on the screen
		cvui::imshow(WINDOW_CONFIRM, frame_confirm);

		if (cv::waitKey(0) == 27) {
			break;
		}
	}
}

int main(int argc, const char *argv[])
{
	cv::Mat frame_enroll = cv::Mat(cv::Size(500, 400), CV_8UC3);

	// Init cvui and tell it to use a value of 20 for cv::waitKey()
	// because we want to enable keyboard shortcut for
	// all components, e.g. button with label "&Quit".
	// If cvui has a value for waitKey, it will call
	// waitKey() automatically for us within cvui::update().
	cvui::init(WINDOW_ENROLL, 20);
    cv::String name = "";
    cv::String id = "";
    cv::String age = "";
    cv::String img_path = "";
    int offset = 80;
	while (true) {
		frame_enroll = cv::Scalar(245, 176, 66);

        cvui::text(frame_enroll  , 40, offset+10, "ENROLL STUDENT", 1, 0xffffff);
		cvui::text(frame_enroll  , 40, offset+50, "Nombre", 0.5, 0xffffff);
        cvui::text(frame_enroll  , 40, offset+80, "Edad", 0.5, 0xffffff);
        cvui::text(frame_enroll  , 40, offset+120, "Matricula", 0.5, 0xffffff);
        cvui::text(frame_enroll  , 40, offset+160, "Foto path", 0.5, 0xffffff);
        
		cvui::input(frame_enroll , 140, offset+40, 100, "input1", name);
		cvui::input(frame_enroll , 140, offset+80, 100, "input2", id);
        cvui::input(frame_enroll , 140, offset+120, 50, "input3", age);
        cvui::input(frame_enroll , 140, offset+160, 200, "input4", img_path);

		// Exit the application if the quit button was pressed.
		// It can be pressed because of a mouse click or because 
		// the user pressed the "q" key on the keyboard, which is
		// marked as a shortcut in the button label ("&Quit").
		if (cvui::button(frame_enroll , 400, offset+200, "&Quit")) {
			break;
		}

        if (cvui::button(frame_enroll , 300, offset+200, "Save")) {
            confirmationFrame(name, age, id, img_path, 1);
		}
		// Since cvui::init() received a param regarding waitKey,
		// there is no need to call cv::waitKey() anymore. cvui::update()
		// will do it automatically.
		cvui::update();
		
		cv::imshow(WINDOW_ENROLL, frame_enroll);
	}

	return 0;
}