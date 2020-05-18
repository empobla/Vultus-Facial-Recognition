#define CVUI_IMPLEMENTATION

# define WINDOW2_NAME "Window 2"
# define WINDOW3_NAME "Window 3"

#define WINDOW_ENROLL "Enroll Student!"
#define WINDOW_CONFIRM "Confirmation!"
#define WINDOW1_NAME "Main Menu"


#include "Screens.h"

  

Screens::Screens() {
   f = new FaceRecognition();
   std::cout<<f<<std::endl;
}

void Screens::Menu(){
    cv::destroyAllWindows();
    cvui::init(WINDOW1_NAME);
    cv::Mat frame = cv::Mat(cv::Size(500, 400), CV_8UC3);
    int count = 0;
    while (true) {
        frame = cv::Scalar(245, 176, 66);
        cvui::text(frame, 10, 10, "VULTUS software", 1, 0xffffff);

        if (cvui::button(frame, 80, 80, "Face verification")) { // To manually verify an unauthorized access
            FaceVerificationWindow();
            break;
        }
        if (cvui::button(frame, 80, 160, "Face identification")) { // Detects the 10 closest matches to the faces database
            // The button was clicked, so let's increment our counter.
            FaceIdentificationWindow();
            break;
        }
        if (cvui::button(frame, 80, 240, "Enroll a student")) { // To feed the database with new values
            EnrollStudentWindow();
            break;
            // The button was clicked, so let's increment our counter.
        }

          if (cvui::button(frame, 80, 320, "&Quit")) { // To feed the database with new values
            break;
            // The button was clicked, so let's increment our counter.
        }
        cvui::imshow(WINDOW1_NAME, frame);
        if (cv::waitKey(20) == 27) {
            break;
        }
    }
    cv::destroyWindow(WINDOW1_NAME);
}


void Screens::CaptureFrame(cv::Mat frame){
    char filename[80];
    sprintf(filename,"/root/workspace/GraphicInterface/test_0.png");
    imwrite(filename, frame);
}


void Screens::confirmationFrame(std::string name, std::string age, std::string id, std::string path, cv::Mat image, int confirmation) {
     // Create a frame where components will be rendered to.
	cv::Mat frame_confirm = cv::Mat(550, 500, CV_8UC3);

	// Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
	cvui::init(WINDOW_CONFIRM);

	while (true) {
		// Fill the frame with a nice color
		frame_confirm = cv::Scalar(245, 176, 66);

        if(confirmation == 1){
            	// Render UI components to the frame
		    cvui::text(frame_confirm, 80, 80, "STUDENT SAVED", 1, 0xffffff);
		    cvui::text(frame_confirm, 80, 120, "Nombre");
            cvui::text(frame_confirm, 80, 180, "Edad");
            cvui::text(frame_confirm, 80, 240, "Matricula");
            cvui::text(frame_confirm, 80, 300, "Foto path");

		    cvui::text(frame_confirm, 80, 140, name);
            cvui::text(frame_confirm, 80, 200, age);
            cvui::text(frame_confirm, 80, 260, id);
            cvui::text(frame_confirm, 80, 320, path);
            cv::Size size(200, 200);
            cv::resize(image, image, size);
            image.copyTo(frame_confirm(cv::Rect(200, 200, 200, 200)));

        }else{
            cvui::text(frame_confirm, 80, 80, "UNABLE TO SAVE STUDENT:(", 1, 0xffffff);

        }


        if (cvui::button(frame_confirm, 80, 400, "DONE")) {
                Menu();
            }
            


		// Update cvui stuff and show everything on the screen
		cvui::imshow(WINDOW_CONFIRM, frame_confirm);

		if (cv::waitKey(20) == 27) {
			break;
		}
	}
}

int Screens::enrollStudent(string path, string name, string age, string id){
    int created = 0;
    cv::Mat image = imread(path);
    cv::imshow("image", image);
    f->enrollStudent(image, id, name, std::stoi(age), created);
    return created;
}

void Screens::EnrollStudentWindow() {
    cv::destroyWindow(WINDOW1_NAME);
   cv::Mat frame_enroll = cv::Mat(cv::Size(500, 400), CV_8UC3);
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
        cvui::text(frame_enroll  , 40, offset+80, "Matricula", 0.5, 0xffffff);
        cvui::text(frame_enroll  , 40, offset+120, "Edad", 0.5, 0xffffff);
        cvui::text(frame_enroll  , 40, offset+160, "Foto path", 0.5, 0xffffff);
        
		cvui::input(frame_enroll , 140, offset+40, 100, "input1", name);
		cvui::input(frame_enroll , 140, offset+80, 100, "input2", id);
        cvui::input(frame_enroll , 140, offset+120, 50, "input3", age);
        cvui::input(frame_enroll , 140, offset+160, 200, "input4", img_path);

		if (cvui::button(frame_enroll , 400, offset+200, "Back")) {
			Menu();
		}

        if (cvui::button(frame_enroll , 300, offset+200, "Save")) {
            confirmationFrame(name, age, id, img_path, imread(img_path), enrollStudent(img_path, name, age, id));
		}

         
	
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
void Screens::FaceVerificationMethod(cv::Mat img, cv::String id){
    cv::Mat input1 = cv::imread("Test_images/img1.png", 1);
    AprovedStudentVerification(0, input1, id);
}

void Screens::FaceIdentificationMethod(cv::Mat img){
    cv::Size size(150, 150);
    cv::Mat input1 = cv::imread("Test_images/img1.png", 1);
    cv::Mat input2 = cv::imread("Test_images/img2.png", 1);
    cv::Mat input3 = cv::imread("Test_images/img3.png", 1);
    cv::Mat input4 = cv::imread("Test_images/img4.jpg", 1);
    cv::resize(input4, input4, size);
    cv::Mat input5 = cv::imread("Test_images/img5.jpg", 1);
    cv::resize(input5, input5, size);
    cv::Mat input6 = cv::imread("Test_images/img6.jpg", 1);
    cv::resize(input6, input6, size);
    cv::Mat input7 = cv::imread("Test_images/img8.png", 1);
    cv::resize(input7, input7, size);
    cv::Mat input8 = cv::imread("Test_images/obama.png", 1);
    cv::resize(input8, input8, size);
    cv::Mat input9 = cv::imread("Test_images/obama_2.png", 1);
    cv::resize(input9, input9, size);
    cv::Mat input10 = cv::imread("Test_images/img9.jpg", 1);
    cv::resize(input10, input10, size);

    AprovedStudentIdentification(1, input1, input2, input3, input4, input5, input6, input7, input8, input9, input10);
}

void Screens::AprovedStudentVerification(int aproved, cv::Mat dbImg, cv::String id){
    cv::Mat acceptedFrame = cv::Mat(cv::Size(1280, 720), CV_8UC3);
    cv::Mat deniedFrame = cv::Mat(cv::Size(1280, 720), CV_8UC3);
    
        while(true){
            cv::Mat screenshot = cv::imread("test_0.png", 1);
            if (aproved==0){
                screenshot.copyTo(acceptedFrame(cv::Rect(0, 0, 640, 480)));
                cvui::text(acceptedFrame, 550, 700, id);
                cvui::text(acceptedFrame, 640, 700, "Not a match, please aprove manually");

                if (cvui::button(acceptedFrame, 700, 160, "Accept")) { 
                    aproved=1;
                    std::cout<<"entre aqui"<<std::endl;
                    //cvui::text(acceptedFrame, 900, 700, "Go ahead!");
                }                
                cvui::update("Images");
            }
            if(aproved==1){
                
                screenshot.copyTo(acceptedFrame(cv::Rect(0, 0, 640, 480)));
                dbImg.copyTo(acceptedFrame(cv::Rect(650, 0, 150, 150)));
                cvui::text(acceptedFrame, 600, 700, id);
                cvui::text(acceptedFrame, 640, 700, "Match, go ahead!", 0.5);
            }
            if(aproved==0){
                cv::imshow("Images", acceptedFrame);
            }
            else{
                cv::imshow("Images", acceptedFrame);
            }
            
            
            if (cv::waitKey(20) == 27) {
                break;
            }
        }
}

void Screens::AprovedStudentIdentification(int aproved, cv::Mat dbImg1, cv::Mat dbImg2, cv::Mat dbImg3, cv::Mat dbImg4, cv::Mat dbImg5, cv::Mat dbImg6, cv::Mat dbImg7, cv::Mat dbImg8, cv::Mat dbImg9, cv::Mat dbImg10){
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
                    //cvui::text(acceptedFrame, 900, 700, "Go ahead!");
                }                
                cvui::update("Images");
            }
            if(aproved==1){
                
                screenshot.copyTo(acceptedFrame(cv::Rect(0, 0, 640, 480)));
                dbImg1.copyTo(acceptedFrame(cv::Rect(650, 0, 150, 150)));
                dbImg2.copyTo(acceptedFrame(cv::Rect(650, 150, 150, 150)));
                dbImg3.copyTo(acceptedFrame(cv::Rect(650, 300, 150, 150)));
                dbImg4.copyTo(acceptedFrame(cv::Rect(650, 450, 150, 150)));
                dbImg5.copyTo(acceptedFrame(cv::Rect(800, 0, 150, 150)));
                dbImg6.copyTo(acceptedFrame(cv::Rect(800, 150, 150, 150)));
                dbImg7.copyTo(acceptedFrame(cv::Rect(800, 300, 150, 150)));
                dbImg8.copyTo(acceptedFrame(cv::Rect(800, 450, 150, 150)));
                dbImg9.copyTo(acceptedFrame(cv::Rect(950, 0, 150, 150)));
                dbImg10.copyTo(acceptedFrame(cv::Rect(950, 150, 150, 150)));
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
