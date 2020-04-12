//
// Created by Ana Maria on 10/04/2020.
//

#ifndef ASSIGNMENT7_FILEREPOSITORY_H
#define ASSIGNMENT7_FILEREPOSITORY_H

#include "Repository.h"
#include <fstream>

class FileRepository: public Repository {
private:
    std::string fileName;
    std::vector<NorvenTurret> listOfSavedTurrets;
    int currentIndexInListOfTurrets = 0;

private:
    int searchTurretByLocation(const std::string& location) override ;
    int searchSavedTurretByLocation(const std::string& location) override ;

public:
    explicit FileRepository(const std::string& givenFileName) { this->fileName = givenFileName;}
    void updateFile(const std::string& newFile) override {this->fileName = newFile;}
    std::string getFilename()const override { return this->fileName;}
    /*
     adds a new turret to the repository
     returns true -> turret was added
            false -> turret already exists
     */
    bool addTurret(const NorvenTurret& turretToAdd)override ;

    /*
     removes a turret from repository
     returns true -> turret was deleted
            false -> turret does not exist
     */
    bool removeTurret(const std::string& location)override ;

    /*
     updates a turret from repository
     returns true -> turret was updated
            false -> turret does not exist
     */
    bool updateTurret(const std::string& location, const std::string& newSize, const int& newAuraLevel, const int& newNumberOfSeparatedParts, const std::string& newVision)override ;

    /*
     moves the current index to the next position or goes back to 0 if it reaches the end of the list
     */
    void moveToNextTurret()override ;

    /*
     saves the turret with the given location
     */
    bool saveTurret(const std::string& location) override ;

    int getCurrentIndexInListOfTurrets() const override { return this->currentIndexInListOfTurrets;}

    std::vector<NorvenTurret> getListOfTurrets() const override;

    std::vector<NorvenTurret> getListOfSavedTurrets() const override { return this->listOfSavedTurrets; }

    friend std::vector<std::string> separate(const std::string& stringToBeSeparated, char delimiter);

    std::vector<NorvenTurret> loadDataFromFile() const;
    void loadDataToFile(const std::vector<NorvenTurret>& turrets);
};


#endif //ASSIGNMENT7_FILEREPOSITORY_H
