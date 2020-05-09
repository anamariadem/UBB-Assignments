//
// Created by Ana Maria on 10/04/2020.
//

#ifndef ASSIGNMENT7_FILEREPOSITORY_H
#define ASSIGNMENT7_FILEREPOSITORY_H

#include "Repository.h"
#include <fstream>

class FileRepository: public Repository{
protected:
    std::string fileName;

public:
    void updateFile(const std::string& newFile) {this->fileName = newFile;}
    std::string getFilename(){ return this->fileName;}
    virtual void clearFile() =0;
};


class TextFileRepository: public FileRepository {
private:
    int searchTurretByLocation(const std::string& location) override ;
    NorvenTurret findTurretByLocation(const std::string& location) override ;
    //int searchSavedTurretByLocation(const std::string& location) override ;

public:
    //explicit TextFileRepository(const std::string& givenFileName) { this->fileName = givenFileName;}
    TextFileRepository(){this->fileName = ""; };

    void clearFile() override;

    /*
     adds a new turret to the turretRepository
     returns true -> turret was added
            false -> turret already exists
     */
    void addTurret(const NorvenTurret& turretToAdd)override ;

    /*
     removes a turret from turretRepository
     returns true -> turret was deleted
            false -> turret does not exist
     */
    void removeTurret(const std::string& location)override ;

    /*
     updates a turret from turretRepository
     returns true -> turret was updated
            false -> turret does not exist
     */
    void updateTurret(const std::string& location, const std::string& newSize, const int& newAuraLevel, const int& newNumberOfSeparatedParts, const std::string& newVision)override ;


    std::vector<NorvenTurret> getListOfTurrets() const override;

    //std::vector<NorvenTurret> getListOfSavedTurrets() const override { return this->listOfSavedTurrets; }

    friend std::vector<std::string> separate(const std::string& stringToBeSeparated, char delimiter);

    std::vector<NorvenTurret>loadDataFromFile() const;
    void loadDataToFile(const std::vector<NorvenTurret>& turrets);

};


#endif //ASSIGNMENT7_FILEREPOSITORY_H
