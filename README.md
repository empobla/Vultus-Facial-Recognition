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

### Verify

### Identify
## Compile
- Go to the directory where you cloned the repository
- Use the following commands: 
    ```sh
    mkdir build
    cd build
    cmake ..
    make 
    ./FaceDetection
    ```

## Description
The Face Recognition module does the function to detect multiple faces adn then store each of the faces as a Vector of Rectangles.

The module consists of 3 codes:
- FaceDetector.cpp
- FaceDetector.hpp
- main.cpp

## FaceDetector.cpp

This codes function is to create, store and scalate the Vector of Rectangles object.

```c++
#include "FaceDetection.hpp"

using namespace std;
using namespace cv;

//In this method we define the variables to be used.
FaceDetector::FaceDetector(){ 
    faceCascade.load("./haarcascade_frontalface_alt.xml");
    size = 30;
    scale = 5.0;
    window_scaling = 1.1; //This multiplies by the size to find the next bigger image, if there even is one to begin with
    minClassifiers = 4;
    imgHeight = 30;
    flags = 0;
}

//Ths method is a constructor.
FaceDetector::FaceDetector(string faceCascadeFile, int scale, int size, double scale_factor, int minConsensus, int flag){
    faceCascade.load(faceCascadeFile); 
    this->scale = scale; 
    this->size = size;
    window_scaling = scale_factor; 
    minClassifiers = minConsensus; 
    imgHeight = size; 
    flags = flag; 
}

//Creation of the vector, resize and change to grayscale.  
vector<Rect> FaceDetector::detection(Mat frame){ 
    vector<Rect> faces; 
    Mat grayscale; 
    cvtColor(frame, grayscale, COLOR_BGR2GRAY); 
    resize(grayscale, grayscale, cv::Size(grayscale.size().width / scale, grayscale.size().height / scale)); 
    FaceDetector::faceCascade.detectMultiScale(grayscale, faces, window_scaling, minClassifiers, flags, cv::Size(size, size)); 
    return faces; 
} 
 
//Scale used in the capture  
int FaceDetector::getScale(){ 
    return scale; 
}
```

## FaceDetector.hpp 
This code function is to import the libraries that are needed to the module. 
Also we define the privacy of the variables and methods used in FaceDetector.cpp.

```c++
#pragma once 

#include <opencv2/opencv.hpp> 
#include <string> 
#include <stdio.h> 
#include <vector> 

class FaceDetector { 
private: 
	cv::CascadeClassifier faceCascade; 
	int scale; 
	int size; 
	double window_scaling; c
	int minClassifiers; 
	int imgHeight; 
	int flags; 

public: 
	FaceDetector(); 
	FaceDetector(std::string faceCascadeFile, int scale, int size, double scale_factor, int minConsensus, int flag); 
	std::vector<cv::Rect> detection(cv::Mat frame); 
	int getScale(); 
};
```

## main.cpp 
This code function is to act as the GUI when is running, but the code in here uses the two previous mentiones codes to define some functionalities, such as the open of the camera, the draw of a rectangle if a fface is deteected and a function to close the program when Q key is type.

```c++
#include "FaceDetection.hpp" 
#include "FaceDetection.cpp" 

using namespace cv; 
using namespace std; 

int main(){ 
    VideoCapture cap; 
    FaceDetector Detect; 
    int scale; 
    scale = Detect.getScale(); 
    cap = VideoCapture(0); //this variable opens the camera 
    if (!cap.isOpened()){ 
        return -1; 
    }//Close if  
    for (;;){ 
        vector<Rect> faces; 
        Mat frame; 
        cap >> frame; //shift bits 
        faces = Detect.detection(frame); //store in a variable the capture in the camera frame 
        //draw a rectangle around a face detected 
        for (Rect area : faces){ 
            Scalar drawColor = Scalar(255, 0, 0); 
            rectangle(frame, Point(cvRound(area.x * scale), cvRound(area.y * scale)), 
                Point(cvRound(((double)area.x + (double)area.width - 1) * scale), 
                    cvRound(((double)area.y + (double)area.height - 1) * scale)), drawColor); 
        }//Close for 
        imshow("Webcam", frame); //opens a window to show image captured         
        //key to close the program 
        char c = (char)waitKey(10); 
        if (c == 27 || c == 'q' || c == 'Q'){ 
            break; 
        }//Close if 
    }//Close for 
    return 0; 
}//Close main 
```


### Enroll user


*Copyright © 2020 ITESM CSF*
