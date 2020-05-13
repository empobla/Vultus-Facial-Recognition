#ifndef FACE_RECOGNITION_HPP
#define FACE_RECOGNITION_HPP

#include <opencv2/core.hpp>

// Detection
#include "../../Face_Alignment/src/faceDetection/module1.hpp"
// Align
#include "../../Face_Alignment/src/faceAlignment/align.hpp"
// Feature Extraction
#include "../../Feature_Extraction/source/feature_detection.h"
// Database
#include "../../Database/src/include/DBManagerInterface.hpp"

class FaceRecognition
{
private:
	Module1 *faceDetector;
	FaceAlignment *faceAligner;
	FeatureDetection *featureDetector;
	DBManagerInterface *db;

public:
	FaceRecognition();
	FaceRecognition(const std::string path1, const std::string path2);
	~FaceRecognition();
	/** */
	void verify(const cv::Mat frame, const std::string id, std::int response, cv::Mat result);
	/** */
	void identify(const cv::Mat frame, std::int response, std::vector<cv::Mat> results);
	/** add new student to database */
	void enrollUser(const cv::Mat frame, const std::string id, const std::string name);
};

#endif