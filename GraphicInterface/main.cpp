#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// One (and only one) of your C++ files must define CVUI_IMPLEMENTATION
// before the inclusion of cvui.h to ensure its implementaiton is compiled.
#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define ENROLL "Enroll Student!"
#define WINDOW_CONFIRM "Confirmation!"




int main(int argc, const char *argv[])
{
	// Create a frame where components will be rendered to.
	cv::Mat frame_enroll = cv::Mat(550, 500, CV_8UC3);

	// Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
	cvui::init(ENROLL);

    cv::String name = "name";
    cv::String id = "id";
    cv::String age = "age";
    cv::String img_path = "image path";
	while (true) {
		// Fill the frame with a nice color
		frame_enroll  = cv::Scalar(245, 176, 66);

		// Render UI components to the frame
		cvui::text(frame_enroll , 80, 80, "ENROLL STUDENT");
		cvui::text(frame_enroll , 80, 120, "Nombre");
        cvui::text(frame_enroll , 80, 180, "Edad");
        cvui::text(frame_enroll , 80, 240, "Matricula");
        cvui::text(frame_enroll , 80, 300, "Foto path");

        cvui::input(frame_enroll, 80, 130, 100, "input1", name);
        cvui::input(frame_enroll, 80, 200, 100, "input2", id);
		cvui::input(frame_enroll, 80, 260, 100, "input3", age);
        cvui::input(frame_enroll, 80, 320, 100, "input4", img_path);


        if (cvui::button(frame_enroll, 80, 400, "ENROLL")) {
                confirmationFrame(name, age, id, img_path, 1);
            }
            



        cvui::update();
		// Update cvui stuff and show everything on the screen
		cvui::imshow(ENROLL, frame_enroll );

		if (cv::waitKey(20) == 27) {
			break;
		}
	}




	return 0;
}