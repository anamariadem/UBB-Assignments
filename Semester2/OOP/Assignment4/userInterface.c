//
// Created by Ana Maria on 14/03/2020.
//

#include "userInterface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

UserInterface* createUserInterface(Service* service){
    UserInterface* ui = (UserInterface*)malloc(sizeof(UserInterface));
    if(ui == NULL)
        return NULL;
    ui->service = service;
    return ui;
}

void destroyUserInterface(UserInterface* ui){
    free(ui);
}

void readUserCommand(UserInterface* ui, char command[50], int* catalogueNumber, char state[20], char type[20], double* value){
    char userInput[50], separatedString[50];
    char* pointerToSeparateString;
    unsigned int lenghtOfString = strlen(userInput);
    printf("Command: ");
    fgets(userInput, sizeof(userInput), stdin);

    pointerToSeparateString = strtok(userInput, " ");
    strcpy(command, pointerToSeparateString);
    //printf("%s", command);

    if(strcmp(command, "add") == 0){
        pointerToSeparateString = strtok(NULL, " ");
        strcpy(separatedString, pointerToSeparateString);
        *catalogueNumber = atoi(separatedString);

        pointerToSeparateString = strtok(NULL, ", ");
        strcpy(state, pointerToSeparateString);

        pointerToSeparateString = strtok(NULL, ", ");
        strcpy(type, pointerToSeparateString);

        pointerToSeparateString = strtok(NULL, ", ");
        strcpy(separatedString, pointerToSeparateString);
        *value = atof(separatedString);

    } else if (strcmp(command, "delete") == 0){
        pointerToSeparateString = strtok(NULL, " ");
        strcpy(separatedString, pointerToSeparateString);
        *catalogueNumber = atoi(separatedString);

    } else if (strcmp(command, "list") == 0 && lenghtOfString!=4 ){
        pointerToSeparateString = strtok(NULL, " ");
        char digits[12] = {"0123456789"};
        int nrDigits =0;
        for(int i =0; i<strlen(digits);i++){
            if(strchr(pointerToSeparateString, digits[i]) != NULL)
                nrDigits++;
        }
        if(nrDigits == 0) {
            strcat(command, ";");
            strcat(command, pointerToSeparateString);
        } else {
            strcat(command, ":");
            strcat(command, pointerToSeparateString);
        }
    } else if (strcmp(command, "update") == 0){
        pointerToSeparateString = strtok(NULL, " ");
        strcpy(separatedString, pointerToSeparateString);
        *catalogueNumber = atoi(separatedString);

        pointerToSeparateString = strtok(NULL, ", ");
        strcpy(state, pointerToSeparateString);

        pointerToSeparateString = strtok(NULL, ", ");
        strcpy(type, pointerToSeparateString);

        pointerToSeparateString = strtok(NULL, ", ");
        strcpy(separatedString, pointerToSeparateString);
        *value = atof(separatedString);
    }

}

void addGearUserInterface(UserInterface* ui, int inputCatalogueNumber, char* inputState, char* inputType, double inputValue){
    int statusOfAdd = addGearService(ui->service, inputCatalogueNumber, inputState, inputType, inputValue);
    if (statusOfAdd == -1)
        printf("No!\n");
}

void removeGearUserInterface(UserInterface* ui, int inputCatalogueNumber){
    int statusOfRemove = removeGearService(ui->service, inputCatalogueNumber);
    if(statusOfRemove == -1)
        printf("No!\n");
}

void updateGearUserInterface(UserInterface* ui, int catalogueNumber, char* newState, char* newType, double newValue){
    int statusofUpdate = updateGearService(ui->service, catalogueNumber, newState, newType, newValue);
    if(statusofUpdate == -1)
        printf("No!\n");
}

void undoUserInterface(UserInterface* ui){
    int undoStatus = undoTheLastOperation(ui->service);
    if (undoStatus == -1)
        printf("No more undo!\n");
}

void redoUserInterface(UserInterface* ui){
    int redoStatus = redoTheLastOperation(ui->service);
    if (redoStatus == -1)
        printf("No more redo!\n");
}

void filterGears(UserInterface* ui, char* command){
    char* pointerToSeparateCommand;
    char inputForFilter[20];
    pointerToSeparateCommand = strtok(command, ";");
    pointerToSeparateCommand = strtok(NULL, ";");
    strcpy(inputForFilter, pointerToSeparateCommand);

    DynamicArray* filteredGears = filterGearsByStateType(ui->service, inputForFilter);
    int lenghtOfFilteredGearsArray = getSizeOfDynamicArray(filteredGears);
    for(int i=0;i<lenghtOfFilteredGearsArray;i++){
        Gear* currentGear = getElement(filteredGears, i);
        printf("Catalogue number: %d\n", currentGear->catalogueNumber);
        printf("State: %s\n", currentGear->state);
        printf("Type: %s\n", currentGear->type);
        printf("Value: %g\n", currentGear->value);
        printf("**********************\n");
    }
}

void printExistingGears(UserInterface* ui){
    DynamicArray* arrayOfExistingGears = getArrayOfGearsService(ui->service);
    int numberOfExistingGears = getNumberOfGearsService(ui->service);

    for(int i=0;i<numberOfExistingGears;i++){
        Gear* currentGear = getElement(arrayOfExistingGears, i);
        printf("Catalogue number: %d\n", currentGear->catalogueNumber);
        printf("State: %s\n", currentGear->state);
        printf("Type: %s\n", currentGear->type);
        printf("Value: %g\n", currentGear->value);
        printf("**********************\n");
    }
}

void gearsWithLessThanValue(UserInterface* ui, char* command){
    DynamicArray* arrayOfExistingGears = getArrayOfGearsService(ui->service);
    int numberOfExistingGears = getNumberOfGearsService(ui->service);
    char* pointerToSeparateCommand;
    char stringBeforeBeingConvertedToInt[50];
    double maximalValueFromUser;
    pointerToSeparateCommand = strtok(command, ":");
    pointerToSeparateCommand = strtok(NULL, ":");
    strcpy(stringBeforeBeingConvertedToInt, pointerToSeparateCommand);
    maximalValueFromUser = atof(stringBeforeBeingConvertedToInt);

    printf("%g\n", maximalValueFromUser);
    sortAscendingByState(ui->service);
    for(int i=0;i<numberOfExistingGears;i++){
        Gear* currentGear = getElement(arrayOfExistingGears, i);
        if(currentGear->value <= maximalValueFromUser) {
            printf("Catalogue number: %d\n", currentGear->catalogueNumber);
            printf("State: %s\n", currentGear->state);
            printf("Type: %s\n", currentGear->type);
            printf("Value: %g\n", currentGear->value);
            printf("**********************\n");
        }
    }
}

void sortDescendingByCatalogueNumberUserInterface(UserInterface* ui){
    sortDescendingByCatalogueNumber(ui->service, compareGearsByCatalogueNumber);
}

void startApp(UserInterface* ui){
    char command[50], inputState[50], inputType[50];
    int catalogueNumber;
    double inputValue;
    int stillRunning = 0;

    while(stillRunning == 0){
        readUserCommand(ui, command, &catalogueNumber, inputState, inputType, &inputValue);

        if (strcmp(command, "exit\n") == 0)
            stillRunning = 1;
        else if (strcmp(command, "add") == 0)
            addGearUserInterface(ui, catalogueNumber, inputState, inputType, inputValue);
        else if (strcmp(command, "delete") == 0)
            removeGearUserInterface(ui, catalogueNumber);
        else if (strcmp(command, "update") == 0)
            updateGearUserInterface(ui, catalogueNumber, inputState, inputType, inputValue);
        else if (strcmp(command, "list\n") == 0)
            printExistingGears(ui);
        else if (strstr(command, "list;") != NULL)
            filterGears(ui, command);
        else if (strstr(command, "list:") != NULL)
            gearsWithLessThanValue(ui, command);
        else if (strcmp(command, "undo\n") == 0)
            undoUserInterface(ui);
        else if (strcmp(command, "redo\n") == 0)
            redoUserInterface(ui);
        else if (strcmp(command, "sort\n") == 0)
            sortDescendingByCatalogueNumberUserInterface(ui);
        else
            printf("Wrong command\n");
    }
}