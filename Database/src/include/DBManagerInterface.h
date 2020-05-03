#ifndef DB_H
#define DB_H

#include <iostream>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/uri.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include "EnvironmentVariables.h"
#include "../Cuatec.cpp"
class DBManagerInterface
{
public:
    mongocxx::database db;
    mongocxx::client conn;
    mongocxx::collection coll;
    DBManagerInterface(std::string uri, std::string db, std::string coll);
    ~DBManagerInterface();
    void create(Cuatec cuatec);
    void readAll();
    Cuatec readOne(std::string matricula);
    void updateName(std::string nombre, std::string nuevoNombre);
    void updateMatricula(std::string matricula, std::string nuevaMatricula);
    void deleteOne(std::string matricula);
    cv::Mat readFeatures(std::string matricula);
    std::string readOid(std::string matricula);
};

#endif