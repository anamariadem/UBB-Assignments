//
// Created by Ana Maria on 04/03/2020.
//

#ifndef ASSIGNMENT3_REPOSITORY_H
#define ASSIGNMENT3_REPOSITORY_H

#include "gear.h"

typedef struct {
    Gear arrayOfGears[500];
    int lenght;
}Repository;

Repository* createRepository();
void destroyRepository(Repository* repository);
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
int addGear(Repository* repository, Gear gearItem);
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
 returns the list of gears from the given repository
 */
Gear* getListOfExistingGears(Repository* repository);
/*
 returns the number of existing gears
 */

int getNumberOfExistingGears(Repository* repository);

void testAddValid();
void testAddInvalid();
void testRemoveValid();
void testRemoveInvalid();
void testUpdateValid();
void testUpdateInvalid();
void testRepository();

#endif //ASSIGNMENT3_REPOSITORY_H
