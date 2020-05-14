#include <iostream>
#include <opencv2/core.hpp>				 //types
#include <opencv2/imgcodecs.hpp>	 // read image
#include <dlib/image_processing.h> //shape_predictor
#include <opencv2/highgui.hpp>		 // display image in window

#include "Face_Recognition.hpp"

using namespace cv;
using namespace std;

int main(int argc, char const *argv[])
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

	// Tests start here!
	FaceRecognition *fr = new FaceRecognition();
	Mat result;
	int response;
	fr->verify(image, "-", response, result);

	// uncomment to show the image
	// namedWindow("image", WINDOW_AUTOSIZE);
	// imshow("image", result);
	// waitKey(0); // Wait for a keystroke in the window

	delete fr;
	return 0;
}
