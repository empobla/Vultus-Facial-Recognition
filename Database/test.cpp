#include "DBManagerInterface.cpp"

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

int main()
{
    //You need to instance de class once like this:
    //DBManagerInterface dbManager(URI, DATABASE, COLLECTION);

    //Methods:

    //-------------------- Create ------------------------

    //Create method receives the name(string), age(int), matricula(string),
    // image from TecId(cv::Mat) and features(cv::Mat)
    //dbManager.create("cmake", 11, "cmake", m2, m);

    //-------------------- Read ------------------------
    //Prints all the data (JSON format)
    //dbManager.readAll();
    //Prints object by matricula
    //dbManager.readOne("A01021111");
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