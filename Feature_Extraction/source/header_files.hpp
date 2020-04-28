/**********************************************************************************************
 * Carla Pérez Gavilán, A01023033
 * Alejandra Nissan, A01024682
 * Carlos García, A01025948
 
Library that contains the function that returns the Local Binary Pattern for a given input
***********************************************************************************************/

#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <opencv2/imgcodecs.hpp>
#include "elbp.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <chrono>
#include <fstream>
#include <limits>
#include <dlib/image_processing.h>
#include <dlib/opencv/cv_image.h>
#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/opencv.h>
#include <dlib/image_transforms.h>




