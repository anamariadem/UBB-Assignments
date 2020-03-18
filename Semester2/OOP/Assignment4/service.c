//
// Created by Ana Maria on 14/03/2020.
//
#include "service.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Service* createService(Repository* repository){
    Service* service = (Service*)malloc(sizeof(Service));
    if(service == NULL)
        return NULL;
    service->repository = repository;
    service->historyOfArraysOfGears = createDynamicArray(INITIAL_CAPACITY);
    service->currentHistoryIndex = -1;
    return service;
}

void destroyService(Service* service){
    //destroyRepository(service->repository);
    destroyHistoryOfRepositories(service->historyOfArraysOfGears);
    destroyDynamicArray(&(service->historyOfArraysOfGears));
    free(service);
}

void destroyHistoryOfRepositories(DynamicArray* history){
    DynamicArray* currentArrayOfGears;
    for(int i=0; i < getSizeOfDynamicArray(history); i++){
        currentArrayOfGears = (DynamicArray*)getElement(history, i);
        destroyGearArray(currentArrayOfGears);
        destroyDynamicArray(&currentArrayOfGears);
    }
}

int addGearService(Service* service, int catalogueNumber, char* state, char* type, double value){
    Gear* gearToAdd = createItemOfTypeGear(catalogueNumber, state, type, value);

    int statusOfAdd = addGear(service->repository, gearToAdd);
    if(statusOfAdd != -1){
        appendArrayOfGearsToHistoryOfArrays(service);
    }
    return statusOfAdd;
}

int removeGearService(Service* service, int catalogueNumber){

    int statusOfRemove = removeGear(service->repository, catalogueNumber);
    if(statusOfRemove != -1)
        appendArrayOfGearsToHistoryOfArrays(service);
    return statusOfRemove;
}

int updateGearService(Service* service, int catalogueNumber, char* state, char* type, double value){
    int statusOfUpdate = updateGear(service->repository, catalogueNumber, state, type, value);
    if(statusOfUpdate != -1)
        appendArrayOfGearsToHistoryOfArrays(service);
    return statusOfUpdate;
}

void appendArrayOfGearsToHistoryOfArrays(Service* service){
    DynamicArray* currentArrayOfGears = getArrayOfGearsService(service);
    DynamicArray* copyOfCurrentArrayOfGears = getCopyOfArrayOfGears(currentArrayOfGears);
    appendToDynamicArray(service->historyOfArraysOfGears, copyOfCurrentArrayOfGears);
    service->currentHistoryIndex ++;
}

int undoTheLastOperation(Service* service){
    if(service->currentHistoryIndex == -1)
        return -1;

    DynamicArray* currentArrayOfGears = getArrayOfGearsService(service);
    destroyGearArray(currentArrayOfGears);
    destroyDynamicArray(&currentArrayOfGears);

    if(service->currentHistoryIndex == 0)
        makeNewRepository(service->repository);
    else{
        DynamicArray* previousArrayOfGears = (DynamicArray *) getElement(service->historyOfArraysOfGears, service->currentHistoryIndex - 1);
        changeArrayOfGears(service->repository, getCopyOfArrayOfGears(previousArrayOfGears));
    }
    service->currentHistoryIndex--;
    return 1;
}

int redoTheLastOperation(Service* service){
    if(service->currentHistoryIndex == getSizeOfDynamicArray(service->historyOfArraysOfGears) - 1)
        return -1;
    DynamicArray* currentArrayOfGears = getArrayOfGearsService(service);
    destroyGearArray(currentArrayOfGears);
    destroyDynamicArray(&currentArrayOfGears);

    DynamicArray* newArrayOfGears = getCopyOfArrayOfGears((DynamicArray*)getElement(service->historyOfArraysOfGears, service->currentHistoryIndex + 1));
    changeArrayOfGears(service->repository, newArrayOfGears);
    service->currentHistoryIndex++;
    return 1;
}

int getNumberOfGearsService(Service* service){
    return getNumberOfGears(service->repository);
}

DynamicArray* getArrayOfGearsService(Service* service){
    return getArrayOfGears(service->repository);
}


void sortAscendingByState(Service* service){
    DynamicArray* arrayOfExistingGears = getArrayOfGears(service->repository);
    int numberOfExistingGears = getNumberOfGears(service->repository);
    for(int i=0; i<numberOfExistingGears-1; i++)
        for(int j=i+1; j< numberOfExistingGears;j++){
            Gear* firstGearToCompare = getElement(arrayOfExistingGears, i);
            Gear* secondGearToCompare = getElement(arrayOfExistingGears, j);
            if(strcmp(getStateOfGearItem(firstGearToCompare), getStateOfGearItem(secondGearToCompare)) >0){
                swapTwoGears(firstGearToCompare, secondGearToCompare);
            }
        }
}

int compareGearsByCatalogueNumber(Gear* firstGearToCompare, Gear* secondGearToCompare){
    if(getCatalogueNumber(firstGearToCompare) <= getCatalogueNumber(secondGearToCompare))
        return 1;
    return 0;
}

void sortDescendingByCatalogueNumber(Service* service, int(*compareGears)(Gear*, Gear*)){
    int indexInArray = 0;
    DynamicArray* arrayOfExistingGears = getArrayOfGears(service->repository);
    int numberOfExistingGears = getNumberOfGears(service->repository);
    while(indexInArray < numberOfExistingGears){
        Gear* firstGearToCompare = getElement(arrayOfExistingGears, indexInArray);
        Gear* secondGearToCompare = getElement(arrayOfExistingGears, indexInArray-1);
        if(indexInArray == 0 || compareGears(firstGearToCompare, secondGearToCompare) == 1)
            indexInArray ++;
        else{
            swapTwoGears(firstGearToCompare, secondGearToCompare);
            indexInArray --;
        }
    }
}

DynamicArray* filterGearsByStateType(Service* service, char* userFilterInput){
    DynamicArray* arrayOfExistingGears = getArrayOfGearsService(service);
    int numberOfExistingGears = getNumberOfGearsService(service);

    DynamicArray* arrayOfFilteredGears = createDynamicArray(INITIAL_CAPACITY);

    for(int i=0;i<numberOfExistingGears;i++) {
        Gear* currentGear = getElement(arrayOfExistingGears, i);
        char currentState[30], currentType[30];
        strcpy(currentState, currentGear->state);
        strcat(currentState, "\n");
        strcpy(currentType, currentGear->type);
        strcat(currentType, "\n");
        if(strcmp(currentState, userFilterInput) == 0 )
            appendToDynamicArray(arrayOfFilteredGears, currentGear);
        else if (strcmp(currentType, userFilterInput) == 0)
           appendToDynamicArray(arrayOfFilteredGears, currentGear);

    }
    return arrayOfFilteredGears;
}