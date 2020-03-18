//
// Created by Ana Maria on 14/03/2020.
//

#include "repository.h"
#include <stdlib.h>


Repository* createRepository(int capacity){
    Repository* repository = (Repository*)malloc(sizeof(Repository));
    repository->arrayOfGears = createDynamicArray(capacity);
    return repository;
}

void destroyGearArray(DynamicArray* arrayOfGears){
   for(int i =0; i < getSizeOfDynamicArray(arrayOfGears); i++)
       destroyGear(arrayOfGears->elements[i]);
}

void destroyRepository(Repository* repository){
    destroyGearArray(repository->arrayOfGears);
    destroyDynamicArray(&(repository->arrayOfGears));
    free(repository);
}


int searchForGear(Repository* repository, int catalogueNumber){
    Gear* currentGear;
    for(int i=0; i < getSizeOfDynamicArray(repository->arrayOfGears); i++){
        currentGear = getElement(repository->arrayOfGears, i);
        if(currentGear->catalogueNumber == catalogueNumber)
            return i;
    }
    return -1;
}

int addGear(Repository* repository, Gear* gearItem){
    if(searchForGear(repository, getCatalogueNumber(gearItem)) != -1) {
        destroyGear(gearItem);
        return -1;
    }

    appendToDynamicArray(repository->arrayOfGears, gearItem);
    //appendArrayOfGearsToHistoryOfArrays(repository);
    return 1;
}

int removeGear(Repository* repository, int catalogueNumber){
    if(searchForGear(repository, catalogueNumber) == -1) {
        //destroyGear(gearItem);
        return -1;
    }

    int indexOfGear = searchForGear(repository, catalogueNumber);
    deleteFromDynamicArray(repository->arrayOfGears, indexOfGear);
    //appendArrayOfGearsToHistoryOfArrays(repository);
    return 1;
}

int updateGear(Repository* repository, int catalogueNumber, char* state, char* type, double value){
    if(searchForGear(repository, catalogueNumber) == -1) {
        //destroyGear(gearItem);
        return -1;
    }
    int indexOfGear = searchForGear(repository, catalogueNumber);
    updateFromDynamicArray(repository->arrayOfGears, indexOfGear, createItemOfTypeGear(catalogueNumber, state, type, value));
    //appendArrayOfGearsToHistoryOfArrays(repository);
    return 1;
}


DynamicArray* getCopyOfArrayOfGears(DynamicArray* dynamicArray)
{
    DynamicArray* transitionListOfMaterials = createDynamicArray(getSizeOfDynamicArray(dynamicArray));
    Gear* gearToBeAppended;
    Gear* gearToCheck;
    for (int i = 0; i < getSizeOfDynamicArray(dynamicArray); i++) {
        gearToCheck = getElement(dynamicArray, i);
        gearToBeAppended = createItemOfTypeGear(gearToCheck->catalogueNumber, gearToCheck->state, gearToCheck->type, gearToCheck->value);
        appendToDynamicArray(transitionListOfMaterials, gearToBeAppended);
    }
    return transitionListOfMaterials;
}

int getNumberOfGears(Repository* repository){
    return getSizeOfDynamicArray(repository->arrayOfGears);
}

void makeNewRepository(Repository* repository){
    repository->arrayOfGears = createDynamicArray(INITIAL_CAPACITY);
}

void changeArrayOfGears(Repository * currentRepository, DynamicArray* newArrayOfGears){
       currentRepository->arrayOfGears = newArrayOfGears;
}

DynamicArray* getArrayOfGears(Repository* repository){
    return repository->arrayOfGears;
}
