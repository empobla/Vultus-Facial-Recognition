# TC2004-FaceRecognition-Spring2020

**Face Recognition System** is a C++ project to recognize members of Tecnológico de Monterrey CSF

## Requirements

### Functional 
- The system will recognize members of Tecnológico de Monterrey CSF.
- The system throws alerts in case the credential does not match the face.
- The system allows to authenticate (comparing) the data of the students with those of the credential.
- The system will grant access if the data match.
- The system will show an alert whether or not he is the person.
- The system allows to enroll new students.
- The system should either verify or identify the student.



### Non Functional
- The system must run in Mac OS (10.14 +), Windows 10 + and Linux (Ubuntu 18.04 +)
- The result must be given under 1 second
- The system is planned to be delivered by June 8th
- The name of the system: <name>
- Data must stay safe and secure

## Dependencies

- [OpenCV](https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html)
- [Dlib](https://github.com/davisking/dlib)
- [Mongocxx Driver](http://mongocxx.org/mongocxx-v3/installation/)
- [MongoDB](https://www.mongodb.com/download-center/community)
- [CMake](https://cmake.org/download/)

## Install

```sh
git clone https://github.com/leonardochang36/TC2004-FaceRecognition-Spring2020.git

cd TC2004-FaceRecognition-Spring2020 && GraphicInterface && mkdir build && cmake .. && make

./GUI
```

## How to use

### GUI

### Verify

### Identify

### Enroll user


*Copyright © 2020 ITESM CSF*
