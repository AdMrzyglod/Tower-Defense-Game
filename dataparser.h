#ifndef DATAPARSER_H
#define DATAPARSER_H



#include <iostream>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "gameconfig.h"
#include <QJsonArray>


class DataParser
{
public:
    static GameConfig* parseJSON(std::string filename);
};

#endif // DATAPARSER_H
