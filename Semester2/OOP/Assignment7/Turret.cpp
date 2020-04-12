//
// Created by Ana Maria on 10/04/2020.
//

#include "Turret.h"

NorvenTurret::NorvenTurret() {
    this->location = "";
    this->size = "";
    this->auraLevel = 0;
    this->separateParts = 0;
    this->vision = "";
}

NorvenTurret::NorvenTurret(const std::string &location, const std::string &size, const int &auraLevel, const int &separateParts, const std::string& vision) {
    this->location = location;
    this->size = size;
    this->auraLevel = auraLevel;
    this->separateParts = separateParts;
    this->vision = vision;
}


std::vector<std::string> separate(const std::string& stringToBeSeparated, char delimiter){
    std::vector<std::string> resultedString;
    std::stringstream stream(stringToBeSeparated);

    std::string token;

    while (getline(stream, token, delimiter))
        resultedString.push_back(token);

    return resultedString;
}

std::istream& operator>>(std::istream& iStream, NorvenTurret& turret){
    std::string line;
    getline(iStream, line);

    std::vector<std::string> separatedArguments = separate(line, (char&) ", ");
    if(separatedArguments.size() != 5){
        return iStream;
    }

    turret.location = separatedArguments[0];
    std::string newSize = separatedArguments[1].substr(1);
    turret.setSizeOfTurret(newSize);
    turret.setAuraLevelOfTurret(std::stoi(separatedArguments[2]));
    turret.setNumberOfSeparatePartsOfTurret(std::stoi(separatedArguments[3]));
    std::string newVision = separatedArguments[4].substr(1);
    turret.setVisionOfTurret(newVision);

    return iStream;
}

std::ostream& operator<<(std::ostream& oStream, const NorvenTurret& turret){
    oStream<<turret.getLocationOfTurret()<<", "<<turret.getSizeOfTurret()<<", "<<turret.getAuraLevelOfTurret()<<", " <<turret.getNumberOfSeparatePartsOfTurret()<<", "<<turret.getVisionOfTurret()<<"\n";
    return oStream;}