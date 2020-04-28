#include "feature_detection.h"

using namespace std::chrono;

int main(int argc, char* argv[]){

    FeatureDetection *d = new FeatureDetection("net/dlib_face_recognition_resnet_model_v1.dat"); 

    string path = "test_images/"; 
    
    Mat input;
    Mat input2;
    double final_result = 0;
    double acceptance_rate = 0.5;
    
    // Check if images were loaded as arguments when running
    if(argc >= 3)
    {
        // Read images as rgb
        input = imread(path+argv[1], 1);
        input2 = imread(path+argv[2], 1);

        // Check if image path found 
        if(!input.data || !input2.data)
        {
            cout<<"One or both images where not found, try again"<<endl;
            return -1;
        }   
    }
    else
    {
        cout<<"This program requires 2 images, less than 2 images where sent"<<endl;
        return -1;
    }

    //Display images as windows
    imshow("first picture", input);
    imshow("second picture", input2);

    // Get feature descriptor with dlib
    Mat result = d->getFeatures2(input);
    Mat result2 = d->getFeatures2(input2);
   
    // Calculate comparison between two descriptors with euclidian distance and measure time it takes to run
    auto time_before = high_resolution_clock::now();
    final_result = d->compareFeatures(result, result2, 5);
    auto time_after = high_resolution_clock::now();

    // Print result 
     cout<<" EUCLIDIAN DISTANCE -->  "<<final_result<<endl;

    // If difference is smaller than acceptance rate it is same person
     if(cv::abs(final_result)<=acceptance_rate)
     {
         cout<<"Same person"<<endl;
     }
     else
     {
         cout<<"Different person"<<endl;
     }

    cout<<"TIME COMPARISON IN NANOSECONDS --> "<<duration_cast<nanoseconds>(time_after-time_before).count()<<endl;
    

    
    waitKey(0);

    return 0;
}
