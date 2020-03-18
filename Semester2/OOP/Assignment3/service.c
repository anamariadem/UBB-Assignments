//
// Created by Ana Maria on 05/03/2020.
//

#include "service.h"
#include <stdlib.h>
#include <assert.h>

Service* createService(Repository* repository){
    Service* service = (Service*)malloc(sizeof(Service));
    if(service == NULL)
        return NULL;
    service->repository = repository;
    return service;
}

void destroyService(Service* service){
    free(service);
}

int addGearService(Service* service, int catalogueNumber, char* state, char* type, double value){
    Gear gear = createItemOfTypeGear(catalogueNumber, state, type, value);
    return addGear(service->repository, gear);
}

int removeGearService(Service* service, int catalogueNumber){
    //Gear gear = createItemOfTypeGear(catalogueNumber, state, type, value);
    return removeGear(service->repository, catalogueNumber);
}

int updateGearService(Service* service, int catalogueNumber, char* state, char* type, double value){
    return updateGear(service->repository, catalogueNumber, state, type, value);
}

Gear* getListOfExistingGearsService(Service* service){
    return getListOfExistingGears(service->repository);
}

int getNumberOfExistingGearsService(Service* service){
    return getNumberOfExistingGears(service->repository);
}

void testAddService(){
    Repository* repository= createRepository();
    Service* service = createService(repository);
    int statusOfAdd = addGearService(service,23, "used", "cogwheel", 65.07);
    assert(statusOfAdd == 0);
    destroyService(service);
    destroyRepository(repository);
}

void testRemoveService(){
    Repository* repository= createRepository();
    Service* service = createService(repository);
    addGearService(service,23, "used", "cogwheel", 65.07);
    int statusOfRemove = removeGearService(service, 23);
    assert(statusOfRemove == 0);
    destroyService(service);
    destroyRepository(repository);
}
void testService(){
    testAddService();
    testRemoveService();
}