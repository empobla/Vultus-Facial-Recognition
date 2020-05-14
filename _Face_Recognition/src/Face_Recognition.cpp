#include "Face_Recognition.hpp"
#include <opencv2/core.hpp>
#include <dlib/image_processing.h>
#include <iostream>

using namespace std;
using namespace cv;

FaceRecognition::FaceRecognition()
{
	//faceDetector = new FaceDetector("../../Face_Detection/models/haarcascade_frontalface_alt.xml");
	faceDetector = new Module1("../../Face_Detection/models/haarcascade_frontalface_alt.xml");
	faceAligner = new FaceAlignment("../../Face_Alignment/models/shape_predictor_5_face_landmarks.dat");
	featureDetector = new FeatureDetection("../../Feature_Extraction/source/net/dlib_face_recognition_resnet_model_v1.dat");
	db = new DBManagerInterface(URI, DATABASE, COLLECTION);
}

FaceRecognition::FaceRecognition(const std::string cascadeClassifier, const std::string faceLandmark, const std::string resnetModel)
{
	//faceDetector = new FaceDetector(cascadeClassifier);
	faceDetector = new Module1(cascadeClassifier);
	faceAligner = new FaceAlignment(faceLandmark);
	featureDetector = new FeatureDetection(resnetModel);
	db = new DBManagerInterface(URI, DATABASE, COLLECTION);
}

FaceRecognition::~FaceRecognition()
{
	delete faceDetector;
	delete faceAligner;
	delete featureDetector;
	delete db;
}

void FaceRecognition::verify(const cv::Mat &frame, const std::string &id, int &response, Cuatec result)
{
	// T4 implement your code here!

	cv::Mat features;
	if (getFeatureDescriptorsFromFrame(frame, features))
	{
		cout << "Continue\n";
	}
	else
	{
		cout << "something went wrong\n";
	}
}

void FaceRecognition::identify(const cv::Mat &frame, int &response, std::vector<Cuatec> &result)
{
	// T1 implemenet your code here!
}

void FaceRecognition::enrollStudent(cv::Mat frame, const std::string id, const std::string name, const int age, int &response)
{

	cv::Mat features;
	if (getFeatureDescriptorsFromFrame(frame, features))
	{
		int created = db->create(name, age, id, frame, features);
		if (created == 1)
		{
			std::cout << " student enrolled successfully " << std::endl;
		}
		else
		{
		std:
			cout << "student cannot be enrolled!" << std::endl;
		}
		response = created;
	}
	else
	{
		cout << "something went wrong\n";
		response = 0;
	}
}

// Private methods

bool FaceRecognition::getFeatureDescriptorsFromFrame(const cv::Mat &frame, cv::Mat featureDescriptors)
{
	//showMat(frame);

	// using module 1
	//std::vector<cv::Rect> faces = faceDetector->detection(frame);

	//using faceAlignment test module
	std::vector<Rect> faces;
	faceDetector->detectFaces(faces, frame);

	if (faces.size() < 0)
	{
		return false;
	}

	Mat tempRes;

	//showMat(frame(faces[i]));
	//cout << faces[i] << "\n";
	faceAligner->alignFace(frame, faces[0], 150, tempRes);
	//showMat(tempRes);
	featureDescriptors = featureDetector->getFeatures2(tempRes);
	//cout << featureDescriptors << "\n";

	return true;
}

void FaceRecognition::showMat(const cv::Mat &image)
{
	namedWindow("image", WINDOW_AUTOSIZE);
	imshow("image", image);
	waitKey(0); // Wait for a keystroke in the window
}