#ifndef CUATEC_H
#define CUATEC_H

class Cuatec
{
public:
    std::string nombre;
    int edad;
    std::string matricula;
    cv::Mat img;
    cv::Mat features;
    Cuatec(std::string name, int age, std::string matricula1, cv::Mat imgMat, cv::Mat featuresMat);
    ~Cuatec();
    std::string getNombre();
    int getEdad();
    std::string getMatricula();
    cv::Mat getImg();
    cv::Mat getFeatures();
    void setNombre(std::string nombre);
    void setEdad(int edad);
    void setMatricula(std::string matricula);
    void setImg(cv::Mat &img);
    void setFeatures(cv::Mat &features);
};

#endif