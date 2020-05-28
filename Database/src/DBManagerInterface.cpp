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
    //Constructing features index
    index = cv::flann::Index();
    createIndex();
}

DBManagerInterface::~DBManagerInterface()
{
}
//Create
int DBManagerInterface::create(Cuatec cuatec)
{
    // //WRITE yml to store
    std::string matRoute = "../../Database/storage/MatFiles/" + cuatec.getMatricula() + ".xml.gz";
    std::string imgRoute = "../../Database/storage/ImgFiles/" + cuatec.getMatricula() + ".xml.gz";

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
        cv::FileStorage featureStorage(matRoute, cv::FileStorage::WRITE | cv::FileStorage::FORMAT_XML);
        cv::FileStorage imgStorage(imgRoute, cv::FileStorage::WRITE | cv::FileStorage::FORMAT_XML);
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
    std::string matRoute = "../../Database/storage/MatFiles/" + matricula1 + ".xml.gz";
    std::string imgRoute = "../../Database/storage/ImgFiles/" + matricula1 + ".xml.gz";

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
        cv::FileStorage featureStorage(matRoute, cv::FileStorage::WRITE | cv::FileStorage::FORMAT_XML);
        cv::FileStorage imgStorage(imgRoute, cv::FileStorage::WRITE | cv::FileStorage::FORMAT_XML);
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
    std::string matString = "../../Database/storage/MatFiles/" + matricula + ".xml.gz";
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
    std::string matString = "../../Database/storage/ImgFiles/" + matricula + ".xml.gz";
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
// 🔧 fast search in construction
std::vector<Cuatec> DBManagerInterface::fastSearch(cv::Mat query, int nearestNeighbors)
{
    createIndex();
    //Declaring mat objects for results
    cv::Mat indices, dists;
    //knn-searching  O(logN+logM)
    // std::cout << query.t() << std::endl;
    index.knnSearch(query.t(), indices, dists, nearestNeighbors);
    //Declaring Cuatec vector to store search results
    std::vector<Cuatec> knnMatches;
    //Declaring temporary Cuatec object that will store Cuatecs received by the iteration
    Cuatec temp;
    for (size_t i = 0; i < nearestNeighbors; i++)
    {
        temp = readOne(matriculaIndex[indices.at<int>(i)]);
        knnMatches.push_back(temp);
    }
    std::cout << indices << std::endl;
    std::cout << dists << std::endl;
    return knnMatches;
}
// 🔧 index in construction
void DBManagerInterface::createIndex()
{
    //Declaring dataset mat object to append all existing features in DB
    cv::Mat dataset;
    //Declaring temporary mat object where feature results are  going to be placed
    cv::Mat tempFeatures;
    //Declaring strings for file storage read
    std::string featuresRoute;
    std::string matricula;

    //Dropping matriculaIndex content to store new matriculas in parallel with new dataset mat object
    matriculaIndex.clear();

    // Reading all documents from DB
    mongocxx::cursor cursor = coll.find({});
    for (auto doc : cursor)
    {
        featuresRoute = doc["identificacionFacial"].get_utf8().value.to_string();
        matricula = doc["matricula"].get_utf8().value.to_string();
        cv::FileStorage fs(featuresRoute, cv::FileStorage::READ);
        fs["data"] >> tempFeatures;
        fs.release();
        //This condition is to avoid any empty mat insertion to dataset (causes error)
        if (!tempFeatures.empty())
        {
            matriculaIndex.push_back(matricula);
            dataset.push_back(tempFeatures.t());
        }
    }
    //Saving it
    cv::FileStorage featureStorage("../../Database/storage/dataset.xml", cv::FileStorage::WRITE | cv::FileStorage::FORMAT_XML);
    featureStorage << "data" << dataset;
    featureStorage.release();

    //Constructing index with a set of randomized kd-trees
    index.build(dataset, cv::flann::KDTreeIndexParams());
}
