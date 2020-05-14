#ifndef SCREENS_H
#define SCREENS_H
#define CVUI_IMPLEMENTATION

#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include "cvui.h"
#include <list>
#include <opencv2/face.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class Screens{
    public:
    Screens();
    void CaptureFrame(cv::Mat frame);
    void FaceVerificationWindow();
    void FaceIdentificationWindow();
    void EnrollStudentWindow();
    void FaceIdentificationMethod(cv::Mat img);
    void FaceVerificationMethod(cv::Mat img);
    void ApprovedStudentVerification(int approved, cv::Mat dbImg);
    void approvedStudentIdentification(int approved, cv::Mat dbImg1, cv::Mat dbImg2, cv::Mat dbImg3, cv::Mat dbImg4, cv::Mat dbImg5);
};

#endif
