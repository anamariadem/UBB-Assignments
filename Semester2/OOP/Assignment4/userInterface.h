//
// Created by Ana Maria on 14/03/2020.
//

#ifndef ASSIGNMENT4_USERINTERFACE_H
#define ASSIGNMENT4_USERINTERFACE_H
#include "service.h"

typedef struct {
    Service* service;
}UserInterface;

UserInterface* createUserInterface(Service* service);
void destroyUserInterface(UserInterface* ui);
void readUserCommand(UserInterface* ui, char command[50], int* catalogueNumber, char state[20], char type[20], double* value);
void addGearUserInterface(UserInterface* ui, int inputCatalogueNumber, char* inputState, char* inputType, double inputValue);
void removeGearUserInterface(UserInterface* ui, int inputCatalogueNumber);
void updateGearUserInterface(UserInterface* ui, int inputCatalogueNumber, char* inputState, char* inputType, double inputValue);
void printExistingGears(UserInterface* ui);
void filterGears(UserInterface* ui, char* command);
void gearsWithLessThanValue(UserInterface* ui, char* command);
void startApp(UserInterface* ui);
void undoUserInterface(UserInterface* ui);
void redoUserInterface(UserInterface* ui);
void sortDescendingByCatalogueNumberUserInterface(UserInterface* ui);

#endif //ASSIGNMENT4_USERINTERFACE_H
