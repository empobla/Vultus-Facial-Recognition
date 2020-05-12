/*******************************************
 * Emilio Popovits : A01027265
 * Sergio Hernandez : A01025210
 * Luis Antonio Garcia : A01021865
 * Eduardo Harari : A01025876

 This is the header file for the initial face detector program.
 *******************************************/

#pragma once

#include <opencv2/opencv.hpp>
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
	FaceDetector();
	FaceDetector(const std::string path);
	FaceDetector(std::string faceCascadeFile, int scale, int size, double scale_factor, int minConsensus, int flag);
	std::vector<cv::Rect> detection(cv::Mat frame);
	int getScale();
};