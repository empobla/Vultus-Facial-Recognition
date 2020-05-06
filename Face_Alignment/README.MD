# Face Alignment

## How to use 

Just copy the foler `src/faceAlignment` and `models` to your project. Then in you `main.cpp`

```c++
#include "faceAlignment/align.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
  //something important here
  // detect face areas ...

  // 
  /**
   * option 1
   * note: if initialized like this, the method will assume is in build folder
   * the go ../models/ to find shape_predictor_5_face_landmarks.dat
  */
  FaceAlignment align;

  // option 2
  /**
   * You can pass the path to one of two models
   * shape_predictor_5_face_landmarks.dat
   * shape_predictor_68_face_landmarks.dat
   * FaceAlignment align("<some_path>/shape_predictor_68_face_landmarks.dat");
   FaceAlignment align("<some_path>/shape_predictor_5_face_landmarks.dat");
  */

  //store result, aligned face
  Mat result;

  for ( size_t i = 0; i < faces.size(); i++ )
  {
    /*
     * This should be used in production
    */
    //aling.alignFace(image, faces[i], 200, result);

    /*
     * This should be user to get log information
    */
    //aling.alignFaceDebugMode(image, faces[i], 150, result, false);

    /*
     * This should be use if you want to see the final result
    */
    aling.alignFaceDebugMode(image, faces[i], 150, result, true);
  }

  return 0;
}
```

## Tests

| Case | Time (ms) |
|------|-----------|
| 1    | 4         |
| 2    | 2         |
| 3    | 2         |
| 4    | 4         |
| 5    | 1         |
| 6    | 2         |
| 7    | 1         |
| 8    | 2         |

Avg: 2.25 ms


### Dependencies

- [opencv](https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html)
- [dlib](https://github.com/davisking/dlib)

### Compile

```sh
# using cmake
mkdir build
cd build
cmake ..
make
./FaceAlignment <img>
```

## Development

- You have to install [opencv](https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html), if you do not want to mess your computer up with extra libraries and environments use docker:

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

*note: for more information you can see [this tutorial](https://youtu.be/NryxTs2OYPI)*

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

## Authors:

[Roberto Gervacio](https://github.com/robtry)

[Jorge Palacios](https://github.com)

[Diego moreno](https://github.com/Diego212)

## To Do

- [x] Review 1 - Add constructuctors, use dlib, avoid loading the model every call
- [x] Review 2 - Use dlib methods to align
