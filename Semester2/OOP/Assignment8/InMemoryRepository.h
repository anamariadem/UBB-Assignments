//
// Created by Ana Maria on 10/04/2020.
//

#ifndef ASSIGNMENT7_INMEMORYREPOSITORY_H
#define ASSIGNMENT7_INMEMORYREPOSITORY_H

#include "Repository.h"
#include "Turret.h"

class InMemoryRepository : public Repository {

private:
    std::vector<NorvenTurret> listOfTurrets;

private:
    int searchTurretByLocation(const std::string& location)override ;
    NorvenTurret findTurretByLocation(const std::string& location) override;
public:
    // default constructor
    InMemoryRepository() {};

    /*
     adds a new turret to the repository
     returns true -> turret was added
            false -> turret already exists
     */
    void addTurret(const NorvenTurret& turretToAdd)override ;

    /*
     removes a turret from repository
     returns true -> turret was deleted
            false -> turret does not exist
     */
    void removeTurret(const std::string& location)override ;

    /*
     updates a turret from repository
     returns true -> turret was updated
            false -> turret does not exist
     */
    void updateTurret(const std::string& location, const std::string& newSize, const int& newAuraLevel, const int& newNumberOfSeparatedParts, const std::string& newVision)override ;


    std::vector<NorvenTurret> getListOfTurrets() const override { return  this->listOfTurrets; }

};


#endif //ASSIGNMENT7_INMEMORYREPOSITORY_H
