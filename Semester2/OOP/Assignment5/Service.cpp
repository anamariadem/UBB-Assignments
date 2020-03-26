//
// Created by Ana Maria on 20/03/2020.
//

#include "Service.h"

bool Service::setApplicationMode(std::string newMode) {
    if(newMode!="A" && newMode!="B")
        return false;
    this->applicationMode = newMode;
    return true;
}

bool Service::addTurretService(const std::string & location, const std::string & size, const int & auraLevel, const int & separateParts, const std::string vision) {
    if(this->applicationMode != "A")
        throw std::exception();
    NorvenTurret turretToAdd(location, size, auraLevel, separateParts, vision);
    return this->repository.addTurretToRepository(turretToAdd);
}

bool Service::removeTurretService(const std::string & location) {
    if(this->applicationMode != "A")
        throw std::exception();
    return this->repository.removeTurretFromRepository(location);
}

bool Service::updateTurretService(const std::string & location, const std::string & size, const int & auraLevel, const int & separateParts, const std::string vision) {
    if(this->applicationMode != "A")
        throw std::exception();
    return this->repository.updateTurretFromRepository(location, size, auraLevel, separateParts, vision);
}

DynamicVector Service::getAllTurretsInRepository() {
    return this->repository.getListOfTurrets();
}