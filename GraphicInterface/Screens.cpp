#define CVUI_IMPLEMENTATION

# define WINDOW2_NAME "Window 2"
# define WINDOW3_NAME "Window 3"

#define WINDOW_ENROLL "Enroll Student!"
#define WINDOW_CONFIRM "Confirmation!"


#include "Screens.h"

Screens::Screens() {
    std::cout<<"constructed screen "<<std::endl;
}

void Screens::CaptureFrame(cv::Mat frame){
    char filename[80];
    sprintf(filename,"/root/workspace/GraphicInterface/test_0.png");
    imwrite(filename, frame);
}


//Metodos para probar GUI

void Screens::FaceVerificationMethod(cv::Mat img){
    cv::Mat input1 = cv::imread("Test_images/img1.png", 1);
    // Metodo de aprobacion
    ApprovedStudentVerification(1, input1);
}

void Screens::ApprovedStudentVerification(int approved, cv::Mat dbImg){
    cv::Mat acceptedFrame = cv::Mat(cv::Size(1280, 720), CV_8UC3);
    cv::Mat deniedFrame = cv::Mat(cv::Size(1280, 720), CV_8UC3);
        while(true){
            cv::Mat screenshot = cv::imread("test_0.png", 1);
            cv::Mat screenshot2 = cv::imread("Test_images/img1.png", 1);
            if (approved==0){
                screenshot.copyTo(deniedFrame(cv::Rect(0, 0, 640, 480)));
                cvui::text(deniedFrame, 640, 700, "Not a match, please aprove manually");

                if (cvui::button(deniedFrame, 700, 160, "Accept")) { 
                    approved=1;
                    std::cout<<"entre aqui"<<std::endl;
                    //cvui::text(acceptedFrame, 900, 700, "Go ahead!");
                }                
                cvui::update("Images");
            }
            if(approved==1){
                
                screenshot.copyTo(acceptedFrame(cv::Rect(0, 0, 640, 480)));
                dbImg.copyTo(acceptedFrame(cv::Rect(650, 0, 150, 150)));
                cvui::text(acceptedFrame, 640, 700, "Match, go ahead!");
            }
            if(approved==0){
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

void Screens::FaceIdentificationMethod(cv::Mat img){
    cv::Mat input1 = cv::imread("Test_images/img1.png", 1);
    cv::Mat input2 = cv::imread("Test_images/img2.png", 1);
    cv::Mat input3 = cv::imread("Test_images/img3.png", 1);
    cv::Mat input4 = cv::imread("Test_images/img4.jpg", 1);
    cv::Mat input5 = cv::imread("Test_images/img5.jpg", 1);
    approvedStudentIdentification(0, input1, input2, input3, input4, input5);
}


void Screens::approvedStudentIdentification(int approved, cv::Mat dbImg1, cv::Mat dbImg2, cv::Mat dbImg3, cv::Mat dbImg4, cv::Mat dbImg5){
    cv::Mat acceptedFrame = cv::Mat(cv::Size(1280, 720), CV_8UC3);
    cv::Mat deniedFrame = cv::Mat(cv::Size(1280, 720), CV_8UC3);
        while(true){
            cv::Mat screenshot = cv::imread("test_0.png", 1);
            cv::Mat screenshot2 = cv::imread("Test_images/img1.png", 1);
            if (approved==0){
                screenshot.copyTo(deniedFrame(cv::Rect(0, 0, 640, 480)));
                cvui::text(deniedFrame, 640, 700, "Not a match, please aprove manually");

                if (cvui::button(deniedFrame, 700, 160, "Accept")) { 
                    approved=1;
                    std::cout<<"entre aqui"<<std::endl;
                    //cvui::text(acceptedFrame, 900, 700, "Go ahead!");
                }                
                cvui::update("Images");
            }
            if(approved==1){
                
                screenshot.copyTo(acceptedFrame(cv::Rect(0, 0, 640, 480)));
                dbImg1.copyTo(acceptedFrame(cv::Rect(650, 0, 150, 150)));
                dbImg2.copyTo(acceptedFrame(cv::Rect(650, 150, 150, 150)));
                dbImg3.copyTo(acceptedFrame(cv::Rect(650, 300, 150, 150)));
                dbImg4.copyTo(acceptedFrame(cv::Rect(650, 450, 226, 226)));
                dbImg5.copyTo(acceptedFrame(cv::Rect(800, 0, 200, 200)));
                cvui::text(acceptedFrame, 640, 700, "Match, go ahead!");
            }
            if(approved==0){
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
		    cvui::text(frame_confirm, 80, 120, "Name");
            cvui::text(frame_confirm, 80, 180, "Age");
            cvui::text(frame_confirm, 80, 240, "ID");
            cvui::text(frame_confirm, 80, 300, "Photo Path");

		    cvui::text(frame_confirm, 80, 140, name);
            cvui::text(frame_confirm, 80, 200, age);
            cvui::text(frame_confirm, 80, 260, id);
            cvui::text(frame_confirm, 80, 320, image);
        }else{
            cvui::text(frame_confirm, 80, 80, "UNABLE TO SAVE STUDENT:(");

        }



        if (cvui::button(frame_confirm, 80, 400, "DONE")) {
                
            }
            


		// Update cvui stuff and show everything on the screen
		cvui::imshow(WINDOW_CONFIRM, frame_confirm);

		if (cv::waitKey(20) == 27) {
			break;
		}
	}
}

void Screens::EnrollStudentWindow() {
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

        cv::String id = "";
        int offset = 80;
        cvui::text(frame  , 40, offset+10, "INPUT THE ID", 1, 0xffffff);
        cvui::text(frame  , 40, offset+120, "ID", 0.5, 0xffffff);
        cvui::input(frame , 140, offset+80, 100, "input1", id);

        while (1){
            cap.read(frame);
            if (cvui::button(frame, 500, 80, "Calculate")) {
                CaptureFrame(frame);
                cv::Mat screenshot = cv::imread("test_0.png", 1);
                FaceVerificationMethod(screenshot);
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