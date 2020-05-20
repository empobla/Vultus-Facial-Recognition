#ifndef SCREENS_H
#define SCREENS_H

#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string>
#include "cvui.h"
#include <list>
#include <opencv2/face.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include "../_Face_Recognition/src/Face_Recognition.hpp"
#include "../Database/src/include/Cuatec.hpp"


class Screens{
    public: 
    Screens(FaceRecognition *fr);
    void MainWindow();

    private:
    FaceRecognition *f;
    void FaceVerificationWindow();
    void FaceIdentificationWindow();
    void EnrollStudentWindow();
    int enrollStudent(std::string path, std::string name, std::string age, std::string id);
    //Missing Cuatec
    void FaceIdentificationMethod(const cv::Mat img, int &approved, std::vector<cv::Mat> &dbImg);
    void ApprovedStudentIdentification(int approved, cv::Mat screenshot, std::vector<cv::Mat> dbImg,  std::vector<int> inputID);
    //Missing Cuatec0
    void FaceVerificationMethod(const cv::Mat &img, const cv::String &id, int &approved, Cuatec &response);
    void ApprovedStudentVerification(int approved, cv::Mat dbImg, cv::String id);
    void confirmationFrame(std::string name, std::string age, std::string id, std::string path, cv::Mat image, int confirmation);
};

#endif
