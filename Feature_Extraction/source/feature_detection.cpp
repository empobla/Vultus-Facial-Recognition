#include "feature_detection.h"

FeatureDetection::FeatureDetection(string path){
    deserialize(path) >> net;
}

Mat FeatureDetection :: normalizeHist(Mat &m)
    { //Pre-defined formula that normalizes an input MAT
        Mat normalized;
        normalize( m, normalized, 0, 1, NORM_MINMAX, -1, Mat() );
        return normalized;
    }

double FeatureDetection :: compareFeatures(Mat &m , Mat &h, int n)
    {
        double result = 0;
        if(n == 5){
            result =  norm(m, h, NORM_L2);
        }else{
            result = compareHist(m, h, n);
        }

        return result;
    }

Mat FeatureDetection :: getFeatures2(Mat &m){
    if(m.channels() == 1){
        cout<<"the image was in grayscale and will be transformed to bgr format"<<endl;
        cv::cvtColor(m, m, cv::COLOR_GRAY2BGR); 
    }else if(m.channels() != 3){
        cout<<"this image was read in the incorrect format "<<endl;
    }

    dlib::matrix<dlib::rgb_pixel> dlibImage;
    dlib::assign_image(dlibImage, dlib::cv_image<bgr_pixel>(m));

     std::vector<dlib::matrix<dlib::rgb_pixel>> faces(1, dlibImage);

     dlib::matrix<float,128,1> face_descriptor = mean(mat(net(faces)));
     cv::Mat img = dlib::toMat(face_descriptor);
     return img.clone();

}