//
// Created by Ana Maria on 28/03/2020.
//

#include "Service.h"

bool Service::setApplicationMode(std::string& newMode) {
    if(newMode!="A" && newMode!="B")
        return false;
    this->applicationMode = newMode;
    return true;
}

bool Service::addTurret(const std::string & location, const std::string & size, const int & auraLevel, const int & separateParts, const std::string & vision) {
    if(this->applicationMode != "A")
        throw std::exception();
    NorvenTurret turretToAdd(location, size, auraLevel, separateParts, vision);
    return this->repository.addTurretToRepository(turretToAdd);
}

bool Service::removeTurret(const std::string & location) {
    if(this->applicationMode != "A")
        throw std::exception();
    return this->repository.removeTurretFromRepository(location);
}

bool Service::updateTurret(const std::string & location, const std::string & size, const int & auraLevel, const int & separateParts, const std::string& vision) {
    if(this->applicationMode != "A")
        throw std::exception();
    return this->repository.updateTurretFromRepository(location, size, auraLevel, separateParts, vision);
}

void Service::moveToNextTurret() {
    if(this->applicationMode != "B")
        throw std::exception();

    this->repository.moveToNextTurret();
}

bool Service::saveTurret(const std::string & location) {
    //std::string message = "Operation not allowed if not in mode B! :( \n";
    if(this->applicationMode != "B")
        throw std::exception();

    return this->repository.saveTurret(location);
}

DynamicVector<NorvenTurret> Service::getListOfTurretsWithAGivenSizeAndAtLeastAGivenNumberOfParts(const std::string & size, const int & separateParts) {
    if(this->applicationMode != "B")
        throw std::exception();

    DynamicVector<NorvenTurret> turretsThatSatisfyTheCondition;

    DynamicVector<NorvenTurret> listOfTurrets = this->repository.getListOfTurrets();

    for(auto& turret : listOfTurrets)
        if(turret.getSizeOfTurret() == size and turret.getNumberOfSeparatePartsOfTurret() >= separateParts)
            turretsThatSatisfyTheCondition.addToDynamicVector(turret);

    return turretsThatSatisfyTheCondition;
}