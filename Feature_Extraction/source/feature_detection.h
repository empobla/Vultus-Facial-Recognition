#ifndef FEATURE_DETECTION_H
#define FEATURE_DETECTION_H


#include "header_files.hpp"
#include "network.h"


class FeatureDetection{
    private:
    anet_type net;

    public:
    FeatureDetection(string path);

    Mat getFeatures(Mat &m, string name);
    
    Mat normalizeHist(Mat &m);

    double compareFeatures(Mat &m , Mat &h, int method);

    Mat getFeatures2(Mat &m);

};


#endif