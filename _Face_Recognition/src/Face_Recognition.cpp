#include "Face_Recognition.hpp"
#include <iostream>

using namespace std;

FaceRecognition::FaceRecognition(){
	faceDetector = new Module1();
	faceAligner = new FaceAlignment("../../Face_Alignment/models/shape_predictor_5_face_landmarks.dat");
	featureDetector = new FeatureDetection("../../Feature_Extraction/source/net/dlib_face_recognition_resnet_model_v1.dat");
	db = new DBManagerInterface(URI, DATABASE, COLLECTION);
}

FaceRecognition::~FaceRecognition(){
	delete faceDetector;
	delete faceAligner;
	delete featureDetector;
	delete db;
	cout << "No errors\n";
}