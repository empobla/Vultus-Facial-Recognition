# Face Detection

## Authors
[Emilio Popovits](https://github.com) <br/>
[Sergio Hernandez Castillo](https://github.com/sergio-hernandez-castillo) <br/>
[Luis Antonio Garcia](https://github.com/WichoGarcia) <br/>
[Eduardo Harari](https://github.com/eduardoharari)

## Compile
- Open up a terminal
- Clone the repository in the desired directory
- Go to the directory where you cloned the repository
- Use the following commands: 
cmake .
make 
./main.cpp 

## Description
The Face Recognition module does the function to detect multiple faces adn then store each of the faces as a Vector of Rectangles.

The module consists of 3 codes:
- FaceDetector.cpp
- FaceDetector.hpp
- main.cpp

## FaceDetector.cpp

//This code function is to create, store and scalate the Vector of Rectangles object.
#include "FaceDetection.hpp"

using namespace std;
using namespace cv;


/* <br/>
In this method we define the variables to be used.<br/>
*/<br/>
FaceDetector::FaceDetector(){ <br/>
    faceCascade.load("./haarcascade_frontalface_alt.xml");<br/>
    size = 30;<br/>
    scale = 5.0;<br/>
    window_scaling = 1.1; //This multiplies by the size to find the next bigger image, if there even is one to begin with <br/>
    minClassifiers = 4;<br/>
    imgHeight = 30;<br/>
    flags = 0;<br/>
}

<br/>
/*<br/>
 Ths method is a constructor.<br/>
*/<br/>
FaceDetector::FaceDetector(string faceCascadeFile, int scale, int size, double scale_factor, int minConsensus, int flag){ <br/>
    faceCascade.load(faceCascadeFile); <br/>
    this->scale = scale; <br/>
    this->size = size;<br/>
    window_scaling = scale_factor; <br/>
    minClassifiers = minConsensus; <br/>
    imgHeight = size; <br/>
    flags = flag; <br/>
}<br/>

/* <br/>
Creation of the vector, resize and change to grayscale. <br/>
*/ <br/>
vector<Rect> FaceDetector::detection(Mat frame){ <br/>
    vector<Rect> faces; <br/>
    Mat grayscale; <br/>

    cvtColor(frame, grayscale, COLOR_BGR2GRAY); <br/>
    resize(grayscale, grayscale, cv::Size(grayscale.size().width / scale, grayscale.size().height / scale)); <br/>
    FaceDetector::faceCascade.detectMultiScale(grayscale, faces, window_scaling, minClassifiers, flags, cv::Size(size, size)); <br/>

    return faces; <br/>
} <br/>


/* <br/>
Scale used in the capture <br/>
*/ <br/>
int FaceDetector::getScale(){ <br/>
    return scale; <br/>
} <br/>

 ## FaceDetector.hpp <br/>
 /*
 This code function is to import the libraries that are needed to the module. <br/>
 Also we define the privacy of the variables and methods used in FaceDetector.cpp <br/>
 */ <br/>
 #pragma once <br/>

#include <opencv2/opencv.hpp> <br/>
#include <string> <br/>
#include <stdio.h> <br/>
#include <vector> <br/>

class FaceDetector { <br/>
private: <br/>
	cv::CascadeClassifier faceCascade; <br/>
	int scale; <br/>
	int size; <br/>
	double window_scaling; <br/>c
	int minClassifiers; <br/>
	int imgHeight; <br/>
	int flags; <br/>

public:
	FaceDetector();
	FaceDetector(std::string faceCascadeFile, int scale, int size, double scale_factor, int minConsensus, int flag);
	std::vector<cv::Rect> detection(cv::Mat frame);
	int getScale();
};


 ## main.cpp
 
 /*
 This code function is to act as the GUI when is running, but the code in here uses the two previous mentiones codes to define some functionalities, such as the open of the camera, the draw of a rectangle if a fface is deteected and a function to close the program when Q key is type.
*/


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
