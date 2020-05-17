#define CVUI_IMPLEMENTATION

# define WINDOW2_NAME "Window 2"
# define WINDOW3_NAME "Window 3"
# define WINDOW_ENROLL "Window 4"
# define WINDOW_CONFIRM "Window 5"
# include "Screens.h"

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
    int approved=-2;
    cv::String id = "A01024682";

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
            if (cvui::button(frame, 500, 80, "Calculate")) {
                // The button was clicked, so let's increment our counter.
                CaptureFrame(frame);
                cv::Mat screenshot = cv::imread("test_0.png", 1);
                FaceVerificationMethod(screenshot, id, approved);
                //This will be returned with the Cuatec
                cv::Mat input1 = cv::imread("Test_images/img1.png", 1);
                //*****

                AprovedStudentVerification(approved, input1, id);
                
            }
            cvui::text(frame, 80, 300, "Matricula");
            cvui::input(frame, 80, 320, 100, "input", id);
            
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
    int approved = -2;
    std::vector<cv::Mat> dbImg;

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
                FaceIdentificationMethod(screenshot, approved, dbImg);
                AprovedStudentIdentification(approved, dbImg);
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
void Screens::FaceVerificationMethod(const cv::Mat &img, const cv::String &id, int &approved){
    //cv::Mat input1 = cv::imread("Test_images/img1.png", 1);
    approved = 0;
    //AprovedStudentVerification(0, input1, id);
}

void Screens::FaceIdentificationMethod(const cv::Mat img, int &approved, std::vector<cv::Mat> &dbImg){
    std::string name;

    cv::Size size(150, 150);
    cv::Mat input = cv::imread("Test_images/img1.png", 1);
    dbImg.push_back(input);
    input = cv::imread("Test_images/img2.png", 1);
    dbImg.push_back(input);
    input = cv::imread("Test_images/img3.png", 1);
    dbImg.push_back(input);
    input = cv::imread("Test_images/img4.jpg", 1);
    cv::resize(input, input, size);
    dbImg.push_back(input);
    input = cv::imread("Test_images/img5.jpg", 1);
    cv::resize(input, input, size);
    dbImg.push_back(input);
    input = cv::imread("Test_images/img6.jpg", 1);
    cv::resize(input, input, size);
    dbImg.push_back(input);
    input = cv::imread("Test_images/img8.png", 1);
    cv::resize(input, input, size);
    dbImg.push_back(input);
    input = cv::imread("Test_images/obama.png", 1);
    cv::resize(input, input, size);
    dbImg.push_back(input);
    input = cv::imread("Test_images/obama_2.png", 1);
    cv::resize(input, input, size);
    dbImg.push_back(input);
    input = cv::imread("Test_images/img9.jpg", 1);
    cv::resize(input, input, size);
    dbImg.push_back(input);
    approved = 1;

}


void Screens::AprovedStudentIdentification(int aproved, std::vector<cv::Mat> dbImg){
    cv::Mat acceptedFrame = cv::Mat(cv::Size(1280, 720), CV_8UC3);
    cv::Mat deniedFrame = cv::Mat(cv::Size(1280, 720), CV_8UC3);
        while(true){
            cv::Mat screenshot = cv::imread("test_0.png", 1);
            cv::Mat screenshot2 = cv::imread("Test_images/img1.png", 1);
            if (aproved==0){
                screenshot.copyTo(acceptedFrame(cv::Rect(0, 0, 640, 480)));
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
                dbImg[0].copyTo(acceptedFrame(cv::Rect(650, 0, 150, 150)));
                dbImg[1].copyTo(acceptedFrame(cv::Rect(650, 150, 150, 150)));
                dbImg[2].copyTo(acceptedFrame(cv::Rect(650, 300, 150, 150)));
                dbImg[3].copyTo(acceptedFrame(cv::Rect(650, 450, 150, 150)));
                dbImg[4].copyTo(acceptedFrame(cv::Rect(800, 0, 150, 150)));
                dbImg[5].copyTo(acceptedFrame(cv::Rect(800, 150, 150, 150)));
                dbImg[6].copyTo(acceptedFrame(cv::Rect(800, 300, 150, 150)));
                dbImg[7].copyTo(acceptedFrame(cv::Rect(800, 450, 150, 150)));
                dbImg[8].copyTo(acceptedFrame(cv::Rect(950, 0, 150, 150)));
                dbImg[9].copyTo(acceptedFrame(cv::Rect(950, 150, 150, 150)));
                cvui::text(acceptedFrame, 640, 700, "Match, go ahead!");
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

void Screens::EnrollStudentWindow() {
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
		cvui::text(frame_enroll  , 40, offset+50, "Matricula", 0.5, 0xffffff);
        cvui::text(frame_enroll  , 40, offset+80, "Edad", 0.5, 0xffffff);
        cvui::text(frame_enroll  , 40, offset+120, "Nombre", 0.5, 0xffffff);
        cvui::text(frame_enroll  , 40, offset+160, "Foto path", 0.5, 0xffffff);
        
		cvui::input(frame_enroll , 140, offset+40, 100, "input1", name);
		cvui::input(frame_enroll , 140, offset+80, 100, "input2", id);
        cvui::input(frame_enroll , 140, offset+120, 50, "input3", age);
        cvui::input(frame_enroll , 140, offset+160, 200, "input4", img_path);

		if (cvui::button(frame_enroll , 400, offset+200, "&Quit")) {
			break;
		}

        if (cvui::button(frame_enroll , 300, offset+200, "Save")) {
            confirmationFrame(name, age, id, img_path, 1);
		}

		cvui::update();
		
		cv::imshow(WINDOW_ENROLL, frame_enroll);
	}
}

void Screens::confirmationFrame(std::string name, std::string age, std::string id, std::string image, int confirmation) {
	cv::Mat frame_confirm = cv::Mat(550, 500, CV_8UC3);
	cvui::init(WINDOW_CONFIRM);

	while (true) {
		frame_confirm = cv::Scalar(245, 176, 66);

        if(confirmation == 1){
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

		cvui::imshow(WINDOW_CONFIRM, frame_confirm);

		if (cv::waitKey(20) == 27) {
			break;
		}
	}
}
