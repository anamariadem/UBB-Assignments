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
 returns: the index of it -> gear was found
        -1 -> gear not found
 */
int searchForGear(Repository* repository, int catalogueNumber);
int addGear(Repository* repository, Gear gearItem);
int removeGear(Repository* repository, int catalogueNumber);
int updateGear(Repository* repository, int, char*, char*, double);
Gear* getListOfExistingGears(Repository* repository);
int getNumberOfExistingGears(Repository* repository);
void testRepository();

#endif //ASSIGNMENT3_REPOSITORY_H
