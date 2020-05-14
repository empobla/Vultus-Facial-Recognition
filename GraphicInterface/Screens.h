#ifndef SCREENS_H
#define SCREENS_H

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
    void FaceVerificationWindow();
    void FaceIdentificationWindow();
    void EnrollStudentWindow();
    void FaceIdentificationMethod(cv::Mat img);
    void AprovedStudentIdentification(int aproved, cv::Mat dbImg1, cv::Mat dbImg2, cv::Mat dbImg3, cv::Mat dbImg4, cv::Mat dbImg5, cv::Mat dbImg6, cv::Mat dbImg7, cv::Mat dbImg8, cv::Mat dbImg9, cv::Mat dbImg10);
    void FaceVerificationMethod(cv::Mat img, cv::String id);
    void AprovedStudentVerification(int aproved, cv::Mat dbImg, cv::String id);
    void confirmationFrame(std::string name, std::string age, std::string id, std::string image, int confirmation);
};

#endif
