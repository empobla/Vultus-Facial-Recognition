#ifndef FACE_ALIGNMENT_HPP
#define FACE_ALIGNMENT_HPP

#include <iostream>
#include <opencv2/core.hpp>
#include <dlib/image_processing.h> //shape_predictor

// http://dlib.net/face_landmark_detection_ex.cpp.html | Landmark detection
// https://hetpro-store.com/TUTORIALES/opencv-rect/ | Info about Rect

class FaceAlignment
{
private:
	/** path to the model*/
	std::string faceLandmarkModel;

	/** sp, can be 5 points or 68 points */
	dlib::shape_predictor landmarkDetector;

	/** store pointer to convert opencv */
	dlib::matrix<dlib::rgb_pixel> face_chips;

	/** 
	 * Load the model using deserialize provided by dlib,
	 * this should be called inside constructor
	*/
	void loadModel();

	/**
	 * Convert opencv Rect in to dlib rectangle
	*/
	void cvRecttodlibRectangle(const cv::Rect &r, dlib::rectangle &rec);

	/**
	 * Main align method, public are variant of this
	*/
	void alignFaceComplete(
			const cv::Mat &image,
			const cv::Rect &faceArea,
			const int size,
			cv::Mat &alignImage,
			const bool debugMode,
			const bool drawMode);

public:
	/** Default constructor */
	FaceAlignment();
	/**
	 * @param path => route to shape_predictor_68_face_landmarks.dat
	 * @link http://dlib.net/files/shape_predictor_5_face_landmarks.dat.bz2
	 * @link http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2
	*/
	FaceAlignment(const std::string path);
	/**
	 * @param Image => current image analyzing
	 * @param FaceArea => current ROI, where is possible to detect eyes
	 * @param Size => for output align image
	 * @param AligImage => store result
	 * Align the face using eyes as reference
	 * @return cv::Mat with face aligned and cropped
	*/
	/**
	 * Clear pointer to result
	*/
	~FaceAlignment();

	void alignFace(
			const cv::Mat &image,
			const cv::Rect &faceArea,
			const int size,
			cv::Mat &alignImage);
	/**
	 * @see FaceAlignment::alignFace()
	 * @param draw => if true will show the final image
	*/
	void alignFaceDebugMode(
			const cv::Mat &image,
			const cv::Rect &faceArea,
			const int size,
			cv::Mat &alignImage,
			const bool draw);
};

#endif