//
// Created by Ana Maria on 28/03/2020.
//

#ifndef ASSIGNMENT6_REPOSITORY_H
#define ASSIGNMENT6_REPOSITORY_H

#include "DynamicVector.h"

class Repository {
private:
    DynamicVector<NorvenTurret> listOfTurrets;
    DynamicVector<NorvenTurret> listOfSavedTurrets;
    int currentIndexInListOfTurrets = 0;

    int searchTurretByLocation(const std::string& location);
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

    /*
     moves the current index to the next position or goes back to 0 if it reaches the end of the list
     */
    void moveToNextTurret();

    /*
     saves the turret with the given location
     */
    bool saveTurret(const std::string& location);

    int getCurrentIndexInListOfTurrets() const { return this->currentIndexInListOfTurrets;}

    DynamicVector<NorvenTurret> getListOfTurrets() const { return  this->listOfTurrets; }

    DynamicVector<NorvenTurret> getListOfSavedTurrets() const { return this->listOfSavedTurrets; }
};


#endif //ASSIGNMENT6_REPOSITORY_H
