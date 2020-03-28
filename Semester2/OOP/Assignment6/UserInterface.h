//
// Created by Ana Maria on 28/03/2020.
//

#ifndef ASSIGNMENT6_USERINTERFACE_H
#define ASSIGNMENT6_USERINTERFACE_H

#include "Service.h"

class UserInterface {
private:
    Service service;
public:
    UserInterface(Service& serviceToBuild): service { serviceToBuild } {}

    static DynamicVector<std::string > separateUserParameters(std::string& command, char& separator);

    void setApplicationMode();

    void startApplication();

    void addTurret();

    void removeTurret();

    void updateTurret();

    void moveToNextTurret();

    void saveTurret();

    void printExistingTurrets();

    void printSavedTurrets();

    void printListOfTurretsWithAGivenSizeAndAtLeastAGivenNumberOfParts(std::string);
};


#endif //ASSIGNMENT6_USERINTERFACE_H
