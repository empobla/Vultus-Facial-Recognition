#include <iostream>
#include <opencv2/core.hpp>		   //types
#include <opencv2/imgcodecs.hpp>   // read image
#include <dlib/image_processing.h> //shape_predictor
#include <opencv2/highgui.hpp>	   // display image in window
#include <chrono>

#include "Face_Recognition.hpp"

using namespace cv;
using namespace std;
using namespace std::chrono;

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
	FaceRecognition *fr = new FaceRecognition(0.5, 10);

	// Test for identify() T1
	int identifyResponse;
	std::vector<Cuatec> identifyResult;

	auto start = high_resolution_clock::now(); 
    fr->identify(image, identifyResponse, identifyResult);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
	cout << "\nExecution time for identification: " << duration.count() << " microseconds." << endl;
	
	if (identifyResponse == 1)
	{
		// Matched the face
		cout << "Face matched..." << endl;
		for (int i = 0; i < identifyResult.size(); i++)
		{
			cout << "-" + identifyResult[i].getNombre() << endl;
		}
	}
	else if (identifyResponse == 0)
	{
		// Could not match the face
		cout << "Face not matched." << endl;
		return -1;
	}
	else
	{
		cout << "Error: Something went wrong in the identification process." << endl;
		return -1;
	}

	// //Test for verification method T4
	// Cuatec cuatecResponse;
	// int queryResponse;

	// auto start = high_resolution_clock::now(); 
    // fr->verify(image, "T01020001", queryResponse, cuatecResponse);
    // auto stop = high_resolution_clock::now();

    // auto duration = duration_cast<microseconds>(stop - start);
	// cout << "\nExecution time for verification: " << duration.count() << " microseconds." << endl;

	// if (queryResponse == 1)
	// {
	// 	//Cuatec matched
	// 	std::cout << "Cuatec matched, showing image..." << std::endl;
	// 	imshow("Cuatec", cuatecResponse.getImg());
	// 	waitKey();
	// }
	// else if (queryResponse == 0)
	// {
	// 	//Cuatec not matched
	// 	std::cout << "Cuatec not matched." << std::endl;
	// }
	// else
	// {
	// 	//Cuatec matched
	// 	std::cout << "Something went wrong! :(" << std::endl;
	// }

	//Test for enroll student T3
	// int verify = 0;
	// fr->enrollStudent(image, "T01020013", "Elon Musk", 48, verify);
	// if (verify == 1)
	// {
	// 	std::cout << "student enrolled succesfully " << std::endl;
	// }
	//Test for identify
	// int response = 0;
	// std::vector<Cuatec> result;
	// fr->identify(image, response, result);
	// Cuatec firstResult = result[0];
	// imshow("image", firstResult.getImg());
	// waitKey(0);
	// for(int i = 0; i < result.size(); i++){
	// 	Cuatec firstResult = result[i];
	// 	imshow("image", firstResult.getImg());
	// 	waitKey(0);
	// }

	// uncomment to show the image
	// namedWindow("image", WINDOW_AUTOSIZE);
	// imshow("image", result);
	// waitKey(0); // Wait for a keystroke in the window

	delete fr;
	return 0;
}
