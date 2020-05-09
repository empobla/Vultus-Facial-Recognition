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

public: <br/>
	FaceDetector(); <br/>
	FaceDetector(std::string faceCascadeFile, int scale, int size, double scale_factor, int minConsensus, int flag); <br/>
	std::vector<cv::Rect> detection(cv::Mat frame); <br/>
	int getScale(); <br/>
};
<br/>

 ## main.cpp <br/>
 
 /* <br/>
 This code function is to act as the GUI when is running, but the code in here uses the two previous mentiones codes to define some functionalities, such as the open of the camera, the draw of a rectangle if a fface is deteected and a function to close the program when Q key is type.
*/ <br/>


#include "FaceDetection.hpp" <br/>
#include "FaceDetection.cpp" <br/>

using namespace cv; <br/>
using namespace std; <br/>

int main(){ <br/>
    VideoCapture cap; <br/>

    FaceDetector Detect; <br/>

    int scale; <br/>
    scale = Detect.getScale(); <br/>

    cap = VideoCapture(0); //this variable opens the camera <br/>

    if (!cap.isOpened()){ <br/>
        return -1; <br/>
    }//Close if  <br/>

    for (;;){ <br/>
        vector<Rect> faces; <br/>
        Mat frame; <br/>
        cap >> frame; //shift bits <br/>

        faces = Detect.detection(frame); //store in a variable the capture in the camera frame <br/>

        //draw a rectangle around a face detected <br/>
        for (Rect area : faces){ <br/>
            Scalar drawColor = Scalar(255, 0, 0); <br/>

            rectangle(frame, Point(cvRound(area.x * scale), cvRound(area.y * scale)), <br/>
                Point(cvRound(((double)area.x + (double)area.width - 1) * scale), <br/>
                    cvRound(((double)area.y + (double)area.height - 1) * scale)), drawColor); <br/>
        }//Close for <br/>

        imshow("Webcam", frame); //opens a window to show image captured <br/>
        
        //key to close the program <br/>
        char c = (char)waitKey(10); <br/>

        if (c == 27 || c == 'q' || c == 'Q'){ <br/>
            break; <br/>
        }//Close if <br/>
    }//Close for <br/>

    return 0; <br/>
}//Close main  <br/>
