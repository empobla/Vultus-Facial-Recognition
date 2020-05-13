#ifndef DB_HPP
#define DB_HPP

#include <iostream>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/uri.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include <mongocxx/exception/bulk_write_exception.hpp>
#include <mongocxx/exception/error_code.hpp>
#include <mongocxx/exception/logic_error.hpp>
#include <mongocxx/exception/operation_exception.hpp>
#include <mongocxx/exception/server_error_code.hpp>

#include "EnvironmentVariables.hpp"
#include "Cuatec.hpp"
class DBManagerInterface
{
public:
    mongocxx::database db;
    mongocxx::client conn;
    mongocxx::collection coll;
    DBManagerInterface(std::string uri, std::string db, std::string coll);
    ~DBManagerInterface();
    int create(Cuatec cuatec);
    int create(std::string name, int age, std::string matricula1, cv::Mat imgMat, cv::Mat featuresMat);
    void readAll();
    std::string readOid(std::string matricula);
    Cuatec readOne(std::string matricula);
    std::string readOneName(std::string matricula);
    int readOneEdad(std::string matricula);
    cv::Mat readOneFeatures(std::string matricula);
    cv::Mat readOneImg(std::string matricula);
    int updateName(std::string matricula, std::string nuevoNombre);
    int updateMatricula(std::string matricula, std::string nuevaMatricula);
    int deleteOne(std::string matricula);
};

#endif