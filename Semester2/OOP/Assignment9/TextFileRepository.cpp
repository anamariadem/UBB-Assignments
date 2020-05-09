//
// Created by Ana Maria on 10/04/2020.
//

#include "TextFileRepository.h"

std::vector<NorvenTurret> TextFileRepository::loadDataFromFile() const{
    if(this->fileName.empty())
        throw MyException("No file was provided! :(\n");

    std::ifstream file{this->fileName};

    std::vector<NorvenTurret> turretsFromFile;
    NorvenTurret turret{};

    while (file >> turret)
        turretsFromFile.push_back(turret);

    file.close();
    return turretsFromFile;
}


void TextFileRepository::loadDataToFile(const std::vector<NorvenTurret>& turretsToLoad) {
    if(this->fileName.empty())
        throw MyException("No file was provided! :(\n");

    std::ofstream file(this->fileName, std::ios::out);

    //if(!file.is_open())
      //  throw std::exception();

    for(auto& turret:turretsToLoad)
        file << turret;

    file.close();
}

void TextFileRepository::clearFile() {
    std::ofstream file(this->fileName);

    file.close();
}


int TextFileRepository::searchTurretByLocation(const std::string &location) {
    std::vector<NorvenTurret> listOfTurrets = this->loadDataFromFile();

    int position = 0;

    for(auto& turret :  listOfTurrets){
        if(turret.getLocationOfTurret() == location)
            return position;
        position++;
    }
    return -1;
}



/*
int TextFileRepository::searchSavedTurretByLocation(const std::string &location) {
    int position = 0;

    for(auto& turret :  this->listOfSavedTurrets){
        if(turret.getLocationOfTurret() == location)
            return position;
        position++;
    }
    return -1;
}*/

void TextFileRepository::addTurret(const NorvenTurret &turretToAdd) {
    if(this->searchTurretByLocation(turretToAdd.getLocationOfTurret()) != -1)
        throw MyException("Turret already exists! :(\n");

    std::ofstream  file(this->fileName, std::ios::app);

    //if (!file.is_open())
      //  throw std::exception();

    file << turretToAdd;
}

void TextFileRepository::removeTurret(const std::string &location) {
    int indexInTurretList = this->searchTurretByLocation(location);
    if(indexInTurretList == -1)
        throw MyException("Turret does not exist! :(\n");

    std::vector<NorvenTurret> listOfTurrets = this->loadDataFromFile();
    listOfTurrets.erase(listOfTurrets.begin() + indexInTurretList);
    this->loadDataToFile(listOfTurrets);

    /*int indexInSavedTurretList = this->searchSavedTurretByLocation(location);
    if(indexInSavedTurretList !=-1)
        this->listOfSavedTurrets.erase(this->listOfSavedTurrets.begin() + indexInSavedTurretList);
    */
}

void TextFileRepository::updateTurret(const std::string &location, const std::string &newSize, const int &newAuraLevel, const int &newNumberOfSeparatedParts, const std::string &newVision) {
    int indexInTurretList = this->searchTurretByLocation(location);
    if(indexInTurretList == -1)
        throw MyException("Turret does not exist! :(\n");

    NorvenTurret newTurret = NorvenTurret(location, newSize, newAuraLevel, newNumberOfSeparatedParts, newVision);
    std::vector<NorvenTurret> listOfTurrets = this->loadDataFromFile();
    listOfTurrets.erase(listOfTurrets.begin() + indexInTurretList );
    listOfTurrets.insert(listOfTurrets.begin() + indexInTurretList , newTurret);
    this->loadDataToFile(listOfTurrets);

}

/*
void TextFileRepository::moveToNextTurret() {
    std::vector<NorvenTurret> listOfTurrets = this->loadDataFromFile();
    if(this->currentIndexInListOfTurrets == listOfTurrets.size()-1)
        this->currentIndexInListOfTurrets = 0;
    else
        this->currentIndexInListOfTurrets ++;
}


void TextFileRepository::saveTurret(const std::string &location) {
    int indexInTurretList = this->searchTurretByLocation(location);
    if(indexInTurretList == -1)
        throw MyException("Turret does not exist! :(\n");

    std::vector<NorvenTurret> listOfTurrets = this->loadDataFromFile();

    NorvenTurret turretToSave = listOfTurrets[indexInTurretList];
    for(auto& turret: this->listOfSavedTurrets)
        if(turret.getLocationOfTurret() == turretToSave.getLocationOfTurret())
            throw MyException("Turret is already saved! :(\n");

    this->listOfSavedTurrets.push_back(turretToSave);
}*/

std::vector<NorvenTurret> TextFileRepository::getListOfTurrets() const {
    return this->loadDataFromFile();
}

NorvenTurret TextFileRepository::findTurretByLocation(const std::string &location) {
    std::vector<NorvenTurret> listOfTurrets = this->loadDataFromFile();

    for(auto turret:listOfTurrets){
        if(turret.getLocationOfTurret() == location)
            return turret;
    }
    throw MyException("Turret does not exist! :(\n");
}
