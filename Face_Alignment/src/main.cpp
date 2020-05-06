#include <opencv2/core.hpp> //types
#include <opencv2/imgcodecs.hpp> // read image
#include <dlib/image_processing.h> //shape_predictor
#include <opencv2/highgui.hpp> // display image in window

#include <iostream>

#include "faceDetection/module1.hpp"
#include "faceAlignment/align.hpp"

using namespace cv;
using namespace std;


int main(int argc, char **argv)
{
	if (argc != 2) { cout << " There is no image to load \n"; return -1; }

	// Image from input
	Mat image;
	image = imread(argv[1]); // Read the file
	if (image.empty()) { cout << "Could not open or find the image \n"; return -1; }

	// Detect Faces
	vector<Rect> faces;
	Module1::detectFaces(faces, image);

	//Aling face
	FaceAlignment aling;
	//FaceAlignment aling("/root/workspace/models/shape_predictor_5_face_landmarks.dat");

	Mat result;

	for ( size_t i = 0; i < faces.size(); i++ )
	{
		//aling.alignFace(image, faces[i], 200, result);
		aling.alignFaceDebugMode(image, faces[i], 150, result, false);
		// namedWindow("Face Aligned", WINDOW_AUTOSIZE);
		// imshow("Face Aligned", result);
		// waitKey(0); // Wait for a keystroke in the window
	}

	return 0;
}
