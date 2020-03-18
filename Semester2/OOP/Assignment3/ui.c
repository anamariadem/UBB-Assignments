//
// Created by Ana Maria on 05/03/2020.
//

#include "ui.h"
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

void readCommand(UserInterface* ui, char command[50], int* catalogueNumber, char state[20], char type[20], double* value){
    char userInput[50], separatedString[50];
    char* pointerToSeparateString;
    unsigned int lenghtOfString = strlen(userInput);
    printf("Command: ");
    fgets(userInput, sizeof(userInput), stdin);
    //gets(command);
    //printf("You wrote: %s\n", userInput);

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

        //printf("Command: %s\n", command);
        //printf("%d\n",  *catalogueNumber);
        //printf("%s\n", state);
        //printf("%s\n", type);
        //printf("%lf", *value);
    } else if (strcmp(command, "delete") == 0){
        pointerToSeparateString = strtok(NULL, " ");
        strcpy(separatedString, pointerToSeparateString);
        *catalogueNumber = atoi(separatedString);

        //printf("Command: %s\n", command);
        //printf("%d\n",  *catalogueNumber);
    } else if (strcmp(command, "list") == 0 && lenghtOfString!=4 ){
        pointerToSeparateString = strtok(NULL, " ");
        strcat(command, ";");
        strcat(command, pointerToSeparateString);
        //printf("Command: %s\n", command);
    } else if (strcmp(command, "update") == 0){
        pointerToSeparateString = strtok(NULL, " ");
        strcpy(separatedString, pointerToSeparateString);
        *catalogueNumber = atoi(separatedString);

        pointerToSeparateString = strtok(NULL, " ");
        strcpy(state, pointerToSeparateString);

        pointerToSeparateString = strtok(NULL, " ");
        strcpy(type, pointerToSeparateString);

        pointerToSeparateString = strtok(NULL, " ");
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

void printExistingGears(UserInterface* ui){
    Gear* arrayOfExistingGears = getListOfExistingGearsService(ui->service);
    int numberOfExistingGears = getNumberOfExistingGearsService(ui->service);

    for(int i=0;i<numberOfExistingGears;i++){
        Gear currentGear = arrayOfExistingGears[i];
        printf("Catalogue number: %d\n", currentGear.catalogueNumber);
        printf("State: %s\n", currentGear.state);
        printf("Type: %s\n", currentGear.type);
        printf("Value: %lf\n", currentGear.value);
        printf("**********************\n");
    }
}

void filterGears(UserInterface* ui, char* command){
    Gear* arrayOfExistingGears = getListOfExistingGearsService(ui->service);
    int numberOfExistingGears = getNumberOfExistingGearsService(ui->service);
    char* pointerToSeparateCommand;
    char inputForFilter[20];
    pointerToSeparateCommand = strtok(command, ";");
    pointerToSeparateCommand = strtok(NULL, ";");
    strcpy(inputForFilter, pointerToSeparateCommand);
    for(int i=0;i<numberOfExistingGears;i++) {
        Gear currentGear = arrayOfExistingGears[i];
        strcat(currentGear.state, "\n");
        strcat(currentGear.type, "\n");
        if(strcmp(currentGear.state, inputForFilter) == 0){
            printf("Catalogue number: %d\n", currentGear.catalogueNumber);
            printf("State: %s", currentGear.state);
            printf("Type: %s", currentGear.type);
            printf("Value: %lf\n", currentGear.value);
            printf("**********************\n");
        } else if (strcmp(currentGear.type, inputForFilter) == 0){
            printf("Catalogue number: %d\n", currentGear.catalogueNumber);
            printf("State: %s", currentGear.state);
            printf("Type: %s", currentGear.type);
            printf("Value: %lf\n", currentGear.value);
            printf("**********************\n");
        }
    }
}

void listTheTypesOfExistingGears(UserInterface* ui){
    Gear* arrayOfExistingGears = getListOfExistingGearsService(ui->service);
    int numberOfExistingGears = getNumberOfExistingGearsService(ui->service);

    for(int i=0;i<numberOfExistingGears;i++){
        char* currentType = (&arrayOfExistingGears[i])->type;
        printf("Type of gear %d is %s \n", i+1, currentType);
    }
    printf("**********************\n");
}

void listTheStatesOfExistingGears(UserInterface* ui){
    Gear* arrayOfExistingGears = getListOfExistingGearsService(ui->service);
    int numberOfExistingGears = getNumberOfExistingGearsService(ui->service);

    for(int i=0;i<numberOfExistingGears;i++){
        char* currentState = (&arrayOfExistingGears[i])->state;
        printf("State of gear %d is %s \n", i+1, currentState);
    }
    printf("**********************\n");
}

void listTheValuesOfExistingGears(UserInterface* ui){
    Gear* arrayOfExistingGears = getListOfExistingGearsService(ui->service);
    int numberOfExistingGears = getNumberOfExistingGearsService(ui->service);

    for(int i=0;i<numberOfExistingGears;i++){
        double currentValue = arrayOfExistingGears[i].value;
        printf("Value of gear %d is %lf \n", i+1, currentValue);
    }
    printf("**********************\n");
}

void start(UserInterface* ui){
    char command[50], inputState[50], inputType[50];
    int catalogueNumber;
    double inputValue;
    int stillRunning = 0;

    while(stillRunning == 0){
        readCommand(ui, command, &catalogueNumber, inputState, inputType, &inputValue);

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
        else
            printf("Wrong command\n");
    }
    //printf("%d\n",  catalogueNumber);
    //printf("%s\n", inputState);
    //printf("%s\n", inputType);
    //printf("%lf", inputValue);
}

void runTests(){
    testCreateGear();
    testRepository();
    testService();
}