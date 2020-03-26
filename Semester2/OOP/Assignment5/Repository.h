//
// Created by Ana Maria on 19/03/2020.
//

#ifndef ASSIGNMENT5_REPOSITORY_H
#define ASSIGNMENT5_REPOSITORY_H

#include "Domain.h"
#include "DynamicVector.h"

class Repository {
private:
    DynamicVector listOfTurrets;
    int searchTurretByLocation(std::string location);

public:
    // default constructor
    Repository() {};

    /*
     adds a new turret to the repository
     returns true -> turret was added
            false -> turret already exists
     */
    bool addTurretToRepository(const NorvenTurret& turretToAdd);

    /*
     removes a turret from repository
     returns true -> turret was deleted
            false -> turret does not exist
     */
    bool removeTurretFromRepository(const std::string& location);

    /*
     updates a turret from repository
     returns true -> turret was updated
            false -> turret does not exist
     */
    bool updateTurretFromRepository(const std::string& location, const std::string& newSize, const int& newAuraLevel, const int& newNumberOfSeparatedParts, const std::string& newVision);

    DynamicVector getListOfTurrets() const { return  this->listOfTurrets; }

};


#endif //ASSIGNMENT5_REPOSITORY_H
