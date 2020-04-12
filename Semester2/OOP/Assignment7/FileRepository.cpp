//
// Created by Ana Maria on 10/04/2020.
//

#include "FileRepository.h"
std::vector<NorvenTurret> FileRepository::loadDataFromFile() const{
    std::ifstream file{this->fileName};

    //if(!file.is_open())
      //  throw std::exception();

    std::vector<NorvenTurret> turretsFromFile;
    NorvenTurret turret{};

    while (file >> turret)
        turretsFromFile.push_back(turret);

    file.close();
    return turretsFromFile;
}

void FileRepository::loadDataToFile(const std::vector<NorvenTurret>& turretsToLoad) {
    std::ofstream file(this->fileName, std::ios::out);

    //if(!file.is_open())
      //  throw std::exception();

    for(auto& turret:turretsToLoad)
        file << turret;

    file.close();
}

int FileRepository::searchTurretByLocation(const std::string &location) {
    std::vector<NorvenTurret> listOfTurrets = this->loadDataFromFile();

    int position = 0;

    for(auto& turret :  listOfTurrets){
        if(turret.getLocationOfTurret() == location)
            return position;
        position++;
    }
    return -1;
}

int FileRepository::searchSavedTurretByLocation(const std::string &location) {
    int position = 0;

    for(auto& turret :  this->listOfSavedTurrets){
        if(turret.getLocationOfTurret() == location)
            return position;
        position++;
    }
    return -1;
}

bool FileRepository::addTurret(const NorvenTurret &turretToAdd) {
    if(this->searchTurretByLocation(turretToAdd.getLocationOfTurret()) != -1)
        return false;

    std::ofstream  file(this->fileName, std::ios::app);

    //if (!file.is_open())
      //  throw std::exception();

    file << turretToAdd;
    return true;
}

bool FileRepository::removeTurret(const std::string &location) {
    int indexInTurretList = this->searchTurretByLocation(location);
    if(indexInTurretList == -1)
        return false;

    std::vector<NorvenTurret> listOfTurrets = this->loadDataFromFile();
    listOfTurrets.erase(listOfTurrets.begin() + indexInTurretList);
    this->loadDataToFile(listOfTurrets);

    int indexInSavedTurretList = this->searchSavedTurretByLocation(location);
    if(indexInSavedTurretList !=-1)
        this->listOfSavedTurrets.erase(this->listOfSavedTurrets.begin() + indexInSavedTurretList);

    return true;
}

bool FileRepository::updateTurret(const std::string &location, const std::string &newSize, const int &newAuraLevel, const int &newNumberOfSeparatedParts, const std::string &newVision) {
    int indexInTurretList = this->searchTurretByLocation(location);
    if(indexInTurretList == -1)
        return false;

    NorvenTurret newTurret = NorvenTurret(location, newSize, newAuraLevel, newNumberOfSeparatedParts, newVision);
    std::vector<NorvenTurret> listOfTurrets = this->loadDataFromFile();
    listOfTurrets.erase(listOfTurrets.begin() + indexInTurretList );
    listOfTurrets.insert(listOfTurrets.begin() + indexInTurretList , newTurret);
    this->loadDataToFile(listOfTurrets);

    return true;
}

void FileRepository::moveToNextTurret() {
    std::vector<NorvenTurret> listOfTurrets = this->loadDataFromFile();
    if(this->currentIndexInListOfTurrets == listOfTurrets.size()-1)
        this->currentIndexInListOfTurrets = 0;
    else
        this->currentIndexInListOfTurrets ++;
}

bool FileRepository::saveTurret(const std::string &location) {
    int indexInTurretList = this->searchTurretByLocation(location);
    if(indexInTurretList == -1)
        return false;

    std::vector<NorvenTurret> listOfTurrets = this->loadDataFromFile();

    NorvenTurret turretToSave = listOfTurrets[indexInTurretList];
    for(auto& turret: this->listOfSavedTurrets)
        if(turret.getLocationOfTurret() == turretToSave.getLocationOfTurret())
            return false;

    this->listOfSavedTurrets.push_back(turretToSave);
    return true;
}

std::vector<NorvenTurret> FileRepository::getListOfTurrets() const {
    return this->loadDataFromFile();
}
