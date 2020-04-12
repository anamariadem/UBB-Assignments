//
// Created by Ana Maria on 10/04/2020.
//

#include "UserInterface.h"
#include <iostream>
#include <fstream>

std::vector<std::string> UserInterface::separateUserParameters(std::string & command, char & separator) {
    std::string separatedPartOfString = "";
    std::vector<std::string> separatedUserCommand;

    for(auto stringIterator: command){
        if(stringIterator != separator)
            separatedPartOfString += stringIterator;

        if(stringIterator == separator && separatedPartOfString!= ""){
            separatedUserCommand.push_back(separatedPartOfString);
            separatedPartOfString = "";
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
    if(statusOfSet == 0)
        std::cout<<"Invalid mode! :( \n";
}

void UserInterface::addTurret() {

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
        bool statusOfAdd = this->service.addTurret(inputLocation, inputSize, inputAuraLevel, inputSeparateParts, inputVision);
        if(!statusOfAdd)
            std::cout<<"Turret already exists! :( \n";
    } catch (std::exception&){
        std::cout<<"Operation not allowed if not in mode A! :( \n";
    }
}

void UserInterface::removeTurret() {
    try {
        std::string userParameters;
        std::getline(std::cin, userParameters);
        userParameters = userParameters.substr(1);

        bool statusOfRemove = this->service.removeTurret(userParameters);
        if(!statusOfRemove)
            std::cout<< "Turret is not in the list! :(\n";
    }catch (std::exception&){
        std::cout<<"Operation not allowed if not in mode A! :( \n";
    }
}

void UserInterface::updateTurret() {
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

        bool statusOfUpdate = this->service.updateTurret(inputLocation, inputSize, inputAuraLevel, inputSeparateParts, inputVision);
        if(!statusOfUpdate)
            std::cout<< "Turret is not in the list! :(\n";

    } catch (std::exception&){
        std::cout<<"Operation not allowed if not in mode A! :( \n";
    }

}
void UserInterface::printExistingTurrets() {
    std::vector<NorvenTurret> listOfTurrets = this->service.getAllTurretsInRepository();

    for(auto& turret: listOfTurrets)
        std::cout<<turret<<"\n";
}

void UserInterface::printSavedTurrets() {
    std::vector<NorvenTurret> listOfSavedTurrets = this->service.getAllSavedTurrets();

    for(auto& turret: listOfSavedTurrets)
        std::cout<<turret<<"\n";
}

void UserInterface::moveToNextTurret() {
    try {
        std::string userParameters;
        std::getline(std::cin, userParameters);
        std::vector<NorvenTurret> listOfTurrets = this->service.getAllTurretsInRepository();
        if(listOfTurrets.size() == 0) {
            std::cout<<"No turrets added!\n";
            return;
        }
        int position = this->service.getCurrentIndexInListOfTurrets();
        std::cout<<listOfTurrets[position]<<"\n";
        //std::cout<<listOfTurrets[position].toString()<<"\n";
        this->service.moveToNextTurret();
    } catch (std::exception&){
        std::cout<<"Operation not allowed if not in mode B! :( \n";
    }
}

void UserInterface::saveTurret() {
    try {
        std::string userParameters;
        std::getline(std::cin, userParameters);
        userParameters = userParameters.substr(1);

        bool statusOfSave = this->service.saveTurret(userParameters);
        if(!statusOfSave)
            std::cout<< "Turret is not in the list or turret already saved :(\n";
    } catch (std::exception& ){
        std::cout<<"Operation not allowed if not in mode B! :( \n";
    }
}

void UserInterface::printListOfTurretsWithAGivenSizeAndAtLeastAGivenNumberOfParts(std::string userParameters) {
    try {

        int inputSeparateParts;
        std::string inputSize;

        std::vector<std::string> separatedParameters = separateUserParameters(userParameters, (char &) ", ");
        inputSize = separatedParameters[0].substr(1);
        inputSeparateParts = std::stoi(separatedParameters[1]);

        std::vector<NorvenTurret> listOfTurrets = this->service.getListOfTurretsWithAGivenSizeAndAtLeastAGivenNumberOfParts(inputSize, inputSeparateParts);
        for(auto& turret: listOfTurrets)
            std::cout<<turret<<"\n";

    } catch (std::exception&){
        std::cout<<"Operation not allowed if not in mode B! :( \n";
    }

}

void UserInterface::updateFile() {
    std::string fileName;
    std::getline(std::cin, fileName);
    fileName = fileName.substr(1);

    std::ofstream newFile{fileName, std::ios::out};

    std::string currentFileName = this->service.getFileName();

    if(currentFileName!="") {
        std::vector<NorvenTurret> listOfTurrets = this->service.getAllTurretsInRepository();
        for (auto &turret:listOfTurrets)
            newFile << turret;
    }
    this->service.updateFile(fileName);
    newFile.close();
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
            addTurret();
        else if (inputCommand == "delete")
            removeTurret();
        else if (inputCommand == "update")
            updateTurret();
        else if (inputCommand == "list") {
            std::string userParameters;
            std::getline(std::cin, userParameters);
            if (userParameters == "")
                printExistingTurrets();
            else
                printListOfTurretsWithAGivenSizeAndAtLeastAGivenNumberOfParts(userParameters);
        }
        else if (inputCommand == "next")
            moveToNextTurret();
        else if (inputCommand == "save")
            saveTurret();
        else if (inputCommand == "mylist")
            printSavedTurrets();
        else if (inputCommand == "fileLocation")
            this->updateFile();
        else
            std::cout<<"Invalid command\n";
    }
}
// /Users/anamaria/Desktop/ass7test/test.csv