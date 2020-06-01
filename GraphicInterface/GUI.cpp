#include "Screens.h"
//g++ *.cpp -o output `pkg-config --cflags --libs opencv4`


using namespace std;

int main() {
    FaceRecognition *fr = new FaceRecognition();
    Screens * wOpener = new Screens(fr);
    wOpener->MainWindow();
    return 0;
}