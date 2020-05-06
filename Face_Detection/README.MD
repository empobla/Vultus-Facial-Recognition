# Face Detection

## Authors
[Emilio Popovits](https://github.com) <br/>
[Sergio Hernandez Castillo](https://github.com/sergio-hernandez-castillo) <br/>
[Luis Antonio Garcia](https://github.com/WichoGarcia)
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
This code function is to create, store and scalate the Vector of Rectangles object.
There are 4 methods:
- FaceDetector::FaceDetector(). In this method we define the variables to be used.
- FaceDetector::FaceDetector(string faceCascadeFile, int scale, int size, double scale_factor, int minConsensus, int flag). Ths method is a constructor.
- Vector<Rect> FaceDetector::detection(Mat frame). -Creation of the vector, resize and change to grayscale.
- int FaceDetector::getScale(). Scale used in the capture
  
 ## FaceDetector.hpp
 This code function is to import the libraries that are needed to the module.
 Also we define the privacy of the variables and methods used in FaceDetector.cpp
 
 ## main.cpp
 This code function is to act as the GUI when is running, but the code in here uses the two previous mentiones codes to define some functionalities, such as the open of the camera, the draw of a rectangle if a fface is deteected and a function to close the program when Q key is type.
