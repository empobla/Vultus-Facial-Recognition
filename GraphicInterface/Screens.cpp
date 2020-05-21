#define CVUI_IMPLEMENTATION

#define WINDOW1_NAME "Window 1"
# define WINDOW2_NAME "Window 2"
# define WINDOW3_NAME "Window 3"
# define WINDOW_ENROLL "Window 4"
# define WINDOW_CONFIRM "Window 5"
# define WINDOW_AP "Approved Verification"
# define WINDOW_ID "Approved Identification"

# include "Screens.h"

Screens::Screens(FaceRecognition *fr) {
    f = fr;
}

void Screens::MainWindow(){
    cv::destroyAllWindows();
    cvui::init(WINDOW1_NAME);
    cv::Mat frame = cv::Mat(cv::Size(1280, 720), CV_8UC3);
    int count = 0;
    while (true) {
        frame = cv::Scalar(100, 100, 100);
        cvui::text(frame, 10, 10, "VULTUS software");

        if (cvui::button(frame, 500, 80, "Face verification")) { // To manually verify an unauthorized access
            FaceVerificationWindow();
            break;
        }
        if (cvui::button(frame, 500, 160, "Face identification")) { // Detects the 10 closest matches to the faces database
            // The button was clicked, so let's increment our counter.
           FaceIdentificationWindow();
           
        }
        if (cvui::button(frame, 500, 240, "Enroll a student")) { // To feed the database with new values
           EnrollStudentWindow();
        }
        cvui::imshow(WINDOW1_NAME, frame);
        if (cv::waitKey(20) == 27) {
            break;
        }
    }
}


void Screens::FaceVerificationWindow() {
    cv::destroyAllWindows();
    cvui::init(WINDOW2_NAME);
    cv::Mat frame = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    int approved= -2;
    Cuatec response;
    cv::String id = "A01024682";

    while (true) {

        cv::VideoCapture cap;
        cap = cv::VideoCapture(0);
        cap.open(0);
        cvui::text(frame, 10, 10, "FaceVerification");

        if (!cap.isOpened()){
            printf("--(!)Error opening video capture\n");
            return;
        }

        cv::Mat screenshot;
        while (1){
            cap.read(frame);
            // Show a button at position (110, 80)
            if (cvui::button(frame, 500, 80, "Calculate")) {
                // The button was clicked, so let's increment our counter.
               

                cap >> screenshot;

                // use f here
                //f->verify(screenshot, id, approved, response);
                FaceVerificationMethod(screenshot, id, approved, response);
                //This will be returned with the Cuatec

                // cout << response;


                ApprovedStudentVerification(approved, screenshot, screenshot, id);

             

                
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

    int approved = -2;
    std::vector<cv::Mat> dbImg;

    while (true) {

        cv::VideoCapture cap;
        cap = cv::VideoCapture(0);
        cap.open(0);
        cvui::text(frame, 10, 10, "FaceIdentification");

        if (!cap.isOpened()){
            printf("--(!)Error opening video capture\n");
        }

        cv::Mat screenshot;
        //std::vector<Cuatec> result;
        while (1){
            cap.read(frame);
            // Show a button at position (110, 80)
            if (cvui::button(frame, 500, 80, "Calculate")) {
                // The button was clicked, so let's increment our counter.
                cap >> screenshot;

                // f->identify(screen, approved, result);
                FaceIdentificationMethod(screenshot, approved, dbImg);

                std::vector<int> idVector;

                for (int i = 0; i < 10; i++){
                    idVector.push_back(1025948);
                }

                ApprovedStudentIdentification(approved, screenshot, dbImg, idVector); 
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
void Screens::FaceVerificationMethod(const cv::Mat &img, const cv::String &id, int &approved, Cuatec &response){
    //cv::Mat input1 = cv::imread("Test_images/img1.png", 1);
    approved = 0;
    //ApprovedStudentVerification(0, input1, id);
}

void Screens::FaceIdentificationMethod(const cv::Mat img, int &approved, std::vector<cv::Mat> &dbImg){
    std::string name;

    cv::Size size(150, 150);
    cv::Mat input = cv::imread("../Test_images/img1.png", 1);
    dbImg.push_back(input);
    input = cv::imread("../Test_images/img2.png", 1);
    dbImg.push_back(input);
    input = cv::imread("../Test_images/img3.png", 1);
    dbImg.push_back(input);
    input = cv::imread("../Test_images/img4.jpg", 1);
    cv::resize(input, input, size);
    dbImg.push_back(input);
    input = cv::imread("../Test_images/img5.jpg", 1);
    cv::resize(input, input, size);
    dbImg.push_back(input);
    input = cv::imread("../Test_images/img6.jpg", 1);
    cv::resize(input, input, size);
    dbImg.push_back(input);
    input = cv::imread("../Test_images/img8.png", 1);
    cv::resize(input, input, size);
    dbImg.push_back(input);
    input = cv::imread("../Test_images/obama.png", 1);
    cv::resize(input, input, size);
    dbImg.push_back(input);
    input = cv::imread("../Test_images/obama_2.png", 1);
    cv::resize(input, input, size);
    dbImg.push_back(input);
    input = cv::imread("../Test_images/img9.jpg", 1);
    cv::resize(input, input, size);
    dbImg.push_back(input);
    approved = 0;

}


void Screens::ApprovedStudentIdentification(int approved, cv::Mat screenshot, std::vector<cv::Mat> dbImg,  std::vector<int> inputID){
    cv::destroyWindow(WINDOW3_NAME);
    cvui::init(WINDOW_ID);
    cv::Mat acceptedFrame = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    cv::Mat deniedFrame = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    cv::Mat restrictedAccess = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
        while(true){
            if (approved==0){
                screenshot.copyTo(deniedFrame (cv::Rect(0, 0, 640, 480)));
                std::string outputID = "";
                outputID = std::to_string(inputID[0]);
                dbImg[0].copyTo(deniedFrame(cv::Rect(650, 0, 150, 150)));
                outputID = std::to_string(inputID[0]);
                cvui::text(deniedFrame, 650, 0, outputID);
                dbImg[2].copyTo(deniedFrame(cv::Rect(650, 300, 150, 150)));
                outputID = std::to_string(inputID[1]);
                cvui::text(deniedFrame, 650, 300, outputID);
                dbImg[1].copyTo(deniedFrame(cv::Rect(650, 150, 150, 150)));
                outputID = std::to_string(inputID[2]);
                cvui::text(deniedFrame, 650, 150, outputID);
                dbImg[3].copyTo(deniedFrame(cv::Rect(650, 450, 150, 150)));
                outputID = std::to_string(inputID[3]);
                cvui::text(deniedFrame, 650, 450, outputID);
                dbImg[4].copyTo(deniedFrame(cv::Rect(800, 0, 150, 150)));
                outputID = std::to_string(inputID[4]);
                cvui::text(deniedFrame, 800, 0, outputID);
                dbImg[5].copyTo(deniedFrame(cv::Rect(800, 150, 150, 150)));
                outputID = std::to_string(inputID[5]);
                cvui::text(deniedFrame, 800, 150, outputID);
                dbImg[6].copyTo(deniedFrame(cv::Rect(800, 300, 150, 150)));
                outputID = std::to_string(inputID[6]);
                cvui::text(deniedFrame, 800, 300, outputID);
                dbImg[7].copyTo(deniedFrame(cv::Rect(800, 450, 150, 150)));
                outputID = std::to_string(inputID[7]);
                cvui::text(deniedFrame, 800, 450, outputID);
                dbImg[8].copyTo(deniedFrame(cv::Rect(950, 0, 150, 150)));
                outputID = std::to_string(inputID[8]);
                cvui::text(deniedFrame, 950, 0, outputID);
                dbImg[9].copyTo(deniedFrame(cv::Rect(950, 150, 150, 150)));
                outputID = std::to_string(inputID[9]);
                cvui::text(deniedFrame, 950, 150, outputID);
                cvui::text(deniedFrame, 640, 700, "Not a match, please aprove manually");

                if (cvui::button(deniedFrame , 800, 160, "Accept")) { 
                    approved=1;
                    std::cout<<"entre aqui"<<std::endl;
                    //cvui::text(acceptedFrame, 900, 700, "Go ahead!");
                }
                if (cvui::button(deniedFrame , 800, 200, "Restrict Access")) { 
                    approved=2;
                    //cvui::text(acceptedFrame, 900, 700, "Denied, please do not allow the access to the installations.");
                }              
                cv::imshow(WINDOW_ID, deniedFrame);

            }
            if(approved==1){
                std::string outputID = "";
                outputID = std::to_string(inputID[0]);
                screenshot.copyTo(acceptedFrame(cv::Rect(0, 0, 640, 480)));
                dbImg[0].copyTo(acceptedFrame(cv::Rect(650, 0, 150, 150)));
                outputID = std::to_string(inputID[0]);
                cvui::text(acceptedFrame, 650, 0, outputID);
                dbImg[2].copyTo(acceptedFrame(cv::Rect(650, 300, 150, 150)));
                outputID = std::to_string(inputID[1]);
                cvui::text(acceptedFrame, 650, 300, outputID);
                dbImg[1].copyTo(acceptedFrame(cv::Rect(650, 150, 150, 150)));
                outputID = std::to_string(inputID[2]);
                cvui::text(acceptedFrame, 650, 150, outputID);
                dbImg[3].copyTo(acceptedFrame(cv::Rect(650, 450, 150, 150)));
                outputID = std::to_string(inputID[3]);
                cvui::text(acceptedFrame, 650, 450, outputID);
                dbImg[4].copyTo(acceptedFrame(cv::Rect(800, 0, 150, 150)));
                outputID = std::to_string(inputID[4]);
                cvui::text(acceptedFrame, 800, 0, outputID);
                dbImg[5].copyTo(acceptedFrame(cv::Rect(800, 150, 150, 150)));
                outputID = std::to_string(inputID[5]);
                cvui::text(acceptedFrame, 800, 150, outputID);
                dbImg[6].copyTo(acceptedFrame(cv::Rect(800, 300, 150, 150)));
                outputID = std::to_string(inputID[6]);
                cvui::text(acceptedFrame, 800, 300, outputID);
                dbImg[7].copyTo(acceptedFrame(cv::Rect(800, 450, 150, 150)));
                outputID = std::to_string(inputID[7]);
                cvui::text(acceptedFrame, 800, 450, outputID);
                dbImg[8].copyTo(acceptedFrame(cv::Rect(950, 0, 150, 150)));
                outputID = std::to_string(inputID[8]);
                cvui::text(acceptedFrame, 950, 0, outputID);
                dbImg[9].copyTo(acceptedFrame(cv::Rect(950, 150, 150, 150)));
                outputID = std::to_string(inputID[9]);
                cvui::text(acceptedFrame, 950, 150, outputID);
                cvui::text(acceptedFrame, 640, 700, "Match, go ahead!");
               

                if (cvui::button(acceptedFrame , 200, 700, "Back to Menu ")) { 
                    MainWindow();
                } 
                cv::imshow(WINDOW_ID, acceptedFrame);

            }
            if(approved == 2){
                screenshot.copyTo(restrictedAccess(cv::Rect(0, 0, 640, 480)));
                cvui::text(restrictedAccess, 640, 700, "Access denied! :(");
                if (cvui::button(restrictedAccess , 200, 700, "Back to Menu ")) { 
                    MainWindow();
                }    
                cv::imshow(WINDOW_ID, restrictedAccess);  


            }

            
           
            cvui::update();

            if (cv::waitKey(20) == 27) {
                break;
            }
        }
}

void Screens::ApprovedStudentVerification(int approved, cv::Mat screenshot, cv::Mat dbImg, cv::String id){
    //cv::destroyWindow(WINDOW2_NAME);
    //cv::destroyWindow(WINDOW1_NAME);
    cvui::init(WINDOW_AP);

    cv::Mat acceptedFrame = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    cv::Mat deniedFrame = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    cv::Mat restrictedAccess = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    
        while(true){
            if (approved==0){
                screenshot.copyTo(deniedFrame(cv::Rect(0, 0, 640, 480)));
                dbImg.copyTo(deniedFrame(cv::Rect(640, 0, 640, 480)));
                cvui::text(deniedFrame, 550, 700, id);
                cvui::text(deniedFrame, 640, 700, "Not a match, please aprove manually");

                if (cvui::button(deniedFrame, 700, 160, "Accept")) { 
                    std::cout<<"entre aqui"<<std::endl;
                    approved =1;
                    //cvui::text(acceptedFrame, 900, 700, "Go ahead!");
                }     
                if (cvui::button(deniedFrame, 700, 200, "Restrict Access")) { 
                    approved = 2;
                    //cvui::text(acceptedFrame, 900, 700, "Go ahead!");
                } 
                
                cv::imshow(WINDOW_AP, deniedFrame);

            }
            if(approved==1){
                // cv::Size size(640, 480);m
                // cv::resize(dbImg, dbImg, size);
                screenshot.copyTo(acceptedFrame(cv::Rect(0, 0, 640, 480)));
                dbImg.copyTo(acceptedFrame(cv::Rect(640, 0, 640, 480)));
                cvui::text(acceptedFrame, 500, 700, id);
                cvui::text(acceptedFrame, 640, 700, "Match, go ahead!", 0.5);
                cv::imshow(WINDOW_AP, acceptedFrame);

            }
            if(approved == 2){
                screenshot.copyTo(restrictedAccess(cv::Rect(0, 0, 640, 480)));
                cvui::text(restrictedAccess, 640, 700, "Access denied! :(");
                if (cvui::button(restrictedAccess , 200, 700, "Back to Menu ")) { 
                    MainWindow();
                }    
                cv::imshow(WINDOW_AP, restrictedAccess);  


            }


            cvui::update();

            if (cv::waitKey(20) == 27) {
                break;
            }
        }
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
                MainWindow();
            }
            


		// Update cvui stuff and show everything on the screen
		cvui::imshow(WINDOW_CONFIRM, frame_confirm);

		if (cv::waitKey(20) == 27) {
			break;
		}
	}
}

int Screens::enrollStudent(std::string path, std::string name, std::string age, std::string id){
    int created = 0;
    cv::Mat image = cv::imread(path);
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
			MainWindow();
		}

        if (cvui::button(frame_enroll , 300, offset+200, "Save")) {
            confirmationFrame(name, age, id, img_path, cv::imread(img_path), enrollStudent(img_path, name, age, id));
		}

         
	
		cvui::update();
		
		cv::imshow(WINDOW_ENROLL, frame_enroll);
	}

}
