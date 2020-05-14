#ifndef FACE_RECOGNITION_HPP
#define FACE_RECOGNITION_HPP

#include <opencv2/core.hpp>

// Detection
#include "../../Face_Detection/source/FaceDetection.hpp"
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
	//FaceDetector *faceDetector;
	Module1 *faceDetector;
	FaceAlignment *faceAligner;
	FeatureDetection *featureDetector;
	DBManagerInterface *db;

	/** Integrate module 1,2 and 3 */
	bool getFeatureDescriptors(const cv::Mat &frame, std::vector<cv::Mat> featureDescriptors);
	void showMat(const cv::Mat &image);

public:
	// Default constructor
	FaceRecognition();
	/**
	 * @param cascadeClassifier => path to haarcascade_frontalface_alt.xml
	 * @link https://github.com/opencv/opencv/blob/master/data/haarcascades/haarcascade_frontalface_alt.xml
	 * @param faceLandmark => path to shape_predictor_5_face_landmarks.dat
	 * @link https://github.com/davisking/dlib-models/blob/master/shape_predictor_5_face_landmarks.dat.bz2
	 * @link https://github.com/davisking/dlib-models/blob/master/shape_predictor_68_face_landmarks.dat.bz2
	 * @param resnetModel => path to dlib_face_recognition_resnet_model_v1.dat
	 * @link https://github.com/davisking/dlib-models/blob/master/dlib_face_recognition_resnet_model_v1.dat.bz2
	*/
	FaceRecognition(const std::string cascadeClassifier,const std::string faceLandmark, const std::string resnetModel);
	~FaceRecognition();

	/**
	 * Verify using ID
	 * @param frame => current captured image
	 * @param id => current student
	 * 
	 * @return response:
	 * * 0 : frame and id doesn't match
	 * * 1 : frame and id match
	 * * -1 : there is more than 1 face
	 * @return result: if response is 1, image of the matched student
	*/
	void verify(const cv::Mat &frame, const std::string &id, int &response, cv::Mat &result);
	/** 
	 * Identify without using ID
	 * @param frame => current captured image
	 * 
	 * @return response:
	 * * 0 : can't match the face
	 * * 1 : matched
	 * @return results:
	 * For each int response, 5 possible matches
	*/

	void identify(const cv::Mat frame, std::vector<int> response, std::vector<std::vector<cv::Mat>> results);
	/** 
	 * Add new student to database
	 * @param frame => current captured image
	 * @param id => of the new student
	 * @param name => of the new student
	 * 
	 * @return response:
	 * * 0: Can not be created
	 * * 1: Created succesfully
	 * * 2: Already exists
	*/
	void enrollStudent(cv::Mat frame, const std::string id, const std::string name, int age, int &response);
};

#endif