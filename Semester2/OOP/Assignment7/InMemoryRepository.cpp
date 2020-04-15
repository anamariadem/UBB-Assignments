//
// Created by Ana Maria on 10/04/2020.
//

#include "InMemoryRepository.h"

int InMemoryRepository::searchTurretByLocation(const std::string &location) {
    int position = 0;

    for(auto& turret :  this->listOfTurrets){
        if(turret.getLocationOfTurret() == location)
            return position;
        position++;
    }
    return -1;
}

int InMemoryRepository::searchSavedTurretByLocation(const std::string &location) {
    int position = 0;

    for(auto& turret :  this->listOfSavedTurrets){
        if(turret.getLocationOfTurret() == location)
            return position;
        position++;
    }
    return -1;
}

bool InMemoryRepository::addTurret(const NorvenTurret &turretToAdd) {
    if(this->searchTurretByLocation(turretToAdd.getLocationOfTurret()) != -1)
        return false;

    this->listOfTurrets.push_back(turretToAdd);
    return true;
}

bool InMemoryRepository::removeTurret(const std::string &location) {
    int indexInTurretList = this->searchTurretByLocation(location);
    if(indexInTurretList == -1)
        return false;

    this->listOfTurrets.erase(this->listOfTurrets.begin() + indexInTurretList);

    int indexInSavedTurretList = this->searchSavedTurretByLocation(location);
    if(indexInSavedTurretList !=-1)
        this->listOfSavedTurrets.erase(this->listOfSavedTurrets.begin() + indexInSavedTurretList);

    return true;
}

bool InMemoryRepository::updateTurret(const std::string &location, const std::string &newSize, const int &newAuraLevel, const int &newNumberOfSeparatedParts, const std::string &newVision) {
    int indexInTurretList = this->searchTurretByLocation(location);
    if(indexInTurretList == -1)
        return false;
    NorvenTurret newTurret = NorvenTurret(location, newSize, newAuraLevel, newNumberOfSeparatedParts, newVision);
    this->listOfTurrets.erase(this->listOfTurrets.begin() + indexInTurretList );
    this->listOfTurrets.insert(this->listOfTurrets.begin() + indexInTurretList , newTurret);
    return true;
}

void InMemoryRepository::moveToNextTurret() {
    if(this->currentIndexInListOfTurrets == this->listOfTurrets.size()-1)
        this->currentIndexInListOfTurrets = 0;
    else
        this->currentIndexInListOfTurrets ++;
}

bool InMemoryRepository::saveTurret(const std::string &location) {
    int indexInTurretList = this->searchTurretByLocation(location);
    if(indexInTurretList == -1)
        return false;

    NorvenTurret turretToSave = this->listOfTurrets[indexInTurretList];
    for(auto& turret: this->listOfSavedTurrets)
        if(turret.getLocationOfTurret() == turretToSave.getLocationOfTurret())
            return false;

    this->listOfSavedTurrets.push_back(turretToSave);
    return true;
}