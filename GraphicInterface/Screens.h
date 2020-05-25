/*
Code written by Alejandra Nissan, Carla Perez and Carlos Garcia
Tecnologico de Monterrey, Santa Fe

Header file, inclusion of libraries and function definitions for integration purposes
*/

#ifndef SCREENS_H
#define SCREENS_H

// Common libraries used
#include <stdio.h>
#include <string>
#include <list>
#include <vector>

// openCV
#include <opencv2/face.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

// GUI implementation based on openCV imshow and other graphics-oriented functions
#include "cvui.h"

// References to other scripts for integration purposes
#include "../_Face_Recognition/src/Face_Recognition.hpp"
#include "../Database/src/include/Cuatec.hpp"

// Function definitions
class Screens{
    public: 
        Screens(FaceRecognition *fr);
        void MainWindow();

    private:
        FaceRecognition *f;
        
        // FaceVerification functions
        void FaceVerificationWindow();
        void FaceVerificationMethod(const cv::Mat &img, const cv::String &id, int &approved, Cuatec &response); //Missing Cuatec0
        void InputID(std::string id);
        void ApprovedStudentVerification(int approved, cv::Mat screenshot, cv::Mat dbImg, cv::String id, std::string inputID);

        // FaceIdentification functions
        void FaceIdentificationWindow();
        void FaceIdentificationMethod(const cv::Mat &img, int &approved, std::vector<cv::Mat> &dbImg); //Missing Cuatec
        void ApprovedStudentIdentification(int approved, cv::Mat screenshot, std::vector<cv::Mat> dbImg,  std::vector<string> inputID);
        
        // EnrollStudent functions
        void EnrollStudentWindow();
        int enrollStudent(std::string path, std::string name, std::string age, std::string id);
        void confirmationFrame(std::string name, std::string age, std::string id, std::string path, cv::Mat image, int confirmation);
        void EnrollStudentScreenshot(); 
};

#endif
