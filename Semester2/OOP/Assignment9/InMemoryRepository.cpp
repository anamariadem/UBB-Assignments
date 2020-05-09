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

void InMemoryRepository::addTurret(const NorvenTurret &turretToAdd) {
    if(this->searchTurretByLocation(turretToAdd.getLocationOfTurret()) != -1)
        throw MyException("Turret already exists! :(\n");
        //return false;

    this->listOfTurrets.push_back(turretToAdd);
}

void InMemoryRepository::removeTurret(const std::string &location) {
    int indexInTurretList = this->searchTurretByLocation(location);
    if(indexInTurretList == -1)
        throw MyException("Turret does not exist! :(\n");

    this->listOfTurrets.erase(this->listOfTurrets.begin() + indexInTurretList);


}

void InMemoryRepository::updateTurret(const std::string &location, const std::string &newSize, const int &newAuraLevel, const int &newNumberOfSeparatedParts, const std::string &newVision) {
    int indexInTurretList = this->searchTurretByLocation(location);
    if(indexInTurretList == -1)
        throw MyException("Turret does not exist! :(\n");
    NorvenTurret newTurret = NorvenTurret(location, newSize, newAuraLevel, newNumberOfSeparatedParts, newVision);
    this->listOfTurrets.erase(this->listOfTurrets.begin() + indexInTurretList );
    this->listOfTurrets.insert(this->listOfTurrets.begin() + indexInTurretList , newTurret);
}

NorvenTurret InMemoryRepository::findTurretByLocation(const std::string& location)
{
    for (auto turret : this->listOfTurrets)
        if (turret.getLocationOfTurret() == location)
            return turret;
    throw MyException("Turret does not exist! :(\n");
}
