#include "dataparser.h"


GameConfig* DataParser::parseJSON(std::string filename){


    QFile file(QString::fromStdString(filename));

    if (!file.open(QIODevice::ReadOnly)) {
        std::cout << "Cannot open JSON file!" << std::endl;
        return nullptr;
    }

    QByteArray jsonData = file.readAll();

    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);

    if (jsonDoc.isNull()) {
        std::cout << "Parse JSON error!" << std::endl;
        return nullptr;
    }

    QJsonObject root = jsonDoc.object();
    int refreshTime = root["refreshTime"].toInt();
    int gameHealth = root["gameHealth"].toInt();
    int money = root["money"].toInt();

    QJsonObject map = root["Map"].toObject();

    int rows = map["rows"].toInt();
    int cols = map["cols"].toInt();
    int squareSize = map["squareSize"].toInt();

    std::vector<std::pair<int,int>> roadPoints;

    QJsonArray points = map["roadPoints"].toArray();

    for(int i=0; i<points.size();i++){
        QJsonArray point = points[i].toArray();
        roadPoints.push_back(std::make_pair(point[0].toInt(),point[1].toInt()));
    }


    std::vector<std::pair<int,int>> towerPoints;

    QJsonArray pointsTower = map["towerPoints"].toArray();

    for(int i=0; i<pointsTower.size();i++){
        QJsonArray point = pointsTower[i].toArray();
        towerPoints.push_back(std::make_pair(point[0].toInt(),point[1].toInt()));
    }

    std::vector<Wave> waves;

    QJsonArray wavesJSON = root["Waves"].toArray();

    for(int i=0; i<wavesJSON.size();i++){
        QJsonObject waveJSON = wavesJSON[i].toObject();
        Wave wave = {.firstDelay=waveJSON["firstDelay"].toDouble(),.numberOfEnemies=waveJSON["numberOfEnemies"].toInt(),.delay=waveJSON["delay"].toDouble(),.enemiesLevel=waveJSON["enemyLevel"].toInt()};
        waves.push_back(wave);
    }

    std::vector<EnemyDetails> enemyDetails;

    QJsonArray enemyDetailsJSON = root["Enemies"].toArray();

    for(int i=0; i<enemyDetailsJSON.size();i++){
        QJsonObject detailsJSON = enemyDetailsJSON[i].toObject();
        EnemyDetails details = {.health=detailsJSON["health"].toInt(),.speed=detailsJSON["speed"].toInt(),.moneyFromEnemy=detailsJSON["moneyFromEnemy"].toInt(),.damageFromEnemy=detailsJSON["damageFromEnemy"].toInt(),.image=detailsJSON["image"].toString()};
        enemyDetails.push_back(details);
    }

    std::vector<TowerDetails> towerDetails;

    QJsonArray towerDetailsJSON = root["Towers"].toArray();

    for(int i=0; i<towerDetailsJSON.size();i++){
        QJsonObject detailsJSON = towerDetailsJSON[i].toObject();
        TowerDetails details = {.radius=detailsJSON["radius"].toInt(),.rateOfFire=detailsJSON["rateOfFire"].toDouble(),.price=detailsJSON["price"].toInt(),.image=detailsJSON["image"].toString(),.bulletSpeed=detailsJSON["bulletSpeed"].toInt(),.bulletDamage=detailsJSON["bulletDamage"].toInt(),.bulletImage=detailsJSON["bulletImage"].toString()};
        towerDetails.push_back(details);
    }




    return new GameConfig(refreshTime,gameHealth,money,rows,cols,squareSize,roadPoints,towerPoints,waves,enemyDetails,towerDetails);
}



