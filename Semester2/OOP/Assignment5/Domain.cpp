//
// Created by Ana Maria on 19/03/2020.
//

#include "Domain.h"

NorvenTurret::NorvenTurret() {
    this->location = "";
    this->size = "";
    this->auraLevel = 0;
    this->separateParts = 0;
    this->vision = "";
}

NorvenTurret::NorvenTurret(const std::string &location, const std::string &size, const int &auraLevel, const int &separateParts, const std::string vision) {
    this->location = location;
    this->size = size;
    this->auraLevel = auraLevel;
    this->separateParts = separateParts;
    this->vision = vision;
}

std::string NorvenTurret::toString() {
    return this->getLocationOfTurret() + " " + this->getSizeOfTurret() + " " + std::to_string(this->getAuraLevelOfTurret()) + " " + std::to_string(this->getNumberOfSeparatePartsOfTurret()) + " " + this->getVisionOfTurret();
}