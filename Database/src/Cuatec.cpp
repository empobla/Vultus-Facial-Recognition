#include "include/Cuatec.h"

Cuatec::Cuatec(std::string name, int age, std::string matricula1, cv::Mat imgMat, cv::Mat featuresMat)
{
    nombre = name;
    edad = age;
    matricula = matricula1;
    img = imgMat;
    features = featuresMat;
}
Cuatec::~Cuatec()
{
}

//Getters
std::string Cuatec::getNombre()
{
    return nombre;
}
int Cuatec::getEdad()
{
    return edad;
}
std::string Cuatec::getMatricula()
{
    return matricula;
}
cv::Mat Cuatec::getImg()
{
    return img;
}
cv::Mat Cuatec::getFeatures()
{
    return features;
}
//Setters
void Cuatec::setNombre(std::string nombre)
{
    nombre = nombre;
}
void Cuatec::setEdad(int edad)
{
    edad = edad;
}
void Cuatec::setMatricula(std::string matricula)
{
    matricula = matricula;
}
void Cuatec::setImg(cv::Mat &img)
{
    img = img;
}
void Cuatec::setFeatures(cv::Mat &features)
{
    features = features;
}