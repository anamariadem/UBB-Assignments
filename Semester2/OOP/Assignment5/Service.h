//
// Created by Ana Maria on 20/03/2020.
//

#ifndef ASSIGNMENT5_SERVICE_H
#define ASSIGNMENT5_SERVICE_H

#include "Repository.h"

class Service {
private:
    Repository& repository;
    std::string applicationMode;
public:
    // constructor
    Service(Repository& repositoryToBuild): repository{ repositoryToBuild }, applicationMode { "B" } {}

    bool setApplicationMode(std::string newMode);

    bool addTurretService(const std::string& location, const std::string& size, const int& auraLevel, const int& separateParts, const std::string vision);

    bool removeTurretService(const std::string& location);

    bool updateTurretService(const std::string& location, const std::string& size, const int& auraLevel, const int& separateParts, const std::string vision);

    DynamicVector getAllTurretsInRepository();
};


#endif //ASSIGNMENT5_SERVICE_H
