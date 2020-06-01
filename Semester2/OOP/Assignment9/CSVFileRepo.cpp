//
// Created by Ana Maria on 23/04/2020.
//

#include "CSVFileRepo.h"

std::vector<NorvenTurret> CSVFileRepository::loadDataFromFile() const{
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

void CSVFileRepository::loadDataToFile(const std::vector<NorvenTurret>& turretsToLoad) {
    if(this->fileName.empty())
        throw MyException("No file was provided! :(\n");
    std::ofstream file(this->fileName, std::ios::out);

    //if(!file.is_open())
    //  throw std::exception();

    for(auto& turret:turretsToLoad)
        file << turret;

    file.close();
}

void CSVFileRepository::clearFile() {
    std::ofstream file(this->fileName);

    file.close();
}


int CSVFileRepository::searchTurretByLocation(const std::string &location) {
    std::vector<NorvenTurret> listOfTurrets = this->loadDataFromFile();

    int position = 0;

    for(auto& turret :  listOfTurrets){
        if(turret.getLocationOfTurret() == location)
            return position;
        position++;
    }
    return -1;
}


void CSVFileRepository::addTurret(const NorvenTurret &turretToAdd) {
    if(this->fileName.empty())
        throw MyException("No file was provided");
    if(this->searchTurretByLocation(turretToAdd.getLocationOfTurret()) != -1)
        throw MyException("Turret already exists! :(\n");

    std::ofstream  file(this->fileName, std::ios::app);

    //if (!file.is_open())
    //  throw std::exception();

    file << turretToAdd;
}

void CSVFileRepository::removeTurret(const std::string &location) {
    if(this->fileName.empty())
        throw MyException("No file was provided");
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

void CSVFileRepository::updateTurret(const std::string &location, const std::string &newSize, const int &newAuraLevel, const int &newNumberOfSeparatedParts, const std::string &newVision) {
    if(this->fileName.empty())
        throw MyException("No file was provided");
    int indexInTurretList = this->searchTurretByLocation(location);
    if(indexInTurretList == -1)
        throw MyException("Turret does not exist! :(\n");

    NorvenTurret newTurret = NorvenTurret(location, newSize, newAuraLevel, newNumberOfSeparatedParts, newVision);
    std::vector<NorvenTurret> listOfTurrets = this->loadDataFromFile();
    listOfTurrets.erase(listOfTurrets.begin() + indexInTurretList );
    listOfTurrets.insert(listOfTurrets.begin() + indexInTurretList , newTurret);
    this->loadDataToFile(listOfTurrets);

}


std::vector<NorvenTurret> CSVFileRepository::getListOfTurrets() const {
    return this->loadDataFromFile();
}

NorvenTurret CSVFileRepository::findTurretByLocation(const std::string &location) {
    std::vector<NorvenTurret> listOfTurrets = this->loadDataFromFile();

    for(auto turret:listOfTurrets){
        if(turret.getLocationOfTurret() == location)
            return turret;
    }
    throw MyException("Turret does not exist! :(\n");
}
