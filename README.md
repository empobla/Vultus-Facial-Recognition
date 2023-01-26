<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Portfolio][moreinfo-shield]][moreinfo-url]
[![Contributors][contributors-shield]][contributors-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<div align="center">
<h3 align="center">Vultus Facial Recognition</h3>

  <p align="center">
    Vultus Facial Recognition is a C++ project to recognize members of Tecnológico de Monterrey CSF.
    <br />
    <br />
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#description">Description</a></li>
        <li><a href="#highlights">Highlights</a></li>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li><a href="#dependencies">Dependencies</a></li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li>
          <a href="#installation">Installation</a>
          <ul>
            <li><a href="#option-1-from-source">Option 1 (from source)</a></li>
            <li><a href="#option-2-docker">Option 2 (Docker)</a></li>
          </ul>
        </li>
      </ul>
    </li>
    <li>
      <a href="#usage">Usage</a>
      <ul>
        <li><a href="#gui">GUI</a></li>
        <li><a href="#verify">Verify</a></li>
        <li><a href="#identify">Identify</a></li>
        <li><a href="#enroll-user">Enroll User</a></li>
      </ul>
    </li>
    <li><a href="#tests">Tests</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

<div align="center">
  <a href='https://emilioppv.com/projects#vultus-facial-recognition'>
    <img alt="Vultus Screen Shot" src="./sample.gif" width="74%">
  </a>
</div>

A facial recognition access system that will grant access to registered users if their face is recognized, and will deny access to non-registered users. In addition, it comes with the functionality of registering new users to the database for future access.



### Description

* The system recognizes members of Tecnológico de Monterrey CSF.
* The system throws alerts in case the credential does not match the face.
* The system allows to authenticate (comparing) the data of the students with those of the credential.
* The system grants access if the data matches.
* The system shows an alert whether or not he/she is the person.
* The system allows the enrollment of new students.
* The system verifies or identifies the student.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Highlights

* The system runs in macOS (10.14+), Linux (Ubuntu 18.04+), (Windows not officially supported, but might work).
* Data in the system stays safe and secure.
* Written in C++.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

[![C++][C++]][C++-url]
[![OpenCV][OpenCV]][OpenCV-url]
[![Dlib][Dlib]][Dlib-url]
[![MongoDB][MongoDB]][Mongo-url]
[![CMake][CMake]][CMake-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- DEPENDENCIES -->
## Dependencies

This project uses the following dependencies:

* [OpenCV](https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html) for facial recognition.
* [Dlib](https://github.com/davisking/dlib) toolkit for several algorithms.
* [Mongocxx Driver](http://mongocxx.org/mongocxx-v3/installation/) for connecting to MongoDB using C++.
* [MongoDB](https://www.mongodb.com/download-center/community) for storing face data and users.
* [CMake](https://cmake.org/download/) for compiling.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple example steps.

### Prerequisites

This project requires that all of its dependencies are correctly installed before running.

To setup the database:
  1. Download the database info [here](https://drive.google.com/open?id=1wuv9Cy0vV7tKd2-CxW3BoRb9rgM2S2km)
  2. Decompress `ImgFiles.zip` and `MatFiles.zip`
  3. Substitute files in `Database/storage/`

### Installation

There must be a camera attached to the computer for the program to work fully.
<br />

_NOTE: To use the webcam you must run Vultus in Linux. The GUI works both in Linux and MacOS, however, you can only use the CLI if you are in Windows._

<br />

#### Option 1 (from source)
1. Clone the repo
   ```sh
   git clone https://github.com/empobla/Vultus-Facial-Recognition.git
   ```
2. Compile
   ```sh
   cd Vultus-Facial-Recognition && cd GraphicInterface && mkdir build && cd build && cmake .. && make
   ```
3. Run Vultus
   ```sh
   ./GraphicInterface
   ```

#### Option 2 ([Docker](https://hub.docker.com/repository/docker/robtry/face-recognition))
1. Pull the docker image
   ```sh
   docker pull robtry/face-recognition
   ```
2. Enable xhost ! (Mack & Linux)
   ```sh
   xhost +
   ```
3. Clone the repo
   ```sh
   git clone https://github.com/empobla/Vultus-Facial-Recognition.git
   ```
4. Run the container
    * Linux:
       ```sh
       docker run --privileged --device /dev/video0:/dev/video0 -v $(pwd):/root/workspace -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY -p 5000:5000 -p 8888:8888 -it robtry/face-recognition
       ```
    * MacOS:
       ```sh
       docker run -it -v $(pwd):/root/workspace -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=docker.for.mac.host.internal:0  -p 5000:5000 -p 8888:8888 robtry/face-recognition
       ```
5. Compile
   ```sh
   cd Vultus-Facial-Recognition && cd GraphicInterface && mkdir build && cd build && cmake .. && make
   ```
6. Run Vultus
   ```sh
   ./GraphicInterface
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

To better visualize how the GUI for Vultus works, you can reference this diagram:

![GUI Flow Diagram](./Flow_GUI.png)

In this section, you can find the main methods that the project uses alongside a description of what they do and how to use them.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### GUI

<figure>
  <img alt="GUI Code" src="./GUI.png">
  <figcaption><code>GUI.cpp</code></figcaption>
</figure>

`Screens.cpp`

Inside this script the menu buttons are displayed and the respective functions are executed once the button is pressed. The buttons and funtionalities of each are the following:

* **"Face Verification"**: Calls the main [Verify](#verify) method (full description below).
* **"Face identification"**: Calls the main [Identify](#identify) method (full description below).
* **"Enroll a Student"**: Calls the main [Enroll User](#enroll-user) method. Allows for a new user to be registered in the database. It requires the name, ID, age and picture of the before-mentioned user.
* **"Quit"**: Exits the program.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Verify

This method verifies if the subject in the frame matches the subject in the database for a given ID. It uses the `Face Detection`, `Face Alignment` and `Features Extraction` modules to get the features of the subject in the frame, and then uses the `Database` module to get the features saved for the given ID and compares both features.

##### Parameters

* **Frame** (`cv::Mat`): object of the frame captured.
* **ID** (`std::string`): ID.
* **Response** (`integer`): integer that will contain the response of the verification. 1 if it's the same person, 0 if not matched and -1 for method error.
* **Result** (`Cuatec`): Cuatec object that, if matched, will contain the matching Cuatec found in the DB.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Identify

This method unites the `Face Detection`, `Face Alignment`, `Feature Extraction` and `Database` modules into one. It identifies a face and returns an amount of possible matches for said face.

The Identify method begins by creating an empty Mat object called "features", which will be used as an argument along with the current frame when calling `getFeatureDescriptorsFromFrame()`. That method encapsulates the first three modules of this system (`Face Detection`, `Face Alignment` and `Feature Extraction`), takes "features" and "near_neighbors" as arguments and once all 3 modules have done their job, a boolean variable is returned. If the result is true, it means all 3 modules worked fine, so "result" will be filled with the possible matches to the face in the current frame via a call to `fastSearch()`. `fastSearch()` is a method provided by the `Database` module which takes as arguments the now filled "features" Mat object and "near_neighbors" (the amount of possible matches desired to be seen). 

Provided the first position inside of "result" will have the most likely match of the person being identified, a call is made to `verify()`, which will take as arguments the same received frame, the cuatecID of the first person in "result", a newly defined and initialized "verfiedResponse" integer and an object of type "Cuatec" named "cuatecRseult". The response value that comes from `verify()` will determine the value for "response". If its equal to 1, so is "response", and there was a match. If its equal to 0, so is "response", and there was no match. If the boolean returned from `getFeatureDescriptorsFromFrame()` was returned as false, the person using the system is notified through an "Error" message and "response" is saved as 0.

##### Parameters

* **Frame** (`cv::Mat`): a Mat object of the current frame being captured.
* **Response** (`integer`): an integer that will contain the response of the identification (1 for a match and 0 for no match).
* **Result** (`Cuatec[]`): a vector of type Cuatec that will save all the possible matches of the identification.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Enroll User

This methods allows the user to enroll a new student. In order to enroll a student, the method recieves the student's name (string), age (int), and id (string) as a unique key; while the Mat object comes from the picture taken by the opeaning camara. In order to insert the new user into the database, the picture must (1) detect the face to be inserted, (2) align the picture and (3) detect a 128-dimension vector with its features. We use the `getFeaturesDescriptorsFromFrame()` to determine its feature vector. The response parameter (int) from the function determines whether the insertion was successful (1) or unsuccesful (0).

##### Parameters

* **Age** (`integer`): an integer that is an input from the user.
* **Id** (`string`): a string recieved from the user, used as a key in the database.
* **Name** (`string`): a string that is an input from the user.
* **Response** (`integer`): an integer that indicates whether the student was successfully enrolled or not.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- Tests -->
## Tests

|  Method  | Windows  |   Mac    | Linux |
| :------: | :------: | :------: | :---: |
|  Verify  | untested | tested | tested |
| Identify | untested | tested | tested |
|  Enroll  | untested | tested | tested |

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- LICENSE -->
## License

_Copyright © 2020 ITESM CSF._ All rights are reserved. Modification or redistribution of this code must have _explicit_ consent from ITESM CSF or the project owners.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

- [Leonardo Chang](https://github.com/leonardochang36): Project Manager
- [Team 1](https://github.com/sergio-hernandez-castillo/FaceDetection) : Face Detection | One to Many comparison.
- [Team 2](https://github.com/robtry/face-alignment) : Face Alignment | Integration.
- [Team 3](https://github.com/cxrlos/Computer_Vision) : Feature Extraction | GUI.
- [Team 4](https://github.com/saulmontesdeoca/faceRecognitionDB) : Database | One to One comparison.

Project Link: [https://github.com/empobla/Vultus-Facial-Recognition](https://github.com/empobla/Vultus-Facial-Recognition)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/empobla/Vultus-Facial-Recognition.svg?style=for-the-badge
[contributors-url]: https://github.com/empobla/Vultus-Facial-Recognition/graphs/contributors
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/emilio-popovits

[C++]: https://img.shields.io/badge/c++-00599c?style=for-the-badge&logo=C%2B%2B&logoColor=ffffff
[C++-url]: https://isocpp.org
[OpenCV]: https://img.shields.io/badge/opencv-5c3ee8?style=for-the-badge&logo=opencv&logoColor=ffffff
[OpenCV-url]: https://opencv.org
[Dlib]: https://img.shields.io/badge/dlib-ffffff?style=for-the-badge&logo=dlib&logoColor=008000
[Dlib-url]: http://dlib.net
[MongoDB]: https://img.shields.io/badge/mongodb-ffffff?style=for-the-badge&logo=mongodb&logoColor=47a248
[Mongo-url]: https://www.mongodb.com
[CMake]: https://img.shields.io/badge/cmake-064f8c?style=for-the-badge&logo=cmake&logoColor=209849
[CMake-url]: https://cmake.org

[moreinfo-url]: https://emilioppv.com/projects#vultus-facial-recognition
[moreinfo-shield]: https://img.shields.io/badge/more%20info-1b1f24?style=for-the-badge&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAA4AAAAOCAMAAAAolt3jAAAABGdBTUEAALGPC/xhBQAAACBjSFJNAAB6JgAAgIQAAPoAAACA6AAAdTAAAOpgAAA6mAAAF3CculE8AAAApVBMVEUbHyQbHyQbHyRnam2sra+vsbKys7Wsrq+goqQwNDgaHyQaIilbXWGChIZMT1OYmpwYQFoaICYXRF8WUHQZLjwvMzdwcnaztLZ1d3pcX2IaICUXTG0WUHMXS2sXSGcWT3MaKjcpLTFVWFyFh4lTVllvcnWpqqwYOEwZM0QXTW4XTnAaJS8lKS3IycoYPlYaIyt4e36rra60tba5urutr7BQU1cAAAB8HBV3AAAAAnRSTlOR/KrCyFQAAAABYktHRDZHv4jRAAAACXBIWXMAAAsTAAALEwEAmpwYAAAAB3RJTUUH5wEZCiUZVutNzgAAAGpJREFUCNdjYGBkggNGBmQeiM+EAjC5zCwsrGzsHJwQLhc3ExMPLxMfP5OAIBODkLCIqBi/uASHpJS0jCyDnLyCopIyh4qqmrqGphYDk5Q2WLGOrh63PsgoA0NDI2NDE1PsFqFw0RyJ6gUAuK4HVipJCoQAAAAuelRYdGRhdGU6Y3JlYXRlAAAImTMyMDLWNTDUNTINMTSwMja3MjLVNjCwMjAAAEFRBQlQZi6pAAAALnpUWHRkYXRlOm1vZGlmeQAACJkzMjAy1jUw1DUyDTE0sDI2tzIy1TYwsDIwAABBUQUJeVmGIQAAAABJRU5ErkJggg==
