//
// Created by Ana Maria on 28/03/2020.
//

#ifndef ASSIGNMENT6_SERVICE_H
#define ASSIGNMENT6_SERVICE_H

#include "Repository.h"

class Service {
private:
    Repository& repository;
    std::string applicationMode;
public:
    // constructor
    Service(Repository& repositoryToBuild): repository{ repositoryToBuild }, applicationMode { "C" } {}

    bool setApplicationMode(std::string& newMode);

    bool addTurret(const std::string& location, const std::string& size, const int& auraLevel, const int& separateParts, const std::string& vision);

    bool removeTurret(const std::string& location);

    bool updateTurret(const std::string& location, const std::string& size, const int& auraLevel, const int& separateParts, const std::string& vision);

    void moveToNextTurret();

    bool saveTurret(const std::string& location);

    DynamicVector<NorvenTurret> getListOfTurretsWithAGivenSizeAndAtLeastAGivenNumberOfParts(const std::string& size, const int& separateParts);

    DynamicVector<NorvenTurret> getAllTurretsInRepository() { return this->repository.getListOfTurrets();}

    DynamicVector<NorvenTurret> getAllSavedTurrets() { return this->repository.getListOfSavedTurrets();}

    int getCurrentIndexInListOfTurrets() { return this->repository.getCurrentIndexInListOfTurrets();}
};


#endif //ASSIGNMENT6_SERVICE_H
