//
// Created by Ana Maria on 05/03/2020.
//

#ifndef ASSIGNMENT3_SERVICE_H
#define ASSIGNMENT3_SERVICE_H

#include "repository.h"

typedef struct {
    Repository* repository;
}Service;

Service* createService(Repository* repository);
void destroyService(Service* service);
int addGearService(Service* service, int catalogueNumber, char* state, char* type, double value);
int removeGearService(Service* service, int catalogueNumber);
int updateGearService(Service* service, int catalogueNumber, char* state, char* type, double value);
Gear* getListOfExistingGearsService(Service* service);
int getNumberOfExistingGearsService(Service* service);
void testService();

#endif //ASSIGNMENT3_SERVICE_H
