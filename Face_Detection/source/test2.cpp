// g++ test2.cpp FaceDetection.cpp -o output `pkg-config --cflags --libs opencv4`

#include "opencv2/objdetect.hpp"
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "FaceDetection.hpp"

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		cout << " There is no image to load \n";
		return -1;
	}

	// Image from input
	Mat image;
	image = imread(argv[1]); // Read the file
	if (image.empty())
	{
		cout << "Could not open or find the image \n";
		return -1;
	}

	FaceDetector Detect("../models/haarcascade_frontalface_alt.xml");

	int scale;
	scale = Detect.getScale();

	// Detect Faces
	vector<Rect> faces;

	faces = Detect.detection(image);

	for (Rect area : faces)
	{
		Scalar drawColor = Scalar(255, 0, 0);

		rectangle(image, Point(cvRound(area.x * scale), cvRound(area.y * scale)),
							Point(cvRound(((double)area.x + (double)area.width - 1) * scale),
										cvRound(((double)area.y + (double)area.height - 1) * scale)),
							drawColor);
	} //Close for
	namedWindow("Face Aligned", WINDOW_AUTOSIZE);
	imshow("Face Aligned", image);
	waitKey(0); // Wait for a keystroke in the window

	return 0;
}