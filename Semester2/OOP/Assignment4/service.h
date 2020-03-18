//
// Created by Ana Maria on 14/03/2020.
//

#ifndef ASSIGNMENT4_SERVICE_H
#define ASSIGNMENT4_SERVICE_H

#include "repository.h"

typedef struct {
    Repository* repository;
    DynamicArray* historyOfArraysOfGears;
    int currentHistoryIndex;
}Service;

/*
 creates a service for your repository
 repository - the given repository
 */
Service* createService(Repository* repository);
void destroyService(Service* service);
void destroyHistoryOfRepositories(DynamicArray* history);
int addGearService(Service* service, int catalogueNumber, char* state, char* type, double value);
int removeGearService(Service* service, int catalogueNumber);
int updateGearService(Service* service, int catalogueNumber, char* state, char* type, double value);
/*
 undo the last operation
 returns 1 -> operation was successful
        -1 -> no undo-s left
 */
int undoTheLastOperation(Service* service);
/*
 redo the last operation
 returns 1 -> operation was successful
        -1 -> no redo-s left
 */
int redoTheLastOperation(Service* service);

/*
 appends a repository to the historyOfArraysOfGears of repositories
 repository - the repository to be stored in history of repositories
 */
void appendArrayOfGearsToHistoryOfArrays(Service* service);

int getNumberOfGearsService(Service*);
DynamicArray* getArrayOfGearsService(Service*);

/*
 sorts the current array of gears ascending by state
 */
void sortAscendingByState(Service* service);
/*
 sorts the current array of gears descending by state
 */
void sortDescendingByCatalogueNumber(Service* service, int(*compareGearsByCatalogueNumber)(Gear*, Gear*));

int compareGearsByCatalogueNumber(Gear*, Gear*);

DynamicArray* filterGearsByStateType(Service* service, char* userFilterInput);

#endif //ASSIGNMENT4_SERVICE_H
