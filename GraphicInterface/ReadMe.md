# Graphical Interface
## Authors:
[Alejandra Nissan](https://github.com/AlejandraNissan) <br/>
[Carla Pérez](https://github.com/CarlaPerezGavilan) <br/>
[Carlos García](https://github.com/cxrlos)

## Description
Graphical User Interface that allows an easy access to the system's functions.

## Sections

## Instructions for Standalone Testing
### Docker installation
Install Docker on the desired platform, open the terminal (and open the application for Windows and OSX) and input the following command:

```sudo docker pull robtry/face-recognition```

This command will install the adequate container in order to run the program without the need to manually install the libraries and dependencies required. After the download is completed, clone or download the files from the repository. Open a terminal or command prompt, change the directory using the `cd` command to the download location. 

### Compilation with CMake and Make
If the program is intended to run on a OSX or Linux system it's necessary to input the `xhost +` command. After all of this is done, input the following commands:

```
sudo docker run -it --name opencv --privileged --device /dev/video0:/dev/video0 -v $(pwd):/root/workspace -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY -p 5000:5000 -p 8888:8888 robtry/face-recognition
cd workspace/GraphicInterface
mkdir build
cd build 
cmake ..
make

```
After these commands your program must be compiled and linked to an executable file.

### Running the code
Locate the file *GraphicInterface* inside the build directory and run the program by using the following command in the terminal or command prompt.

```./GraphicInterface```

***NOTE:*** There must be a camera attached to the computer for the program to work fully.