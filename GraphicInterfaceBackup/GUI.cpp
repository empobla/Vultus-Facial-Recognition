#include "Screens.h"
//g++ *.cpp -o output `pkg-config --cflags --libs opencv4`


using namespace std;

int main() {
    Screens * wOpener = new Screens();

    wOpener->MainWindow();
    return 0;
}