//
// Created by Ana Maria on 28/03/2020.
//

#include "Repository.h"

int Repository::searchTurretByLocation(const std::string& location) {
    int position = 0;

    for(auto& turret :  this->listOfTurrets){
        if(turret.getLocationOfTurret() == location)
            return position;
        position++;
    }
    return -1;
}

int Repository::searchSavedTurretByLocation(const std::string &location) {
    int position = 0;

    for(auto& turret :  this->listOfSavedTurrets){
        if(turret.getLocationOfTurret() == location)
            return position;
        position++;
    }
    return -1;
}

bool Repository::addTurretToRepository(const class NorvenTurret & turretToAdd) {
    if(this->searchTurretByLocation(turretToAdd.getLocationOfTurret()) != -1)
        return false;

    this->listOfTurrets.addToDynamicVector(turretToAdd);
    return true;
}

bool Repository::removeTurretFromRepository(const std::string & location) {
    int indexInTurretList = this->searchTurretByLocation(location);
    if(indexInTurretList == -1)
        return false;

    this->listOfTurrets.deleteFromDynamicVector(indexInTurretList);

    int indexInSavedTurretList = this->searchSavedTurretByLocation(location);
    if(indexInSavedTurretList !=-1)
        this->listOfSavedTurrets.deleteFromDynamicVector(indexInSavedTurretList);

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

void Repository::moveToNextTurret() {
    if(this->currentIndexInListOfTurrets == this->listOfTurrets.getSizeOfVector() -1)
        this->currentIndexInListOfTurrets = 0;
    else
        this->currentIndexInListOfTurrets ++;
}

bool Repository::saveTurret(const std::string& location) {
    int indexInTurretList = this->searchTurretByLocation(location);
    if(indexInTurretList == -1)
        return false;

    NorvenTurret turretToSave = this->listOfTurrets[indexInTurretList];
    for(auto& turret: this->listOfSavedTurrets)
        if(turret.getLocationOfTurret() == turretToSave.getLocationOfTurret())
            return false;

    this->listOfSavedTurrets.addToDynamicVector(turretToSave);
    return true;
}