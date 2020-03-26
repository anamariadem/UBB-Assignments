//
// Created by Ana Maria on 19/03/2020.
//

#include "Repository.h"

int Repository::searchTurretByLocation(std::string location) {
    NorvenTurret currentTurret;

    for(int i=0; i< this->listOfTurrets.getSizeOfVector(); i++){
        currentTurret = this->listOfTurrets.getElement(i);
        if(currentTurret.getLocationOfTurret() == location)
            return i;
    }
    return -1;
}

bool Repository::addTurretToRepository(const class NorvenTurret & turretToAdd) {
    if(this->searchTurretByLocation(turretToAdd.getLocationOfTurret()) !=-1)
        return false;

    this->listOfTurrets.addToDynamicVector(turretToAdd);
    return true;
}

bool Repository::removeTurretFromRepository(const std::string & location) {
    int indexInTurretList = this->searchTurretByLocation(location);
    if(indexInTurretList == -1)
        return false;

    this->listOfTurrets.deleteFromDynamicVector(indexInTurretList);
    return true;
}

bool Repository::updateTurretFromRepository(const std::string & location, const std::string & newSize, const int & newAuraLevel, const int & newNumberOfSeparatedParts, const std::string & newVision) {
    int indexInTurretList = this->searchTurretByLocation(location);
    if(indexInTurretList == -1)
        return false;
    NorvenTurret newTurret = NorvenTurret(location, newSize, newAuraLevel, newNumberOfSeparatedParts, newVision);
    this->listOfTurrets.updateElementInDynamicArray(indexInTurretList, newTurret);
    return true;
}