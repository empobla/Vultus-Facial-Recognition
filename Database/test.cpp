#include "src/DBManagerInterface.cpp"

using namespace cv;
using namespace std;

int main()
{
    //Example of mat
    //Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));

    //------------------ Class Cuatec ---------------------
    //Cuatec receives name(string), age(int), matricula(string),
    // image from TecId(cv::Mat) and features(cv::Mat)
    //Cuatec nuevoCatec("Saul Montes De Oca", 22, "A01025975", M, M);

    //Getters
    // string nombre = nuevoCatec.getNombre();
    // string matricula = nuevoCatec.getMatricula();
    // int edad = nuevoCatec.getEdad();
    // Mat img = nuevoCatec.getImg();
    // Mat features = nuevoCatec.getFeatures();

    //Setters
    //nuevoCatec.setNombre(string nuevoNombre);
    //nuevoCatec.setMatricula(string nuevoMatricula);
    //nuevoCatec.setEdad(int nuevaEdad);
    //nuevoCatec.setImg(Mat nuevaImagen);
    //nuevoCatec.setFeatures(Mat nuevoFeatures);

    //You need to instance de class once like this:
    //DBManagerInterface dbManager(URI, DATABASE, COLLECTION);

    //Methods:

    //-------------------- Create ------------------------
    //Create method receives a Cuatec object
    //dbManager.create(nuevoCatec);

    //-------------------- Read ------------------------
    //Prints all the data (JSON format)
    //dbManager.readAll();
    //Returns a Cuatec object found in the DB
    //Cuatec nuevoCuatec = dbManager.readOne("A01021111");
    //Returns ObjectId (string format) by matricula
    //std::string oid = dbManager.readOid("A01021111");

    //-------------------- Update ------------------------
    //Updates name old(string) -> to new one(string)
    //dbManager.updateName("Luis Garcia ","Victor Coeto");
    //Updates matricula old(string) -> to new one(string)
    //dbManager.updateMatricula("A01021111", "A01025986");

    //-------------------- Delete ------------------------
    //Delete by name
    //dbManager.deleteOne("Victor Coeto");

    return 0;
}