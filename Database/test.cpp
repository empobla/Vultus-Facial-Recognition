#include "src/include/DBManagerInterface.hpp"

using namespace cv;
using namespace std;

int main()
{
    //Example of mat
    // Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));

    //------------------ Class Cuatec ---------------------
    //Cuatec receives name(string), age(int), matricula(string),
    // image from TecId(cv::Mat) and features(cv::Mat)
    // Cuatec nuevoCuatec("Sal Montesdeoca", 22, "A01025975", M, M);

    //Getters
    // string nombre = nuevoCuatec.getNombre();
    // string matricula = nuevoCuatec.getMatricula();
    // int edad = nuevoCuatec.getEdad();
    // Mat img = nuevoCuatec.getImg();
    // Mat features = nuevoCuatec.getFeatures();

    //Setters
    //nuevoCuatec.setNombre(string nuevoNombre);
    //nuevoCuatec.setMatricula(string nuevoMatricula);
    //nuevoCuatec.setEdad(int nuevaEdad);
    //nuevoCuatec.setImg(Mat nuevaImagen);
    //nuevoCuatec.setFeatures(Mat nuevoFeatures);

    //You need to instance de class once like this:
    // DBManagerInterface dbManager(URI, DATABASE, COLLECTION);

    //Methods:

    //-------------------- Create ------------------------
    /* 
        Create method can either receive a Cuatec object
        or receive (std::string name, int age, std::string matricula,
        cv::Mat image, cv::Mat features)
        Returns int:
            0 for failed insertion
            1 for succeed insertion
    */
    // int created = dbManager.create("wicho Garcia", 22, "A01025555", M, M);
    // int created = dbManager.create(nuevoCuatec);

    //-------------------- Read ------------------------
    //Prints all the data (JSON format)
    //dbManager.readAll(); //Not recomended for bigdata

    //Returns a Cuatec object found in the DB
    //Cuatec nuevoCuatec = dbManager.readOne("A01021111");

    //Returns ObjectId (string format)
    // string oid = dbManager.readOid("A01025975");

    //Returns name as string
    // string nombre = dbManager.readOneName("A01025975");

    //Returns age as int
    // int edad = dbManager.readOneEdad("A01025975");

    //Returns features as cv::Mat
    // Mat features = dbManager.readOneFeatures("A01025555");

    //Returns img as cv::Mat
    // Mat img = dbManager.readOneImg("A01025555");

    //-------------------- Update ------------------------
    //Receives matricula of object to update and new name
    //Returns:
    //0 for failing at updating
    //1 for suceeding at updating
    //int updated = dbManager.updateName("A01025975","Victor Coeto");

    //Receives matricula of object to update and new matricula
    //Returns:
    //0 for failing at updating
    //1 for suceeding at updating
    //int updated = dbManager.updateMatricula("A01021111", "A01025986");

    //-------------------- Delete ------------------------
    //Receives matricula of object to delete
    //Returns:
    //0 for failing at deleting
    //1 for suceeding at deleting
    // int result = dbManager.deleteOne("A01025975"); //falta borrar xmls guardados

    return 0;
}