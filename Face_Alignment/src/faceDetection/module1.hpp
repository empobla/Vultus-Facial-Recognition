#ifndef MODULE_ONE_HPP
#define MODULE_ONE_HPP

#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

class Module1 {
	string FACEMODEL;
	public:
	Module1(const string path);
	/**
	 * return vector of Rect with ROI of possible faces
	*/
	void detectFaces(vector<Rect> &faces, const Mat image);
};

#endif