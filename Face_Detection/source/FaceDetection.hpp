/*******************************************
 * Emilio Popovits : A01027265
 * Sergio Hernandez : A01025210
 * Luis Antonio Garcia : A01021865
 * Eduardo Harari : A01025876

 This is the header file for the initial face detector program.
 *******************************************/

#pragma once	// Tells compiler to "copy" this only once, even if FaceDetection.hpp used more than once.

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <stdio.h>
#include <vector>

class FaceDetector {
private:
	cv::CascadeClassifier faceCascade;
	int scale;
	int size;
	double window_scaling;
	int minClassifiers;
	int imgHeight;
	int flags;

public:
	FaceDetector();	// Default constructor, initializes variables with "default" values (set by us)
	FaceDetector(const std::string path);	// Constructor that initializes faceCascade path to a chosen one
	FaceDetector(std::string faceCascadeFile, int scale, int size, double scale_factor, int minConsensus, int flag);	// Overload constructor that initializes every other variable to user choice
	std::vector<cv::Rect> detection(cv::Mat frame);	// Converts image into grayscale and resizes
	std::vector<cv::Rect> identify(cv::Mat image);	// Detects faces and draws rectangles around them
	int getScale();	// Getter method for scale variable
};