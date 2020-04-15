//
// Created by Ana Maria on 10/04/2020.
//

#ifndef ASSIGNMENT7_SERVICE_H
#define ASSIGNMENT7_SERVICE_H

#include "Repository.h"
#include <algorithm>

class Service {
private:
    Repository& repository;
    std::string applicationMode;
public:
    // constructor
    Service(Repository& repositoryToBuild): repository{ repositoryToBuild }, applicationMode { "C" } {}

    void updateFile(const std::string & newFileName) {this->repository.updateFile(newFileName);}

    std::string getFileName() const { return this->repository.getFilename(); }

    bool setApplicationMode(std::string& newMode);

    bool addTurret(const std::string& location, const std::string& size, const int& auraLevel, const int& separateParts, const std::string& vision);

    bool removeTurret(const std::string& location);

    bool updateTurret(const std::string& location, const std::string& size, const int& auraLevel, const int& separateParts, const std::string& vision);

    void moveToNextTurret();

    bool saveTurret(const std::string& location);


    std::vector<NorvenTurret> getListOfTurretsWithAGivenSizeAndAtLeastAGivenNumberOfParts(const std::string& size, const int& separateParts);

    std::vector<NorvenTurret> getAllTurretsInRepository() { return this->repository.getListOfTurrets();}

    std::vector<NorvenTurret> getAllSavedTurrets() { return this->repository.getListOfSavedTurrets();}

    int getCurrentIndexInListOfTurrets() { return this->repository.getCurrentIndexInListOfTurrets();}
};


#endif //ASSIGNMENT7_SERVICE_H
