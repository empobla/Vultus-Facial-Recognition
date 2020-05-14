// g++ test.cpp FaceDetection.cpp -o output `pkg-config --cflags --libs opencv4`

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "FaceDetection.hpp"

using namespace std;
using namespace cv;

string cascadeName, nestedCascadeName;

int main(int argc, const char **argv)
{
	// VideoCapture class for playing video for which faces to be detected
	VideoCapture capture;
	Mat frame, image;

	FaceDetector Detect("../models/haarcascade_frontalface_alt.xml");

	int scale;
	scale = Detect.getScale();

	// Start Video..1) 0 for WebCam 2) "Path to Video" for a Local Video
	capture.open(0);
	if (capture.isOpened())
	{
		// Capture frames from video and detect faces
		cout << "Face Detection Started...." << endl;
		while (1)
		{
			vector<Rect> faces;
			Mat frame;
			capture >> frame;

			faces = Detect.detection(frame);

			for (Rect area : faces)
			{
				Scalar drawColor = Scalar(255, 0, 0);

				rectangle(frame, Point(cvRound(area.x * scale), cvRound(area.y * scale)),
									Point(cvRound(((double)area.x + (double)area.width - 1) * scale),
												cvRound(((double)area.y + (double)area.height - 1) * scale)),
									drawColor);
			} //Close for

			imshow("Webcam", frame);
			char c = (char)waitKey(10);

			// Press q to exit from window
			if (c == 27 || c == 'q' || c == 'Q')
				break;
		}
	}
	else
		cout << "Could not Open Camera";
	return 0;
}
