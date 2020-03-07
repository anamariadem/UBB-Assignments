//
// Created by Ana Maria on 05/03/2020.
//

#ifndef ASSIGNMENT3_UI_H
#define ASSIGNMENT3_UI_H

#include "service.h"

typedef struct {
    Service* service;
}UserInterface;

UserInterface* createUserInterface(Service* service);
void destroyUserInterface(UserInterface* ui);
void addGearUserInterface(UserInterface* ui, int inputCatalogueNumber, char* inputState, char* inputType, double inputValue);
void removeGearUserInterface(UserInterface* ui, int inputCatalogueNumber);
void updateGearUserInterface(UserInterface* ui, int inputCatalogueNumber, char* inputState, char* inputType, double inputValue);
void printExistingGears(UserInterface* ui);
void listTheTypesOfExistingGears(UserInterface* ui);
void listTheStatesOfExistingGears(UserInterface* ui);
void listTheValuesOfExistingGears(UserInterface* ui);
void readCommand(UserInterface* ui, char command[50], int* catalogueNumber, char state[20], char type[20], double* value);
void start(UserInterface* ui);

#endif //ASSIGNMENT3_UI_H
