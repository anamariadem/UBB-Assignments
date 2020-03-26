//
// Created by Ana Maria on 20/03/2020.
//

#ifndef ASSIGNMENT5_USERINTERFACE_H
#define ASSIGNMENT5_USERINTERFACE_H

#include "Service.h"
#include <vector>

class UserInterface {
private:
    Service service;
public:
    UserInterface(Service& serviceToBuild): service { serviceToBuild } {}

    static std::vector<std::string> separateUserParameters(std::string& command, char& separator);

    void setApplicationMode();

    void startApplication();

    void addTurretUserInterface();

    void removeTurretUserInterface();

    void updateTurretUserInterface();

    void printExistingTurrets();
};


#endif //ASSIGNMENT5_USERINTERFACE_H
