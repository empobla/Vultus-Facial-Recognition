#ifndef MODULE_ONE_HPP
#define MODULE_ONE_HPP

#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

class Module1 {
	const static string FACEMODEL;
	public:
	/**
	 * return vector of Rect with ROI of possible faces
	*/
	static void detectFaces(vector<Rect> &faces, const Mat image);
};

#endif