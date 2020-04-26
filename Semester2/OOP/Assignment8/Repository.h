//
// Created by Ana Maria on 10/04/2020.
//

#ifndef ASSIGNMENT7_REPOSITORY_H
#define ASSIGNMENT7_REPOSITORY_H

#include "Turret.h"
#include "TurretValidator.h"
#include <string>

class Repository{
public:
    virtual int searchTurretByLocation(const std::string& location) = 0;
    virtual NorvenTurret findTurretByLocation(const std::string& location) =0;
    //virtual int searchSavedTurretByLocation(const std::string& location) = 0;

    virtual void addTurret(const NorvenTurret& turretToAdd) = 0;
    virtual void removeTurret(const std::string& location) = 0;
    virtual void updateTurret(const std::string& location, const std::string& newSize, const int& newAuraLevel, const int& newNumberOfSeparatedParts, const std::string& newVision) =0;
    //virtual void saveTurret(const std::string& location)=0;
    virtual std::vector<NorvenTurret> getListOfTurrets() const = 0;
    //virtual std::vector<NorvenTurret> getListOfSavedTurrets() const = 0;

    virtual ~Repository() {}
};

#endif //ASSIGNMENT7_REPOSITORY_H
