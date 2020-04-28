# Face Alignment
## Start:

```sh
# Get the image
docker pull https://hub.docker.com/repository/docker/robtry/opencv-420

# Enable xhost !
xhost +

# Linux
docker run --privileged --device /dev/video0:/dev/video0 -v $(pwd):/root/workspace -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY -p 5000:5000 -p 8888:8888 -it robtry/opencv-420

# Mac
sudo docker run -it -v $(pwd):/root/workspace -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=docker.for.mac.host.internal:0  -p 5000:5000 -p 8888:8888 robtry/opencv-420
```

## Compile

You can follow one the next options:

```sh
#inside docker | only opencv
g++ <file>.cpp `pkg-config --cflags --libs opencv4`
```

Compiling using dlib

```sh
# use cmake
```

### Compile the module

*note:* In `models` folder you need to download and extract the model, you can find the link in `models/_download.txt`

```sh
# using cmake
# inside docker, you don't need to download dlib repo
mkdir build
cd build
cmake ..
make
./FaceAlignment <img>
```

## Autocomplete in vscode:

```sh
# AUTOCOMPLETE OPENCV
# from docker to this workspace
cd ~/workspace/
cp -r /usr/include/opencv4/ .

# AUTOCOMPLETE DLIB
# from docker to this workspace
cd /opt/
git clone https://github.com/davisking/dlib
cd ~/workspace/
cp -r /opt/dlib/dlib/ .
```

Then add to configuration file:

```json
"configurations": [
  {
    "includePath": [
      "${workspaceFolder}/**",
      "${workspaceFolder}/opencv4/"
    ],
  }
```

## How to use 

Just copy the foler `src/faceAlignment` to your project. Then in you `main.cpp`

```c++
#include "faceAlignment/align.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  //something important here
  //...


  //Aling face

  // option 1
  /**
   * note: if initialized like this the method will assume is in build folder
   * the go ../models/ to find shape_predictor_5_face_landmarks.dat
  */
  FaceAlignment aling;

  // option 2
  /**
   * You can pass the path to one of two models
   * shape_predictor_5_face_landmarks.dat
   * shape_predictor_68_face_landmarks.dat
  */
  //FaceAlignment aling("<some_path>/shape_predictor_68_face_landmarks.dat");

	//store result
	Mat result;

  for ( size_t i = 0; i < faces.size(); i++ )
  {
    //aling.alignFace(image, faces[i], 200, result);
    //aling.alignFaceDebugMode(image, faces[i], 150, result, false);
    aling.alignFaceDebugMode(image, faces[i], 150, result, true);
  }

  return 0;
}
```

## Authors:

[Roberto Gervacio](https://github.com/robtry)

[Jorge Palacios](https://github.com)

## To Do

- [x] Review 1 - Add constructuctors, use dlib, avoid loading the model every call
- [x] Review 2 - Use dlib methods to align
