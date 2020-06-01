//
// Created by Ana Maria on 24/04/2020.
//

#include <iostream>
#include "HTMLFileRepository.h"

std::vector<NorvenTurret> HTMLFileRepository::loadDataFromFile() const {
    if(this->fileName.empty())
        throw MyException("No file was provided! :(\n");

    std::ifstream file{this->fileName};
    if(file.eof())
        return std::vector<NorvenTurret>();

    std::vector<NorvenTurret> turretsFromFile;
    std::string buffer, location, size, vision;
    int auraLevel, numberOfSeparateParts;

    for(int i=0; i<14; i++){
        getline(file, buffer);
    }

    while(!file.eof()){
        getline(file, buffer);
        if(buffer == "</table>")
            break;
        getline(file, buffer);
        auto indexToStop = buffer.find_last_of('<');
        location = buffer.substr(4, indexToStop-4);

        getline(file, buffer);
        indexToStop = buffer.find_last_of('<');
        size = buffer.substr(4, indexToStop-4);

        getline(file, buffer);
        indexToStop = buffer.find_last_of('<');
        auraLevel = std::atoi(buffer.substr(4, indexToStop-4).c_str());

        getline(file, buffer);
        indexToStop = buffer.find_last_of('<');
        numberOfSeparateParts = std::atoi(buffer.substr(4, indexToStop-4).c_str());

        getline(file, buffer);
        indexToStop = buffer.find_last_of('<');
        vision = buffer.substr(4, indexToStop-4);

        turretsFromFile.emplace_back(location, size, auraLevel, numberOfSeparateParts, vision);

        getline(file, buffer);
    }

    file.close();
    return turretsFromFile;
}

void HTMLFileRepository::loadDataToFile(const std::vector<NorvenTurret> &turrets) {
    if(this->fileName.empty())
        throw MyException("No file was provided! :(\n");

    std::ofstream file(this->fileName, std::ios::out);

    file << "<!DOCTYPE html>\n";
    file << "<html>\n";
    file << "<head>\n";
    file << "<title>NorvenTurret</title>\n";
    file << "</head>\n";
    file << "<body>\n";
    file << "<table border=\"1\">\n";
    file << "<tr>\n";
    file << "<td>Location</td>\n";
    file << "<td>Size</td>\n";
    file << "<td>Aura Level</td>\n";
    file << "<td>Number of separate parts</td>\n";
    file << "<td>Vision</td>\n";
    file << "</tr>\n";

    for(auto& turret : turrets){
        file << "<tr>\n";
        file << "<td>"<<turret.getLocationOfTurret()<<"</td>\n";
        file << "<td>"<<turret.getSizeOfTurret()<<"</td>\n";
        file << "<td>"<<turret.getAuraLevelOfTurret()<<"</td>\n";
        file << "<td>"<<turret.getNumberOfSeparatePartsOfTurret()<<"</td>\n";
        file << "<td>"<<turret.getVisionOfTurret()<<"</td>\n";
        file << "</tr>\n";
    }

    file << "</table>\n";
    file << "</body>\n";
    file << "</html>";


    file.close();
}

int HTMLFileRepository::searchTurretByLocation(const std::string &location) {
    std::vector<NorvenTurret> listOfTurrets = this->loadDataFromFile();

    int position = 0;

    for(auto& turret :  listOfTurrets){
        if(turret.getLocationOfTurret() == location)
            return position;
        position++;
    }
    return -1;
}


void HTMLFileRepository::addTurret(const NorvenTurret &turretToAdd) {
    if(this->fileName.empty())
        throw MyException("No file was provided");
    if(this->searchTurretByLocation(turretToAdd.getLocationOfTurret()) != -1)
        throw MyException("Turret already exists! :(\n");

    std::vector<NorvenTurret> listOfTurrets = this->loadDataFromFile();
    listOfTurrets.push_back(turretToAdd);
    this->loadDataToFile(listOfTurrets);
}

void HTMLFileRepository::removeTurret(const std::string &location) {
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

void HTMLFileRepository::updateTurret(const std::string &location, const std::string &newSize, const int &newAuraLevel, const int &newNumberOfSeparatedParts, const std::string &newVision) {
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


std::vector<NorvenTurret> HTMLFileRepository::getListOfTurrets() const {
    return this->loadDataFromFile();
}

NorvenTurret HTMLFileRepository::findTurretByLocation(const std::string &location) {
    std::vector<NorvenTurret> listOfTurrets = this->loadDataFromFile();

    for(auto turret:listOfTurrets){
        if(turret.getLocationOfTurret() == location)
            return turret;
    }
    throw MyException("Turret does not exist! :(\n");
}

void HTMLFileRepository::clearFile() {
    std::ofstream file(this->fileName);

    file.close();
}
