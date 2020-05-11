#include "../Database/src/DBManagerInterface.cpp"
#include "../Feature_Extraction/source/feature_detection.cpp"

int main(int argc, char *argv[])
{
    DBManagerInterface dbManager(URI, DATABASE, COLLECTION);
    FeatureDetection *d = new FeatureDetection("net/dlib_face_recognition_resnet_model_v1.dat");

    Mat img;
    double final_result = 0;
    double acceptance_rate = 0.5;

    // Check if images were loaded as arguments when running
    if (argc >= 2)
    {
        // Read images as rgb
        img = imread(argv[1], 1);

        // Check if image path found
        if (!img.data)
        {
            cout << "Img not found, try again" << endl;
            return -1;
        }
    }
    else
    {
        cout << "This program requires 1 image1, less than 1 images where sent" << endl;
        return -1;
    }

    //Getting features
    Mat features = d->getFeatures2(img);

    Cuatec nuevoCatec("Victor Coeto", 22, "A01024444", img, features);

    //DBManagerInterface dbManager(URI, DATABASE, COLLECTION);

    return 0;
}