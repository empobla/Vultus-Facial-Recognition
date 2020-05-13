#include "include/DBManagerInterface.hpp"

DBManagerInterface::DBManagerInterface(std::string uri, std::string database, std::string collection)
{
    mongocxx::instance instance{};
    // mongocxx::client conn{mongocxx::uri{}};
    conn = mongocxx::uri{uri};
    //Seleccionando la base de datos Cuatecs
    db = conn[database];
    //Seleccionando la coleccion
    coll = db[collection];
}

DBManagerInterface::~DBManagerInterface()
{
}
//Create
int DBManagerInterface::create(Cuatec cuatec)
{
    // //WRITE yml to store
    std::string matRoute = "../storage/MatFiles/" + cuatec.getMatricula() + ".xml.gz";
    std::string imgRoute = "../storage/ImgFiles/" + cuatec.getMatricula() + ".xml.gz";

    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
                                         << "nombre" << cuatec.getNombre()
                                         << "img" << imgRoute
                                         << "edad" << cuatec.getEdad()
                                         << "matricula" << cuatec.getMatricula()
                                         << "identificacionFacial" << matRoute
                                         << bsoncxx::builder::stream::finalize;

    bsoncxx::stdx::optional<mongocxx::result::insert_one> result = coll.insert_one(doc_value.view()); //Inserting Document

    if (result->result().inserted_count() != 1)
    {
        return 0;
    }
    else
    {
        cv::FileStorage featureStorage(matRoute, cv::FileStorage::WRITE | cv::FileStorage::FORMAT_YAML);
        cv::FileStorage imgStorage(imgRoute, cv::FileStorage::WRITE | cv::FileStorage::FORMAT_YAML);
        featureStorage << "data" << cuatec.getFeatures();
        imgStorage << "data" << cuatec.getImg();
        featureStorage.release();
        imgStorage.release();
        return 1;
    }
}
int DBManagerInterface::create(std::string name, int age, std::string matricula1, cv::Mat imgMat, cv::Mat featuresMat)
{
    // //WRITE yml to store
    std::string matRoute = "../storage/MatFiles/" + matricula1 + ".xml.gz";
    std::string imgRoute = "../storage/ImgFiles/" + matricula1 + ".xml.gz";

    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
                                         << "nombre" << name
                                         << "img" << imgRoute
                                         << "edad" << age
                                         << "matricula" << matricula1
                                         << "identificacionFacial" << matRoute
                                         << bsoncxx::builder::stream::finalize;

    bsoncxx::stdx::optional<mongocxx::result::insert_one> result = coll.insert_one(doc_value.view()); //Inserting Document

    if (result->result().inserted_count() != 1)
    {
        return 0;
    }
    else
    {
        cv::FileStorage featureStorage(matRoute, cv::FileStorage::WRITE | cv::FileStorage::FORMAT_YAML);
        cv::FileStorage imgStorage(imgRoute, cv::FileStorage::WRITE | cv::FileStorage::FORMAT_YAML);
        featureStorage << "data" << featuresMat;
        imgStorage << "data" << imgMat;
        featureStorage.release();
        imgStorage.release();
        return 1;
    }
}

//Read
void DBManagerInterface::readAll()
{
    mongocxx::cursor cursor = coll.find({});
    for (auto doc : cursor)
    {
        std::cout << bsoncxx::to_json(doc) << "\n";
    }
}

Cuatec DBManagerInterface::readOne(std::string matricula)
{
    bsoncxx::stdx::optional<bsoncxx::document::value> doc =
        coll.find_one(bsoncxx::builder::stream::document{} << "matricula" << matricula
                                                           << bsoncxx::builder::stream::finalize);
    bsoncxx::document::view view = doc->view();
    std::string nombre = view["nombre"].get_utf8().value.to_string();
    int edad = view["edad"].get_int32(); //Checar
    cv::Mat imgMat;
    auto imgMatString = view["img"].get_utf8().value.to_string();
    cv::FileStorage fs(imgMatString, cv::FileStorage::READ);
    fs["data"] >> imgMat;
    fs.release();
    cv::Mat featuresMat;
    auto featuresMatString = view["identificacionFacial"].get_utf8().value.to_string();
    cv::FileStorage fs2(featuresMatString, cv::FileStorage::READ);
    fs2["data"] >> featuresMat;
    fs2.release();
    Cuatec cuatec(nombre, edad, matricula, imgMat, featuresMat);
    return cuatec;
}

std::string DBManagerInterface::readOid(std::string matricula)
{
    bsoncxx::stdx::optional<bsoncxx::document::value> doc =
        coll.find_one(bsoncxx::builder::stream::document{} << "matricula" << matricula
                                                           << bsoncxx::builder::stream::finalize);
    bsoncxx::document::view view = doc->view();
    bsoncxx::document::element id_ele = view["_id"];
    std::string oid = id_ele.get_oid().value.to_string();
    return oid;
};
std::string DBManagerInterface::readOneName(std::string matricula)
{
    bsoncxx::stdx::optional<bsoncxx::document::value> doc =
        coll.find_one(bsoncxx::builder::stream::document{} << "matricula" << matricula
                                                           << bsoncxx::builder::stream::finalize);
    bsoncxx::document::view view = doc->view();
    std::string name = view["nombre"].get_utf8().value.to_string();
    return name;
}
int DBManagerInterface::readOneEdad(std::string matricula)
{
    bsoncxx::stdx::optional<bsoncxx::document::value> doc =
        coll.find_one(bsoncxx::builder::stream::document{} << "matricula" << matricula
                                                           << bsoncxx::builder::stream::finalize);
    bsoncxx::document::view view = doc->view();
    int edad = view["edad"].get_int32();
    return edad;
}
cv::Mat DBManagerInterface::readOneFeatures(std::string matricula)
{
    cv::Mat m;
    std::string matString = "../storage/MatFiles/" + matricula + ".xml.gz";
    cv::FileStorage fs(matString, cv::FileStorage::READ);
    fs["data"] >> m;
    fs.release();
    if (m.empty())
    {
        std::cout << "No features saved for " + matricula << std::endl;
    }
    return m;
};
cv::Mat DBManagerInterface::readOneImg(std::string matricula)
{
    cv::Mat m;
    std::string matString = "../storage/ImgFiles/" + matricula + ".xml.gz";
    cv::FileStorage fs(matString, cv::FileStorage::READ);
    fs["data"] >> m;
    fs.release();
    if (m.empty())
    {
        std::cout << "No Img saved for " + matricula << std::endl;
    }
    return m;
};

//Update
int DBManagerInterface::updateName(std::string matricula, std::string nuevoNombre)
{
    auto updated = coll.update_one(bsoncxx::builder::stream::document{} << "matricula" << matricula << bsoncxx::builder::stream::finalize,
                                   bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document << "nombre" << nuevoNombre << bsoncxx::builder::stream::close_document
                                                                        << bsoncxx::builder::stream::finalize);
    if (updated->result().upserted_count() != 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int DBManagerInterface::updateMatricula(std::string matricula, std::string nuevaMatricula)
{
    auto updated = coll.update_one(bsoncxx::builder::stream::document{} << "matricula" << matricula << bsoncxx::builder::stream::finalize,
                                   bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document << "matricula" << nuevaMatricula << bsoncxx::builder::stream::close_document
                                                                        << bsoncxx::builder::stream::finalize);
    if (updated->result().upserted_count() != 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

//Delete
int DBManagerInterface::deleteOne(std::string matricula)
{
    auto result = coll.delete_one(bsoncxx::builder::stream::document{} << "matricula" << matricula << bsoncxx::builder::stream::finalize);
    if (result->deleted_count() != 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
std::vector<cv::Mat> DBManagerInterface::fastSearch(cv::Mat featuresMat, int nearestNeighbors)
{

    cv::flann::Index flann_index(,
                                 cvflann::SavedIndexParams("c:\\index.fln"),
                                 cvflann::FLANN_DIST_EUCLIDEAN);
    std::vector<cv::Mat> knnMatches;
    return knnMatches;
}
