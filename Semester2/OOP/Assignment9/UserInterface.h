//
// Created by Ana Maria on 10/04/2020.
//

#ifndef ASSIGNMENT7_USERINTERFACE_H
#define ASSIGNMENT7_USERINTERFACE_H

#include "Service.h"


class UserInterface {
private:
    Service& service;
public:
    explicit UserInterface(Service& serviceToBuild): service { serviceToBuild } {}

    static std::vector<std::string > separateUserParameters(std::string& command, char& separator);

    void updateAllTurretsFile();

    void updateSavedTurretsFile();

    void setApplicationMode();

    void startApplication();

    void addTurret();

    void removeTurret();

    void updateTurret();

    void moveToNextTurret();

    void saveTurret();

    void printExistingTurrets();

    void printSavedTurrets();

    void openFileWithCorrectApplication();

    void printListOfTurretsWithAGivenSizeAndAtLeastAGivenNumberOfParts(std::string);

    void undo();

    void redo();
};


#endif //ASSIGNMENT7_USERINTERFACE_H
