# TC2004-FaceRecognition-Spring2020

**Face Recognition System** is a C++ project to recognize members of Tecnológico de Monterrey CSF

## Requirements

### Functional

- The system will recognize members of Tecnológico de Monterrey CSF.
- The system throws alerts in case the credential does not match the face.
- The system allows to authenticate (comparing) the data of the students with those of the credential.
- The system will grant access if the data match.
- The system will show an alert whether or not he is the person.
- The system allows to enroll new students.
- The system should either verify or identify the student.

### Non Functional

- The system must run in Mac OS (10.14 +), Windows 10 + and Linux (Ubuntu 18.04 +)
- The result must be given under 1 second
- The system is planned to be delivered by May 28th
- The name of the system: <name>
- Data must stay safe and secure

## Dependencies

Below are the dependencies used in this project:

- [OpenCV](https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html)
- [Dlib](https://github.com/davisking/dlib)
- [Mongocxx Driver](http://mongocxx.org/mongocxx-v3/installation/)
- [MongoDB](https://www.mongodb.com/download-center/community)
- [CMake](https://cmake.org/download/)

## Install

```sh
git clone https://github.com/leonardochang36/TC2004-FaceRecognition-Spring2020.git

cd TC2004-FaceRecognition-Spring2020 && GraphicInterface && mkdir build && cmake .. && make

./GUI
```

## How to use

### GUI

Inside the code, the main functions that are used are the following:

**_GUI.cpp_**

```c
int main(){
	// Calls the MainWindow() function contained inside Screens.cpp
}
```

**_Screens.cpp_**

```c
void Screens::MainWindow(){
	// Creates the buttons and calls the respective functions
}


// VERIFICATION METHODS
void Screens::FaceVerificationWindow(){
	// To verify an access given a capture and an ID
}

void Screens::InputID(std::string id){
	// Opens a window for the user to input the ID
}

void Screens::FaceVerificationMethod(const cv::Mat &img, const cv::String &id, int &approved, Cuatec &response){
	// Approves or denies an access attempt
}

void Screens::ApprovedStudentVerification(int approved, cv::Mat screenshot, cv::Mat dbImg, cv::String id, std::string inputID){
	// Window after the automatic verification process, can approve or deny access manually
}

// IDENTIFICATION METHODS
void Screens::FaceIdentificationWindow(){
	// To verify an access given a capture and an the top 10 database closest images
}

void Screens::FaceIdentificationMethod(const cv::Mat &img, int &approved, std::vector<cv::Mat> &dbImg){
	// Approves or denies an access attempt
}

void Screens::ApprovedStudentIdentification(int approved, cv::Mat screenshot, std::vector < cv::Mat > dbImg, std::vector < string > inputID) {
	// Window after the automatic verification process, can approve or deny access manually
}

// ENROLL METHODS
void Screens::EnrollStudentWindow(){
	// Creates window with textboxes to be filled with the required user information
}

int Screens::enrollStudent(std::string path, std::string name, std::string age, std::string id){
	// Uploads the data to the database
}

void Screens::confirmationFrame(std::string name, std::string age, std::string id, std::string path, cv::Mat image, int confirmation) {
	// Displays the input data in another window
}
```

Graphical User Interface that allows an easy access to the system's functions. For standalone testing go to the GraphicInterface subdirectory and input the following commands:

```sh
mkdir build
cd build
cmake ..
make
./GraphicInterface
```

**_NOTE:_** There must be a camera attached to the computer for the program to work fully.

Once the program is successfully compiled and is running, the navigation through the GUI is pretty simple. There will be buttons displayed which will run the different functions associated with them.

### Verify

This method verifies if the subject in frame matches the subject in database for a given ID. It uses the modules Face Detection, Face Alignment and Features Extraction modules to get the features of the subject in frame, then uses the module Database to get the features saved for the ID given and compares both features.

#### Parameters

- Frame: cv::Mat object of the frame captured.
- ID: std::string of Id
- Response: integer that will contain the response of the verification. 1 for same person, 0 for not matched and -1 for method error.
- Result: Cuatec object that, in case of match, will contain the matching Cuatec found in DB.

### Identify

This method unites the face detection, face alignment, feature extraction and database modules into one. As parameters, it receives the current frame ("frame") being shot by the camera, an integer ("response") that will either be saved as a 0 or 1, and the empty vector (result) of possible matches to the face in the current frame.

The method begins by creating an empty Mat object called "features", which will be used as an argument along with the current frame when calling "getFeatureDescriptorsFromFrame()". That method encapsulates the first three modules of this system (face detection, face alignment and feature extraction),takes "features" and "near_neighbors" as arguments and once all 3 modules have done their piece of work, a boolean variable is returned. If it was returned as a true, it means all 3 modules worked fine, so "response" is saved as a 1, and "result" will be filled with possible matches to the face in the current frame via a call to "fastSearch" (a method provided by the database module), which takes as arguments the now filled "features" Mat object and "near_neighbors" (the amount of possible matches desired to be seen). If the boolean returned from "getFeatureDescriptorsFromFrame()" was returned as false, the person using the system is notified through an "Error" message and "response" is saved as 0.

```c++
void FaceRecognition::identify(const cv::Mat &frame, int &response, std::vector<Cuatec> &result)
{
	cv::Mat features;

	if (getFeatureDescriptorsFromFrame(frame, features))
	{
		//Matched the face
		response = 1;
		//result = db->readOne(id);
		result = db->fastSearch(features, near_neighbors);
	}

	else
	{
		cout << "Error: Something went wrong in the identification process.\n";
		//Can't match the face
		response = 0;
	}
}
```

### Enroll user

_Copyright © 2020 ITESM CSF_
