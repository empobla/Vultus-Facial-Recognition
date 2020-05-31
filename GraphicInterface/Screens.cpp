#define CVUI_IMPLEMENTATION

#define WINDOW1_NAME "VUlTUS - Main Menu"
#define WINDOW2_NAME "VULTUS - Verification"
#define WINDOW_VERIFY_ID "VULTUS - ID Verification"
#define WINDOW3_NAME "VULTUS - Identificration"
#define WINDOW_ENROLL "VULTUS - Enroll a Student"
#define WINDOW_CONFIRM "VULTUS - Confirmation"
#define WINDOW_AP "VULTUS - Approved Verification"
#define WINDOW_ID "VULTUS - Approved Identification"
#define WINDOW_PICTURE_ENROLL "VULTUS - take picture"


#include "Screens.h"

Screens::Screens(FaceRecognition *fr) {
    f = fr;
}


void Screens::Init(){
    // int check = 1;
    // while(check==1){
    //     std::cout<<"To continue enter 1"<<std::endl;
    //     std::cout<<"To stop enter -1"<<std::endl;
    //     cin >> check;
    //     MainWindow();
        
    // }

    while(true){
        MainWindow();

        if (cv::waitKey(20) == 27) {
            return;
        }
    }
};
//! --- MENU WINDOW FUNCTION ---

void Screens::MainWindow(){
    cv::destroyAllWindows();
    cvui::init(WINDOW1_NAME);
    cv::Mat frame = cv::Mat(cv::Size(500, 500), CV_8UC3);
    int count = 0;
    while (true) {
        frame = cv::Scalar(245, 176, 66);
        cvui::text(frame, 100, 10, "VULTUS software", 1, 0xffffff);

        if (cvui::button(frame, 100, 80, "Face verification")) { // To manually verify an unauthorized access
            FaceVerificationWindow();
            //cv::destroyWindow(WINDOW2_NAME);
            cv::destroyAllWindows();
            return;
            //break;
        }
        if (cvui::button(frame, 100, 160, "Face identification")) { // Detects the 10 closest matches to the faces database
            // The button was clicked, so let's increment our counter.
           FaceIdentificationWindow();
           return;
            //break;

        }
        if (cvui::button(frame, 100, 240, "Enroll a student")) { // To feed the database with new values
           EnrollStudentWindow();
           return;
           //break;
        }
        if (cvui::button(frame, 100, 300, "&Quit")) { 
            //cv::destroyAllWindows();  
            return;
        }
        cvui::imshow(WINDOW1_NAME, frame);
        cvui::update();
        if (cv::waitKey(20) == 27) {
            return;
        }
        // cvui::update();
        // std::cout<<"volvi a correr"<<std::endl;
    }
}


//! --- FACE VERIFICATION FUNCTIONS ---

void Screens::FaceVerificationWindow() {
    int approved= -2;
    //cv::destroyAllWindows();
    cvui::init(WINDOW2_NAME);
    cv::Mat frame = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    Cuatec response;
    cv::String id = "";
    std::cout<<"Please enter your id"<<std::endl;
    std::cin>>id;

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
            if (cvui::button(frame, 500, 80, "Calculate")) {
                cap >> screenshot;
                //InputId(id);
                //cv::destroyWindow(WINDOW_VERIFY_ID);
                f->verify(screenshot, id, approved, response);
                std::cout<<approved<<std::endl;
                // FaceVerificationMethod(screenshot, id, approved, response); // This will be returned with the Cuatec
                // cout << response;
                cap.release();
                std::string inputID = id;
                ApprovedStudentVerification(approved, screenshot, response.getImg(), id, inputID);
                cv::destroyWindow(WINDOW_AP);
                return;
                if (cv::waitKey(20) == 27) { // Waits for the escape key to be pressed in order to exit the window
                    return;
                }
            }
            if (cvui::button(frame, 500, 120, "Back to Menu ")) {
                //MainWindow();
                return;
                if (cv::waitKey(20) == 27) { // Waits for the escape key to be pressed in order to exit the window
                    return;
                }
                
            }
            
            cvui::update();
            cv::imshow(WINDOW2_NAME, frame);

            if (cv::waitKey(20) == 27) { // Waits for the escape key to be pressed in order to exit the window
                return;
            }
        }

        if (cv::waitKey(20) == 27) { // Waits for the escape key to be pressed in order to exit the window
            return;
        }
    }
}

void Screens::InputId(std::string &id){
    cvui::init(WINDOW_VERIFY_ID);
    cv::Mat frameId = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);

    while (true){
		frameId = cv::Scalar(245, 176, 66);

            cvui::text(frameId, 80, 240, "Matricula");

            cvui::input(frameId, 140, 80, 100, "input4", id);
            cvui::update();
        if (cvui::button(frameId, 80, 400, "Confirm")) {
                 return;
        }


		cvui::imshow(WINDOW_VERIFY_ID, frameId);
		if (cv::waitKey(20) == 27) {
			return;
		}
	}
}

void Screens::FaceVerificationMethod(const cv::Mat &img, const cv::String &id, int &approved, Cuatec &response){
    //cv::Mat input1 = cv::imread("Test_images/img1.png", 1);
    approved = 0;
    //ApprovedStudentVerification(0, input1, id);
}

void Screens::ApprovedStudentVerification(int approved, cv::Mat screenshot, cv::Mat dbImg, cv::String id, std::string inputID) {
    //cv::destroyAllWindows();
    cvui::init(WINDOW_AP);

    cv::Mat acceptedFrame = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    cv::Mat deniedFrame = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    cv::Mat restrictedAccess = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    cv::Mat problemOcurred = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);

    acceptedFrame = cv::Scalar(245, 176, 66);
    deniedFrame = cv::Scalar(245, 176, 66);
    restrictedAccess = cv::Scalar(245, 176, 66);
    problemOcurred= cv::Scalar(245, 176, 66);

    cv::Mat deniedAccessImage = cv::imread("../Resources/access_denied.jpg", 1);
    cv::Size size(300, 200);
    cv::resize(deniedAccessImage, deniedAccessImage, size);
    
    while (true) {
        if (approved == 0) {
            screenshot.copyTo(deniedFrame(cv::Rect(0, 0, 640, 480)));
            dbImg.copyTo(deniedFrame(cv::Rect(640, 0, 640, 480)));
            deniedAccessImage.copyTo(deniedFrame(cv::Rect(0, 490, 300, 200)));
            cvui::text(deniedFrame, 640, 0, inputID);
            cvui::text(deniedFrame, 550, 700, id);
            cvui::text(deniedFrame, 640, 700, "Not a match, please aprove manually");

            if (cvui::button(deniedFrame, 700, 500, "Accept")) {
                approved = 1;
                //cvui::text(acceptedFrame, 900, 700, "Go ahead!");
            }

            if (cvui::button(deniedFrame, 700, 550, "Restrict Access")) {
                approved = 2;
                //cvui::text(acceptedFrame, 900, 700, "Go ahead!");
            }

            cv::imshow(WINDOW_AP, deniedFrame);

        }
        if (approved == 1) {
            // cv::Size size(640, 480);
            // cv::resize(dbImg, dbImg, size);
            screenshot.copyTo(acceptedFrame(cv::Rect(0, 0, 640, 480)));
            dbImg.copyTo(acceptedFrame(cv::Rect(640, 0, 640, 480)));
            cvui::text(acceptedFrame, 640, 0, inputID);
            cvui::text(acceptedFrame, 500, 700, id);
            cvui::text(acceptedFrame, 640, 700, "Match, go ahead!", 0.5);
            if (cvui::button(acceptedFrame, 400, 600, "Back to Menu ")) {
                //MainWindow();
                return;
                if (cv::waitKey(20) == 27) { // Waits for the escape key to be pressed in order to exit the window
                    return;
                }
            }
            cv::imshow(WINDOW_AP, acceptedFrame);

        }
        if (approved == 2) {
            screenshot.copyTo(restrictedAccess(cv::Rect(0, 0, 640, 480)));
            deniedAccessImage.copyTo(restrictedAccess(cv::Rect(0, 490, 300, 200)));
            cvui::text(restrictedAccess, 640, 700, "Access denied! :(");

            if (cvui::button(restrictedAccess, 200, 700, "Back to Menu ")) {
                //MainWindow();
                return;
                if (cv::waitKey(20) == 27) { // Waits for the escape key to be pressed in order to exit the window
                    return;
                }

            }
            cv::imshow(WINDOW_AP, restrictedAccess);

        }
        if(approved == -1){
            cvui::text(problemOcurred, 0, 300, "A problem ocurred, try again", 2.5, 0xff0000);
            cv::imshow(WINDOW_AP, problemOcurred);
            if (cvui::button(problemOcurred, 200, 700, "Back to Menu ")) {
                return;
                if (cv::waitKey(20) == 27) { // Waits for the escape key to be pressed in order to exit the window
                    return;
                }

            }
        }

        cvui::update();
       
        if (cv::waitKey(20) == 27) {
            return;
        }
    }
}



//! --- FACE IDENTIFICATION FUNCTIONS ---

void Screens::FaceIdentificationWindow() {
     cv::destroyAllWindows();
    cvui::init(WINDOW3_NAME);
    cv::Mat frame = cv::Mat(cv::Size(1280, 720), CV_8UC3);

    int approved = -2;
    std::vector<cv::Mat> dbImg;
    std::vector<string> idVector;
    cv::Size size(150, 150);

    while (true) {

        cv::VideoCapture cap;
        cap = cv::VideoCapture(0);
        cap.open(0);
        cvui::text(frame, 10, 10, "FaceIdentification");

        if (!cap.isOpened()){
            printf("--(!)Error opening video capture\n");
        }

        cv::Mat screenshot;
        std::vector<Cuatec> result;
        while (1){
            cap.read(frame);
            if (cvui::button(frame, 500, 80, "Calculate")) {
                cap >> screenshot;
                cap.release();
                std::cout<<"0"<<std::endl;
                f->identify(screenshot, approved, result);
                std::cout<<"1"<<std::endl;
                //FaceIdentificationMethod(screenshot, approved, dbImg);
                if(!result.empty()){
                    std::cout<<"2"<<std::endl;
                    for(int i=0; i< result.size(); i++){
                        std::cout<<"3"<<std::endl;
                        cv::Mat temporalImg;
                        cv::resize(result[i].getImg(), temporalImg, size);
                        dbImg.push_back(temporalImg);
                        
                        //std::cout<<"Mat "<<i<<": "<<dbImg[i]<<std::endl;
                        //dbImg.push_back(result[i].getImg());
                        idVector.push_back(result[i].getMatricula());
                    }
                }
                else{
                    std::cout<<"Is empty"<<std::endl;
                }

                std::cout<<"Approved: "<<approved<<std::endl;
                //FaceIdentificationMethod(screenshot, approved, dbImg);
                 
            if (cvui::button(frame, 500, 120, "Back to Menu ")) {
                MainWindow();
                return;
            }
                ApprovedStudentIdentification(approved, screenshot, dbImg, idVector); 
            }
            
            cv::imshow(WINDOW3_NAME, frame);
            if (cv::waitKey(20) == 27) {
                return;
            }
        }

        if (cv::waitKey(20) == 27) {
            return;
        }
    }
}


void Screens::FaceIdentificationMethod(const cv::Mat &img, int &approved, std::vector<cv::Mat> &dbImg){
    std::string name;

    cv::Size size(150, 150);

    // Hard-coded method to input the values in the vector variable, will be automated when the database is connected to the function
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
    approved=0;
}

void Screens::ApprovedStudentIdentification(int approved, cv::Mat screenshot, std::vector < cv::Mat > dbImg, std::vector < string > inputID) {
    cv::destroyAllWindows();
    cvui::init(WINDOW_ID);
    cv::Mat acceptedFrame = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    cv::Mat deniedFrame = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    cv::Mat restrictedAccess = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    cv::Mat deniedAccessImage = cv::imread("../Resources/access_denied.jpg", 1);
    acceptedFrame=cv::Scalar(245, 176, 66);
    restrictedAccess=cv::Scalar(245, 176, 66);
    cv::Size size(300, 200);
    cv::resize(deniedAccessImage, deniedAccessImage, size);
    deniedFrame = cv::Scalar(245, 176, 66);
    int posX = 650;
    int posY= 180;
    int cont = 0;

    while (true) {
        if (approved == 0) {
            // Print of the 10 images with the closest relation to the capture, hard-coded and will be automated when database implementation replaces it
            screenshot.copyTo(deniedFrame(cv::Rect(0, 0, 640, 480)));
            posX = 650;
            posY= 180;
            cont = 0;

            for(int i =0; cont<dbImg.size(); i++){
                
                if(posY*i==720){
                    if((posX+150)<=1280 && ((posY*i))<=720){
                        i=0; 
                        posX += 180;                   
                    }
                    else{
                        break;
                    }
                }
                //std::cout<<"Pos x: "<<posX<<" Pos y: "<<posY*i<<std::endl;
                dbImg[cont].copyTo(deniedFrame(cv::Rect(posX, posY*i, 150, 150)));
                cvui::text(deniedFrame, posX, posY*i, inputID[cont], 0.5, 0xff0000);
                cont++;
            }
            cvui::text(deniedFrame, 640, 700, "Not a match, please aprove manually");

            if (cvui::button(deniedFrame, 800, 600, "Accept")) { // Manually accepts the incoming person
                approved = 1;
                // std::cout<<"entre aqui"<<std::endl;
                // cvui::text(acceptedFrame, 900, 700, "Go ahead!");
            }
            if (cvui::button(deniedFrame, 800, 650, "Restrict Access")) { // Manually rejects the incoming person
                approved = 2;
                //cvui::text(acceptedFrame, 900, 700, "Denied, please do not allow the access to the installations.");
            }

            cv::imshow(WINDOW_ID, deniedFrame);

        }

        if (approved == 1) { // Very similar to the block mentioned beforehand, but the approval is given directly by the system  
            screenshot.copyTo(acceptedFrame(cv::Rect(0, 0, 640, 480)));
            posX = 650;
            posY= 180;
            cont = 0;

            for(int i =0; cont<dbImg.size(); i++){
                
                if(posY*i==720){
                    if((posX+150)<=1280 && ((posY*i))<=720){
                        i=0; 
                        posX += 180;                   
                    }
                    else{
                        break;
                    }
                }
                //std::cout<<"Pos x: "<<posX<<" Pos y: "<<posY*i<<std::endl;
                dbImg[cont].copyTo(acceptedFrame(cv::Rect(posX, posY*i, 150, 150)));
                cvui::text(acceptedFrame, posX, posY*i, inputID[cont], 0.5, 0xff0000);
                // cvui::text(acceptedFrame, posX, posY*i, inputID[cont]);
                cont++;
            }

            cvui::text(acceptedFrame, 640, 700, "Match, go ahead!");

            if (cvui::button(acceptedFrame, 200, 600, "Back to Menu ")) {
                MainWindow();
                return;
            }
            cv::imshow(WINDOW_ID, acceptedFrame);

        }
        if (approved == 2) {
            screenshot.copyTo(restrictedAccess(cv::Rect(0, 0, 640, 480)));
            deniedAccessImage.copyTo(restrictedAccess(cv::Rect(950, 300, 300, 200)));
            cvui::text(deniedFrame, 640, 700, "Access denied! :(");
            if (cvui::button(restrictedAccess, 200, 600, "Back to Menu ")) {
                MainWindow();
                 return;
            }
            cv::imshow(WINDOW_ID, restrictedAccess);
        }
        cvui::update();

        if (cv::waitKey(20) == 27) {
            return;
        }
    }
}



//! --- STUDENT ENROLL FUNCTIONS ---

void Screens::EnrollStudentWindow() {
    cv::destroyAllWindows();
    cv::Mat frame_enroll = cv::Mat(cv::Size(500, 400), CV_8UC3);
	cvui::init(WINDOW_ENROLL, 20);
    cv::String name = "";
    cv::String id = "";
    cv::String age = "";
    cv::String img_path = "";
    int offset = 80;

	while (true) { // Displays the textfields as well as the necessary function buttons
		frame_enroll = cv::Scalar(245, 176, 66);

        cvui::text(frame_enroll  , 40, offset+10, "ENROLL STUDENT", 1, 0xffffff);
		cvui::text(frame_enroll  , 40, offset+50, "Nombre", 0.5, 0xffffff);
        cvui::text(frame_enroll  , 40, offset+80, "Matricula", 0.5, 0xffffff);
        cvui::text(frame_enroll  , 40, offset+120, "Edad", 0.5, 0xffffff);
        
		cvui::input(frame_enroll , 140, offset+40, 100, "input1", name);
		cvui::input(frame_enroll , 140, offset+80, 100, "input2", id);
        cvui::input(frame_enroll , 140, offset+120, 50, "input3", age);

		if (cvui::button(frame_enroll , 300, offset+250, "Back to Menu")) {
			MainWindow();
            return;
		}

        if (cvui::button(frame_enroll , 300, offset+200, "Take picture")) {
            EnrollStudentScreenshot(name, age, id);
            //confirmationFrame(name, age, id, "ImageDataBase.jpg", cv::imread("ImageDataBase.jpg"), enrollStudent(img_path, name, age, id));
		}

		cvui::update();
		cv::imshow(WINDOW_ENROLL, frame_enroll);
	}
}

int Screens::enrollStudent(std::string path, std::string name, std::string age, std::string id){
    int created = 0;
    cv::Mat image = cv::imread(path, 1);
    f->enrollStudent(image, id, name, std::stoi(age), created);
    return created;
}



void Screens::confirmationFrame(std::string name, std::string age, std::string id, std::string path, cv::Mat &image, int confirmation) {
	cv::Mat frame_confirm = cv::Mat(550, 500, CV_8UC3);
    cv::destroyAllWindows();
	cvui::init(WINDOW_CONFIRM);

	while (true){
		frame_confirm = cv::Scalar(245, 176, 66);

        if(confirmation == 1){ // Displays confirmation message showing the values that were saved in the database
		    cvui::text(frame_confirm, 80, 80, "STUDENT SAVED", 1, 0xffffff);
		    cvui::text(frame_confirm, 80, 120, "Nombre");
            cvui::text(frame_confirm, 80, 180, "Edad");
            cvui::text(frame_confirm, 80, 240, "Matricula");

		    cvui::text(frame_confirm, 80, 140, name);
            cvui::text(frame_confirm, 80, 200, age);
            cvui::text(frame_confirm, 80, 260, id);
            cv::Size size(200, 200);
            cv::resize(image, image, size);
            image.copyTo(frame_confirm(cv::Rect(200, 200, 200, 200)));

        } else {
            cvui::text(frame_confirm, 80, 80, "UNABLE TO SAVE STUDENT:(", 1, 0xffffff);
        }
        if (cvui::button(frame_confirm, 80, 400, "Back to Menu")) {
                MainWindow();
                 return;
        }
        if (cvui::button(frame_confirm, 80, 450, "Enroll New Student")) {
                EnrollStudentWindow();
        }

		cvui::imshow(WINDOW_CONFIRM, frame_confirm);

		if (cv::waitKey(20) == 27) {
			return;
		}
	}
}

void Screens::EnrollStudentScreenshot(std::string name, std::string age, std::string id) {
    //cv::destroyAllWindows();
    cvui::init(WINDOW_PICTURE_ENROLL);
    cv::Mat frame = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    cv::Mat screenshot;
    while (true) {
        cv::VideoCapture cap;
        cap = cv::VideoCapture(0);
        cap.open(0);
        cvui::text(frame, 10, 10, "Enroll student");

        if (!cap.isOpened()){
            printf("--(!)Error opening video capture\n");
            return;
        }

        while (1){
            cap.read(frame);
            if (cvui::button(frame, 500, 80, "Calculate")) {
                cap >> screenshot;
                cv::imwrite( "ImageDataBase.jpg", screenshot);
                if(!screenshot.data){
                    std::cout<<"no se lee bien la imagen"<<std::endl;
                }
                //std::cout<<screenshot<<std::endl;
                //void confirmationFrame(std::string name, std::string age, std::string id, std::string path, cv::Mat image, int confirmation);
                confirmationFrame(name, age, id, "ImageDataBase.jpg", screenshot, enrollStudent("ImageDataBase.jpg", name, age, id));
                cap.release();
                return;
            }
            
            cvui::update();
            cv::imshow(WINDOW_PICTURE_ENROLL, frame);


            if (cv::waitKey(20) == 27) { // Waits for the escape key to be pressed in order to exit the window
                return;
            }
        }

        if (cv::waitKey(20) == 27) { // Waits for the escape key to be pressed in order to exit the window
            return;
        }
    }
}