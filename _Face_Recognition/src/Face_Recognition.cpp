#include "Face_Recognition.hpp"
#include <iostream>

using namespace std;

FaceRecognition::FaceRecognition()
{
	faceDetector = new Module1();
	faceAligner = new FaceAlignment("../../Face_Alignment/models/shape_predictor_5_face_landmarks.dat");
	featureDetector = new FeatureDetection("../../Feature_Extraction/source/net/dlib_face_recognition_resnet_model_v1.dat");
	db = new DBManagerInterface(URI, DATABASE, COLLECTION);
}

FaceRecognition::~FaceRecognition()
{
	delete faceDetector;
	delete faceAligner;
	delete featureDetector;
	delete db;
	cout << "No errors\n";
}

void FaceRecognition::verify(const cv::Mat frame, const std::string id, std::int response, cv::Mat result)
{
	// Reading features of Cuatec id from DB
	cv::Mat cuatecFeatures = db->readOneFeatures(id);

	//Face detect from frame
	std::vector<Rect> faces;
	faceDetector->detectFaces(faces, frame);

	//Face align
	cv::Mat faceAligned;

	for (size_t i = 0; i < faces.size(); i++)
	{
		aling.alignFaceDebugMode(frame, faces[i], 150, faceAligned, true);
	}

	//Features extraction
	cv::Mat subjectFeatures = featureDetector->getFeatures2(faceAligned);

	double match_rate = 0;
	double acceptance_rate = 0.5;

	match_rate = featureDetector->compareFeatures(subjectFeatures, cuatecFeatures, 5);

	//Compare features from DB vs features from frame
	if (cv::abs(match_rate) <= acceptance_rate)
	{
		//Same person
		response = 1;
		result = db.readOneImg(id);
	}
	else
	{
		//Different person
		response = 0;
	}
}
