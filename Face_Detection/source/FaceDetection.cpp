#include "FaceDetection.hpp"

using namespace std;
using namespace cv;

FaceDetector::FaceDetector(){
    faceCascade.load("./haarcascade_frontalface_alt.xml");
    size = 30;
    scale = 5.0;
    window_scaling = 1.1; //This multiplies by the size to find the next bigger image, if there even is one to begin with 
    minClassifiers = 4;
    imgHeight = 30;
    flags = 0;
}

FaceDetector::FaceDetector(string faceCascadeFile, int scale, int size, double scale_factor, int minConsensus, int flag){
    faceCascade.load(faceCascadeFile);
    this->scale = scale;
    this->size = size;
    window_scaling = scale_factor;
    minClassifiers = minConsensus;
    imgHeight = size;
    flags = flag;
}

vector<Rect> FaceDetector::detection(Mat frame){
    vector<Rect> faces;
    Mat grayscale;

    cvtColor(frame, grayscale, COLOR_BGR2GRAY);
    resize(grayscale, grayscale, cv::Size(grayscale.size().width / scale, grayscale.size().height / scale));
    FaceDetector::faceCascade.detectMultiScale(grayscale, faces, window_scaling, minClassifiers, flags, cv::Size(size, size));

    return faces;
}

int FaceDetector::getScale(){
    return scale;
}