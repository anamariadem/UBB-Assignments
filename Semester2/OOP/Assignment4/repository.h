//
// Created by Ana Maria on 14/03/2020.
//

#ifndef ASSIGNMENT4_REPOSITORY_H
#define ASSIGNMENT4_REPOSITORY_H

#define INITIAL_CAPACITY 2
#include "dinamicArray.h"
#include "gear.h"
typedef struct {
    DynamicArray* arrayOfGears;
}Repository;

/*
 creates a repository with a given capacity
 capacity - the initial capacity of the repository
 */
Repository* createRepository(int capacity);

/*
 destroys an array of gears
 dynamicArray - the dynamic array to be destroyed
 */
void destroyGearArray(DynamicArray* dynamicArray);
/*
 destroys the historyOfArraysOfGears of repositories
 dynamicArray - the historyOfArraysOfGears to be destroyed
 */
//void destroyHistoryOfRepositories(DynamicArray* dynamicArray);
void destroyRepository(Repository*);


/*
 searches for a gear item in the array of existing gears
 repository - the given repository to search through
 catalogueNumber - the given catalogue number of the gear item to  be searched
 returns: the index of it -> gear was found
        -1 -> gear not found
 */
int searchForGear(Repository* repository, int catalogueNumber);
/*
 adds a new gear to the given repository
 repository - the given repository to add to
 gearItem - the gear to add
 returns 0 -> gear was successfully added
        -1 -> gear already existed so it was not readded
 */
int addGear(Repository* repository, Gear* gearItem);
/*
 removes a gear from the given repository
 repository - the given repository to remove from
 catalogueNumber - the given catalogue number of the gear to be removed
 returns 0 -> gear was successfully removed from repository
        -1 -> gear does not exist
 */
int removeGear(Repository* repository, int catalogueNumber);
/*
 updates a gear from the given repository
 repository - the given repository to update
 catalogueNumber - the given catalogue number of the gear to be updated
 newState - the new state of the gear
 newType - the new type of the gear
 newValue - the new value of the gear
 */
int updateGear(Repository* repository, int, char*, char*, double);

/*
 creates a new repository, in case it was deleted by the undo
 */
void makeNewRepository(Repository*);

/*
 changes the array of gears in case of undo or redo
 repository -> the current repository
 dynamic array -> the new array of gears
 */
void changeArrayOfGears(Repository *,DynamicArray*);

/*
 creates a copy of the array of gears
 */
DynamicArray* getCopyOfArrayOfGears(DynamicArray*);

int getNumberOfGears(Repository*);
DynamicArray* getArrayOfGears(Repository*);


#endif //ASSIGNMENT4_REPOSITORY_H
