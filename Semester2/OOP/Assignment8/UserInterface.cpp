//
// Created by Ana Maria on 10/04/2020.
//

#include "UserInterface.h"
#include <iostream>


std::vector<std::string> UserInterface::separateUserParameters(std::string & command, char & separator) {
    std::string separatedPartOfString="";
    std::vector<std::string> separatedUserCommand;

    for(auto stringIterator: command){
        if(stringIterator != separator)
            separatedPartOfString += stringIterator;

        if(stringIterator == separator && !separatedPartOfString.empty()){
            separatedUserCommand.push_back(separatedPartOfString);
            separatedPartOfString = "";
        }
    }
    if(!separatedPartOfString.empty())
        separatedUserCommand.push_back(separatedPartOfString);
    return separatedUserCommand;
}

void UserInterface::setApplicationMode() {
    try {
        std::string userParameters;
        std::getline(std::cin, userParameters);
        userParameters = userParameters.substr(1);
        this->service.setApplicationMode(userParameters);
    }catch (MyException& exception){
        std::cout<<exception.what();
    }
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
        this->service.addTurret(inputLocation, inputSize, inputAuraLevel, inputSeparateParts, inputVision);

    } catch (std::invalid_argument&) {
        std::cout<<"Please provide the correct type for parameters!\n";
    }catch (MyException& exception){
            std::cout<<exception.what();
        }
}


void UserInterface::removeTurret() {
    try {
        std::string userParameters;
        std::getline(std::cin, userParameters);
        userParameters = userParameters.substr(1);

        this->service.removeTurret(userParameters);
    }catch (MyException& exception){
        std::cout<<exception.what();
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

        this->service.updateTurret(inputLocation, inputSize, inputAuraLevel, inputSeparateParts, inputVision);

    } catch (std::invalid_argument&) {
        std::cout<<"Please provide the correct type for parameters!\n";
    }catch (MyException& exception){
        std::cout<<exception.what();
    }

}
void UserInterface::printExistingTurrets() {
    try {
        std::vector<NorvenTurret> listOfTurrets = this->service.getAllTurretsInRepository();

        for (auto &turret: listOfTurrets)
            std::cout << turret << "\n";
    }catch (MyException& exception){
        std::cout<<exception.what();
    }
}

void UserInterface::printSavedTurrets() {
    try {
        std::vector<NorvenTurret> listOfSavedTurrets = this->service.getAllSavedTurrets();

        for (auto &turret: listOfSavedTurrets)
            std::cout << turret << "\n";
    }catch (MyException& exception){
        std::cout<<exception.what();
    }
}

void UserInterface::openFileWithCorrectApplication(){
    std::string fileName;
    std::getline(std::cin, fileName);
    fileName = fileName.substr(1);
    
    system(("\"" + fileName + "\"").c_str());
    //system(("open " + "\" "+ fileName + "\"").c_str());

    /*auto indexOfLastDot = fileName.find_last_of('.');
    std::string fileExtension = fileName.substr(indexOfLastDot);

    if (fileExtension == ".txt" or fileExtension == ".csv") {
        std::string command = "notepad.exe ";
        command += fileName;
        system(command.c_str());
    }
   else if (fileExtension == ".html") {
        std::string quotes = "\"";
        system((quotes + fileName + quotes).c_str());
   }*/
 }

void UserInterface::moveToNextTurret() {
    try {
        std::string userParameters;
        std::getline(std::cin, userParameters);
        std::vector<NorvenTurret> listOfTurrets = this->service.getAllTurretsInRepository();
        if(listOfTurrets.empty()) {
            std::cout<<"No turrets added!\n";
            return;
        }
        int position = this->service.getCurrentIndexInListOfTurrets();
        std::cout<<listOfTurrets[position]<<"\n";
        //std::cout<<listOfTurrets[position].toString()<<"\n";
        this->service.moveToNextTurret();
    } catch (MyException& exception){
        std::cout<<exception.what();
    }
}

void UserInterface::saveTurret() {
    try {
        std::string userParameters;
        std::getline(std::cin, userParameters);
        userParameters = userParameters.substr(1);

        this->service.saveTurret(userParameters);
    } catch (MyException& exception){
        std::cout<<exception.what();
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

    } catch (std::invalid_argument&) {
        std::cout<<"Please provide the correct type for parameters!\n";
    }catch (MyException& exception){
        std::cout<<exception.what();
    }

}

void UserInterface::updateAllTurretsFile() {
    std::string fileName;
    std::getline(std::cin, fileName);
    fileName = fileName.substr(1);

    std::ofstream newFile{fileName, std::ios::app};


    /*std::string currentFileName = this->service.getFileName();

    if(!currentFileName.empty()) {
        //std::ofstream newFile{fileName, std::ios::app};
        std::vector<NorvenTurret> listOfTurrets = this->service.getAllTurretsInRepository();
        for (auto &turret:listOfTurrets)
            newFile << turret;
        //newFile.close();
    }*/
    this->service.updateAllTurretsFile(fileName);
    newFile.close();
}

void UserInterface::updateSavedTurretsFile() {
    std::string fileName;
    std::getline(std::cin, fileName);
    fileName = fileName.substr(1);

    std::ofstream newFile{fileName, std::ios::app};
    this->service.updateSavedTurretsFile(fileName);
    newFile.close();
}

void UserInterface::startApplication(){
    std::string inputCommand;

    while(1){
        std::cout<<"Command: ";
        inputCommand = "";
        std::cin>>inputCommand;
        if (inputCommand == "exit") {
            break;
        }
        else if (inputCommand == "mode")
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
            if (userParameters.empty())
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
            this->updateAllTurretsFile();
        else if (inputCommand == "mylistLocation")
            this->updateSavedTurretsFile();
        else if (inputCommand == "open")
            this->openFileWithCorrectApplication();
        else
            std::cout<<"Invalid command\n";
    }
}
// /Users/anamaria/Desktop/ass7test/test.csv