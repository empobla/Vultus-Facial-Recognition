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
	FaceDetector(std::string faceCascadeFile, int scale, int size, double scale_factor, int minConsensus, int flag);
	std::vector<cv::Rect> detection(cv::Mat frame);
	int getScale();
};