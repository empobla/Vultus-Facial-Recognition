#include "include/DBManagerInterface.h"

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
void DBManagerInterface::create(Cuatec cuatec)
{
    bsoncxx::oid _oid;
    // //WRITE yml to store
    std::string matRoute = "../storage/MatFiles/" + _oid.to_string() + ".xml.gz";
    std::string imgRoute = "../storage/ImgFiles/" + _oid.to_string() + ".xml.gz";
    cv::FileStorage featureStorage(matRoute, cv::FileStorage::WRITE | cv::FileStorage::FORMAT_YAML);
    cv::FileStorage imgStorage(imgRoute, cv::FileStorage::WRITE | cv::FileStorage::FORMAT_YAML);
    featureStorage << "data" << cuatec.getFeatures();
    imgStorage << "data" << cuatec.getImg();
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
                                         << "_id" << _oid
                                         << "nombre" << cuatec.getNombre()
                                         << "img" << imgRoute
                                         << "edad" << cuatec.getEdad()
                                         << "matricula" << cuatec.getMatricula()
                                         << "identificacionFacial" << matRoute
                                         << bsoncxx::builder::stream::finalize;

    bsoncxx::stdx::optional<mongocxx::result::insert_one> result =
        coll.insert_one(doc_value.view()); //Inserting Document
    std::cout << "Inserted " << result->inserted_id().get_oid().value.to_string() << std::endl;
    featureStorage.release();
    imgStorage.release();
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

//Update
void DBManagerInterface::updateName(std::string nombre, std::string nuevoNombre)
{
    coll.update_one(bsoncxx::builder::stream::document{} << "nombre" << nombre << bsoncxx::builder::stream::finalize,
                    bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document << "nombre" << nuevoNombre << bsoncxx::builder::stream::close_document
                                                         << bsoncxx::builder::stream::finalize);
}

void DBManagerInterface::updateMatricula(std::string matricula, std::string nuevaMatricula)
{
    coll.update_one(bsoncxx::builder::stream::document{} << "matricula" << matricula << bsoncxx::builder::stream::finalize,
                    bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document << "matricula" << nuevaMatricula << bsoncxx::builder::stream::close_document
                                                         << bsoncxx::builder::stream::finalize);
}

//Delete
void DBManagerInterface::deleteOne(std::string matricula)
{
    coll.delete_one(bsoncxx::builder::stream::document{} << "matricula" << matricula << bsoncxx::builder::stream::finalize);
}
cv::Mat DBManagerInterface::readFeatures(std::string matricula)
{
    cv::Mat m;
    bsoncxx::stdx::optional<bsoncxx::document::value> doc =
        coll.find_one(bsoncxx::builder::stream::document{} << "matricula" << matricula
                                                           << bsoncxx::builder::stream::finalize);
    bsoncxx::document::view view = doc->view();
    auto matString = view["identificacionFacial"][0].get_utf8().value.to_string();
    std::cout << matString << std::endl;
    cv::FileStorage fs(matString, cv::FileStorage::READ);
    fs["data"] >> m;
    fs.release();
    return m;
};