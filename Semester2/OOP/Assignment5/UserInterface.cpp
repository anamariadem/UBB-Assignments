//
// Created by Ana Maria on 20/03/2020.
//

#include <iostream>
#include "UserInterface.h"
#include <exception>

std::vector<std::string> UserInterface::separateUserParameters(std::string & userCommand, char & separator) {
    std::string separatedPartOfString = "";
    std::vector<std::string> separatedUserCommand;

    for(auto stringIterator: userCommand){
        if(stringIterator != separator)
            separatedPartOfString += stringIterator;

        if(stringIterator == separator && separatedPartOfString!= ""){
            separatedUserCommand.push_back(separatedPartOfString);
            separatedPartOfString="";
        }
    }

    if(separatedPartOfString != "")
        separatedUserCommand.push_back(separatedPartOfString);
    return separatedUserCommand;
}

void UserInterface::setApplicationMode() {
    std::string userParameters;
    std::getline(std::cin, userParameters);
    userParameters = userParameters.substr(1);
    int statusOfSet = this->service.setApplicationMode(userParameters);
    if(statusOfSet == false)
        std::cout<<"Invalid mode! :( \n";
}

void UserInterface::addTurretUserInterface() {

    try {
        std::string userParameters;
        std::getline(std::cin, userParameters);

        std::string inputLocation, inputSize, inputVision;
        int inputAuraLevel, inputSeparateParts;
        std::vector<std::string> separatedParameters = separateUserParameters(userParameters, (char &) ", ");
        inputLocation = separatedParameters[0].substr(1);
        inputSize = separatedParameters[1].substr(1);
        inputAuraLevel = std::stoi(separatedParameters[2]);
        inputSeparateParts = std::stoi(separatedParameters[3]);
        inputVision = separatedParameters[4].substr(1);
        bool statusOfAdd = this->service.addTurretService(inputLocation, inputSize, inputAuraLevel, inputSeparateParts, inputVision);
        if(!statusOfAdd)
            std::cout<<"Turret already exists! :( \n";
    } catch (std::exception&){
        std::cout<<"Operation not allowed if not in mode A! :( \n";
    }
}

void UserInterface::removeTurretUserInterface() {
    try {
        std::string userParameters;
        std::getline(std::cin, userParameters);

        std::string inputLocation;
        //std::getline(std::cin, userParameters);
        //std::vector<std::string> separatedParameters = separateUserParameters(userParameters, (char &) ", ");
        // inputLocation = userParameters.substr(1);

        bool statusOfRemove = this->service.removeTurretService(inputLocation);
        if(!statusOfRemove)
            std::cout<< "Turret is not in the list! :(\n";
    }catch (std::exception&){
        std::cout<<"Operation not allowed if not in mode A! :( \n";
    }
}

void UserInterface::updateTurretUserInterface() {
    try {
        std::string userParameters;
        std::getline(std::cin, userParameters);

        std::string inputLocation, inputSize, inputVision;
        int inputAuraLevel, inputSeparateParts;
        std::vector<std::string> separatedParameters = separateUserParameters(userParameters, (char &) ", ");
        inputLocation = separatedParameters[0].substr(1);
        inputSize = separatedParameters[1].substr(1);
        inputAuraLevel = std::stoi(separatedParameters[2]);
        inputSeparateParts = std::stoi(separatedParameters[3]);
        inputVision = separatedParameters[4].substr(1);
        bool statusOfUpdate = this->service.updateTurretService(inputLocation, inputSize, inputAuraLevel, inputSeparateParts, inputVision);
        if(!statusOfUpdate)
            std::cout<< "Turret is not in the list! :(\n";

    } catch (std::exception&){
        std::cout<<"Operation not allowed if not in mode A! :( \n";
    }

}
void UserInterface::printExistingTurrets() {
    DynamicVector listOfTurrets = this->service.getAllTurretsInRepository();

    for(int i=0; i < listOfTurrets.getSizeOfVector(); i++){
        NorvenTurret currentTurret = listOfTurrets.getElement(i);
        std::cout<<currentTurret.toString()<<std::endl;
    }
}

void UserInterface::startApplication(){
    std::string inputCommand;

    while(1){
        std::cout<<"Command: ";
        inputCommand = "";
        std::cin>>inputCommand;
        if(inputCommand == "exit") {
            break;
        } else if (inputCommand == "mode")
            setApplicationMode();
        else if (inputCommand == "add")
            addTurretUserInterface();
        else if (inputCommand == "delete")
            removeTurretUserInterface();
        else if (inputCommand == "update")
            updateTurretUserInterface();
        else if (inputCommand == "list")
            printExistingTurrets();
        else
            std::cout<<"Invalid command\n";
    }
}
