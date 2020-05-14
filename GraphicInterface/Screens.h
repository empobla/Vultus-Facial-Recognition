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
    void FaceIdentificationMethod(cv::Mat img);
    void AprovedStudentIdentification(int aproved, cv::Mat dbImg1, cv::Mat dbImg2, cv::Mat dbImg3, cv::Mat dbImg4, cv::Mat dbImg5);
};

#endif
