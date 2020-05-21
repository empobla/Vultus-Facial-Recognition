/*
Code written by Alejandra Nissan, Carla Perez and Carlos Garcia
Tecnologico de Monterrey, Santa Fe

Main code
*/

#include "Screens.h"
using namespace std;

int main() {
    FaceRecognition *fr = new FaceRecognition(0.5);
    Screens * wOpener = new Screens(fr);
    wOpener->MainWindow();
    return 0;
}