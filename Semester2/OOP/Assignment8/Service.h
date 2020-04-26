//
// Created by Ana Maria on 10/04/2020.
//

#ifndef ASSIGNMENT7_SERVICE_H
#define ASSIGNMENT7_SERVICE_H

#include "Repository.h"
#include "TextFileRepository.h"
#include "InMemoryRepository.h"
#include "CSVFileRepo.h"
#include "HTMLFileRepository.h"
#include "TurretValidator.h"
#include <algorithm>

class Service {
private:
    Repository* turretRepository;
    Repository* savedTurretRepository;
    std::string applicationMode = "C";
    int currentIndexInListOfTurrets = 0;

private:
    static FileRepository* createTurretRepositoryBasedOnFileExtension(const std::string &newFileName);
public:
    // constructor
    //Service(Repository* repositoryToBuild, Repository* savedRepoToBuild): turretRepository{repositoryToBuild }, applicationMode {"C" }, savedTurretRepository{savedRepoToBuild} {}

    Service(){this->turretRepository = new InMemoryRepository, this->savedTurretRepository = new InMemoryRepository;}

    void updateAllTurretsFile(const std::string & newFileName);

    void updateSavedTurretsFile(const std::string & newFileNam);

    std::string getFileName() const;

    void setApplicationMode(std::string& newMode);

    void addTurret(const std::string& location, const std::string& size, const int& auraLevel, const int& separateParts, const std::string& vision);

    void removeTurret(const std::string& location);

    void updateTurret(const std::string& location, const std::string& size, const int& auraLevel, const int& separateParts, const std::string& vision);

    void moveToNextTurret();

    void saveTurret(const std::string& location);

    std::vector<NorvenTurret> getListOfTurretsWithAGivenSizeAndAtLeastAGivenNumberOfParts(const std::string& size, const int& separateParts);

    std::vector<NorvenTurret> getAllTurretsInRepository() { return this->turretRepository->getListOfTurrets();}

    std::vector<NorvenTurret> getAllSavedTurrets() { return this->savedTurretRepository->getListOfTurrets();}

    int getCurrentIndexInListOfTurrets() { return this->currentIndexInListOfTurrets;}

    ~Service();
};


#endif //ASSIGNMENT7_SERVICE_H
