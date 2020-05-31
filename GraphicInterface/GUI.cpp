#include "Screens.h"
//g++ *.cpp -o output `pkg-config --cflags --libs opencv4`


using namespace std;

int main() {
    FaceRecognition *fr = new FaceRecognition(0.5);
    Screens * wOpener = new Screens(fr);
    //wOpener->MainWindow();
    wOpener->Init();
    return 0;
}