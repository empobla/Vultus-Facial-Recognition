#define CVUI_IMPLEMENTATION

#define WINDOW1_NAME "VUlTUS - Main Menu"
#define WINDOW2_NAME "VULTUS - Verification"
#define WINDOW_VERIFY_ID "VULTUS - ID Verification"
#define WINDOW3_NAME "VULTUS - Identification"
#define WINDOW_ENROLL "VULTUS - Enroll a Student"
#define WINDOW_CONFIRM "VULTUS - Confirmation"
#define WINDOW_AP "VULTUS - Approved Verification"
#define WINDOW_ID "VULTUS - Approved Identification"
#define WINDOW_INSERT_IDD "Vultus- What is your id?"
#define WINDOW_PICTURE_ENROLL "VULTUS - take picture"


#include "Screens.h"

Screens::Screens(FaceRecognition *fr) {
    f = fr;
}

//! --- MENU WINDOW FUNCTION ---

void Screens::MainWindow(){
    cvui::init(WINDOW1_NAME);
    cv::Mat frame = cv::Mat(cv::Size(500, 500), CV_8UC3);
    int count = 0;
    while (true) {
        frame = cv::Scalar(245, 176, 66);
        cvui::text(frame, 100, 10, "VULTUS software", 1, 0xffffff);

        if (cvui::button(frame, 100, 80, "Face verification")) { // To manually verify an unauthorized access
            FaceVerificationWindow();
            cvui::init(WINDOW1_NAME);
            cv::destroyWindow(WINDOW2_NAME);
        }
        if (cvui::button(frame, 100, 160, "Face identification")) { // Detects the 10 closest matches to the faces database
           FaceIdentificationWindow();
           cvui::init(WINDOW1_NAME);
           cv::destroyWindow(WINDOW3_NAME);
        }
        if (cvui::button(frame, 100, 240, "Enroll a student")) { // To feed the database with new values
           EnrollStudentWindow();
            cvui::init(WINDOW1_NAME);
           cv::destroyWindow(WINDOW_ENROLL);
        }
        if (cvui::button(frame, 100, 280, "Quit")) { // To feed the database with new values
           break;
        }
        cvui::imshow(WINDOW1_NAME, frame);
        cvui::update();
        if (cv::waitKey(20) == 27) {
            break;
        }
    }
}


//! --- FACE VERIFICATION FUNCTIONS ---

void Screens::FaceVerificationWindow() {
    int approved= -1;
    std::string path="";
    
    cv::destroyAllWindows();
    cvui::init(WINDOW2_NAME);
    cv::Mat frame = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    Cuatec response;
    //cv::String id = "";
    std::string id;

    while (true) {
        cv::VideoCapture cap;
        cap = cv::VideoCapture(0);
        cap.open(0);
        cvui::text(frame, 10, 10, "FaceVerification");

        cv::Mat screenshot;
    if(!cap.isOpened()){
        while (1){
            printf("--(!)Error opening video capture\n");
            printf("Please enter the path of the image\n");
            std::cin>>path;
            screenshot=cv::imread(path);
            if(!screenshot.empty()){
                break;
            }
        }
        id = IdAdd();
        cv::destroyWindow(WINDOW_INSERT_IDD);
        f->verify(screenshot, id, approved, response);
        std::string inputID = id;
        ApprovedStudentVerification(approved, screenshot, response.getImg(), id, inputID);
        cv::destroyWindow(WINDOW_AP);
        return;

    }
    else{
        while (1){
            cap.read(frame);
            if (cvui::button(frame, 100, 80, "Calculate")) {
                cap >> screenshot;
                id = IdAdd();
                cv::destroyWindow(WINDOW_INSERT_IDD);
                f->verify(screenshot, id, approved, response);
                cap.release();
                std::string inputID = id;
                ApprovedStudentVerification(approved, screenshot, response.getImg(), id, inputID);
                cv::destroyWindow(WINDOW_AP);
                return;
            }
            if (cvui::button(frame, 100, 120, "Back to Menu ")) {
                return;
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
}


cv::String Screens::IdAdd() {
    //cv::destroyAllWindows();
    cv::Mat frame_id_add = cv::Mat(cv::Size(500, 400), CV_8UC3);
	cvui::init(WINDOW_INSERT_IDD, 20);
    cv::String name = "";
    cv::String id = "";
    cv::String age = "";
    cv::String img_path = "";
    int offset = 80;

	while (true) { // Displays the textfields as well as the necessary function buttons
		frame_id_add = cv::Scalar(245, 176, 66);

        cvui::text(frame_id_add  , 40, offset+10, "Please write the id below:", 1, 0xffffff);
		cvui::text(frame_id_add  , 40, offset+50, "ID", 0.5, 0xffffff);
        
		cvui::input(frame_id_add , 140, offset+40, 100, "input1", id);

        if (cvui::button(frame_id_add , 200, offset+150, "Calculate")) {
            return id;
		}
        if (cvui::button(frame_id_add , 200, offset+200, "Add Manually through terminal")) {
            std::cout<<"Add id here "<<std::endl;
            std::cin>>id;
            return id;
		}

		cvui::update();
		cv::imshow(WINDOW_INSERT_IDD, frame_id_add);
	}
}

void Screens::ApprovedStudentVerification(int approved, cv::Mat screenshot, cv::Mat dbImg, cv::String id, std::string inputID) {
    cvui::init(WINDOW_AP);
    cv::Mat acceptedFrame = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    cv::Mat deniedFrame = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    cv::Mat restrictedAccess = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    cv::Mat problemOcurred = cv::Mat::zeros(cv::Size(600, 400), CV_8UC3);

    acceptedFrame = cv::Scalar(245, 176, 66);
    deniedFrame = cv::Scalar(245, 176, 66);
    restrictedAccess = cv::Scalar(245, 176, 66);
    problemOcurred= cv::Scalar(3, 86, 252);

    cv::Mat deniedAccessImage = cv::imread("../Resources/access_denied.jpg", 1);
    cv::Size size(300, 200);
    cv::resize(deniedAccessImage, deniedAccessImage, size);
    
    cv::Size size2(640, 480);
    cv::resize(screenshot, screenshot, size2);
    if(approved != -1){
        cv::resize(dbImg, dbImg, size2);
    }
    
    while (true) {
        if (approved == 0) {
            screenshot.copyTo(deniedFrame(cv::Rect(0, 0, 640, 480)));
            dbImg.copyTo(deniedFrame(cv::Rect(640, 0, 640, 480)));
            deniedAccessImage.copyTo(deniedFrame(cv::Rect(0, 490, 300, 200)));
            cvui::text(deniedFrame, 640, 0, inputID);
            cvui::text(deniedFrame, 550, 700, id);
            cvui::text(deniedFrame, 640, 700, "Not a match, please aprove manually");

            if (cvui::button(deniedFrame, 800, 500, "Accept")) {
                approved = 1;
            }

            if (cvui::button(deniedFrame, 800, 550, "Restrict Access")) {
                approved = 2;
            }

            cv::imshow(WINDOW_AP, deniedFrame);

        }
        if (approved == 1) {
            // cv::Size size(640, 480);
            // cv::resize(dbImg, dbImg, size);
            screenshot.copyTo(acceptedFrame(cv::Rect(0, 0, 640, 480)));
            dbImg.copyTo(acceptedFrame(cv::Rect(640, 0, 640, 480)));
            cvui::text(acceptedFrame, 640, 500, inputID, 1);
            cvui::text(acceptedFrame, 640, 650, id, 1);
            cvui::text(acceptedFrame, 640, 600, "Match, go ahead!", 1);
            if (cvui::button(acceptedFrame, 400, 600, "Back to Menu ")) {
                return;
            }
            cv::imshow(WINDOW_AP, acceptedFrame);

        }
        if (approved == 2) {
            screenshot.copyTo(restrictedAccess(cv::Rect(0, 0, 640, 480)));
            deniedAccessImage.copyTo(restrictedAccess(cv::Rect(0, 490, 300, 200)));
            cvui::text(restrictedAccess, 640, 600, "Access denied! :(", 1);

            if (cvui::button(restrictedAccess, 400, 500, "Back to Menu ")) {
                return;
            }
            cv::imshow(WINDOW_AP, restrictedAccess);

        }
        if(approved == -1){
            cvui::text(problemOcurred, 80, 100, "A problem ocurred,  try again", 1, 0xffffff);
            cvui::text(problemOcurred, 80, 150, "Recommendation: Check if id is in database", 0.5, 0xffffff);
            if (cvui::button(problemOcurred, 200, 200, "Back to Menu ")) {
                return;
            }
            cv::imshow(WINDOW_AP, problemOcurred);

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
    int approved = -1;
    cvui::init(WINDOW3_NAME);
    cv::Mat frame = cv::Mat(cv::Size(1280, 720), CV_8UC3);
    std::vector<cv::Mat> dbImg;
    std::vector<string> idVector;
    cv::Mat screenshot;
    std::vector<Cuatec> result;
    std::string path="";
    cv::Size size(150, 150);

    while (true) {
        cv::VideoCapture cap;
        cap = cv::VideoCapture(0);
        cap.open(0);

        if(!cap.isOpened()){
            while (1){
                printf("--(!)Error opening video capture\n");
                printf("Please enter the path of the image\n");
                std::cin>>path;
                screenshot=cv::imread(path);
                if(!screenshot.empty()){
                    break;
                }
            }
            std::cout<<"Check 1"<<std::endl;
            f->identify(screenshot, approved, result);
            std::cout<<"Check 2"<<std::endl;
            for(int i=0; i< result.size(); i++){
                std::cout<<"4"<<std::endl;
                cv::Mat temporalImg;
                cv::resize(result[i].getImg(), temporalImg, size);
                dbImg.push_back(temporalImg);
                idVector.push_back(result[i].getMatricula());
            }
            ApprovedStudentIdentification(approved, screenshot, dbImg, idVector); 
            cv::destroyWindow(WINDOW_ID);
            return;
        }
        else{


            cvui::text(frame, 10, 10, "FaceIdentification");

            if (!cap.isOpened()){
                printf("--(!)Error opening video capture\n");
            }

            while (1){
                
                cap.read(frame);
                if (cvui::button(frame, 100, 80, "Calculate")) {
                    cap >> screenshot;
                    cap.release();
                    std::cout<<"1"<<std::endl;
                    f->identify(screenshot, approved, result);
                    std::cout<<"2"<<std::endl;
                    if(!result.empty()){
                        std::cout<<"3"<<std::endl;
                        for(int i=0; i< result.size(); i++){
                            std::cout<<"4"<<std::endl;
                            cv::Mat temporalImg;
                            cv::resize(result[i].getImg(), temporalImg, size);
                            dbImg.push_back(temporalImg);
                            idVector.push_back(result[i].getMatricula());
                        }
                    }
                    else{
                        std::cout<<"Is empty"<<std::endl;
                    }
                    
            
                    ApprovedStudentIdentification(approved, screenshot, dbImg, idVector); 
                    cv::destroyWindow(WINDOW_ID);
                    return;
                }
                if (cvui::button(frame, 100, 120, "Back to Menu ")) {
                    return;
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
}



void Screens::ApprovedStudentIdentification(int approved, cv::Mat screenshot, std::vector < cv::Mat > dbImg, std::vector < string > inputID) {
    //cv::destroyAllWindows();
    cvui::init(WINDOW_ID);
    cv::Mat acceptedFrame = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    cv::Mat deniedFrame = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    cv::Mat restrictedAccess = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    cv::Mat problemOcurred = cv::Mat::zeros(cv::Size(1280, 720), CV_8UC3);
    
    cv::Mat deniedAccessImage = cv::imread("../Resources/access_denied.jpg", 1);
    acceptedFrame=cv::Scalar(245, 176, 66);
    restrictedAccess=cv::Scalar(245, 176, 66);
    cv::Size size(300, 200);
    cv::resize(deniedAccessImage, deniedAccessImage, size);
    deniedFrame = cv::Scalar(245, 176, 66);
    int posX = 650;
    int posY= 180;
    int cont = 0;
    
    cv::Size size2(640, 480);
    cv::resize(screenshot, screenshot, size2);
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
                dbImg[cont].copyTo(deniedFrame(cv::Rect(posX, posY*i, 150, 150)));
                cvui::text(deniedFrame, posX, (posY*i)+160, inputID[cont], 0.5, 0xffffff);
                cont++;
            }
            cvui::text(deniedFrame, 100, 600, "Not a match, please aprove manually", 0.8, 0xffffff);

            if (cvui::button(deniedFrame, 1000, 600, "Accept")) { // Manually accepts the incoming person
                approved = 1;
            }
            if (cvui::button(deniedFrame, 1000, 650, "Restrict Access")) { // Manually rejects the incoming person
                approved = 2;
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
                dbImg[cont].copyTo(acceptedFrame(cv::Rect(posX, posY*i, 150, 150)));
                cvui::text(acceptedFrame, posX, (posY*i)+160, inputID[cont], 0.5, 0xff0000);
                cont++;
            }

            cvui::text(acceptedFrame, 200, 600, "Match, go ahead!", 1, 0xffffff);

            if (cvui::button(acceptedFrame, 200, 550, "Back to Menu ")) {
                return;
            }
            cv::imshow(WINDOW_ID, acceptedFrame);

        }
        if (approved == 2) {
            screenshot.copyTo(restrictedAccess(cv::Rect(0, 0, 640, 480)));
            deniedAccessImage.copyTo(restrictedAccess(cv::Rect(950, 300, 300, 200)));
            cvui::text(deniedFrame, 640, 700, "Access denied! :(");
            if (cvui::button(restrictedAccess, 200, 600, "Back to Menu ")) {
                 return;
            }
            cv::imshow(WINDOW_ID, restrictedAccess);
        }
                if(approved == -1){
            cvui::text(problemOcurred, 0, 300, "A problem ocurred, try again", 2.5, 0xff0000);
            cv::imshow(WINDOW_AP, problemOcurred);
            if (cvui::button(problemOcurred, 200, 700, "Back to Menu ")) {
                return;
            }
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
            return;
		}
        if (cvui::button(frame_enroll , 100, offset+250, "Clear")) {
            name = "";
            id = "";
            age = "";
		}

        if (cvui::button(frame_enroll , 300, offset+200, "Take picture")) {
            EnrollStudentScreenshot(name, age, id);
            cv::destroyWindow(WINDOW_PICTURE_ENROLL);
            return;
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
    //cv::destroyAllWindows();
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
        if (cvui::button(frame_confirm, 80, 450, "Back to menu")) {
                //EnrollStudentWindow();
                return;
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
    std::string path="";
    while (true) {
        cv::VideoCapture cap;
        cap = cv::VideoCapture(0);
        cap.open(0);
        cvui::text(frame, 10, 10, "Enroll student");

        if(!cap.isOpened()){
            while (!cap.isOpened()){
                printf("--(!)Error opening video capture\n");
                printf("Please enter the path of the image\n");
                std::cin>>path;
                screenshot=cv::imread(path);
                if(!screenshot.empty()){
                    break;
                }
            }
            cv::imwrite( "ImageDataBase.jpg", screenshot);
            confirmationFrame(name, age, id, "ImageDataBase.jpg", screenshot, enrollStudent("ImageDataBase.jpg", name, age, id));
            cv::destroyWindow(WINDOW_CONFIRM);
            return;

        }
        else{
            while (1){
                cap.read(frame);
                if (cvui::button(frame, 100, 80, "Save Image")) {
                    cap >> screenshot;
                    cv::imwrite( "ImageDataBase.jpg", screenshot);
                    if(!screenshot.data){
                        std::cout<<"no se lee bien la imagen"<<std::endl;
                    }
                    confirmationFrame(name, age, id, "ImageDataBase.jpg", screenshot, enrollStudent("ImageDataBase.jpg", name, age, id));
                    cv::destroyWindow(WINDOW_CONFIRM);
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
}