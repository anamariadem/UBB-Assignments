//
// Created by Ana Maria on 04/03/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "repository.h"
#include <assert.h>

Repository* createRepository(){
    Repository* repo = (Repository*)malloc(sizeof(Repository));
    repo->lenght = 0;
    return repo;
}

void destroyRepository(Repository* repository){
    free(repository);
}


int searchForGear(Repository* repository, int catalogueNumber){
    for(int i=0; i < repository->lenght; i++){
        if(catalogueNumber == getCatalogueNumber(repository->arrayOfGears[i]))
            return i;
    }
    return -1;
}

int addGear(Repository* repository, Gear gearItem){
    if(searchForGear(repository, getCatalogueNumber(gearItem)) != -1)
        return -1;
    repository->arrayOfGears[repository->lenght++] = gearItem;
    return 0;
}

int removeGear(Repository* repository, int catalogueNumber){
    int indexOfGear = searchForGear(repository, catalogueNumber);
    if(indexOfGear == -1)
        return -1;
    for(int i = indexOfGear; i < repository->lenght - 1;i++ )
        repository->arrayOfGears[i] = repository->arrayOfGears[i+1];
    repository->lenght-- ;
    return 0;
}

int updateGear(Repository* repository, int catalogueNumber, char* newState, char* newType, double newValue){
    int indexOfGear = searchForGear(repository, catalogueNumber);
    if (indexOfGear == -1)
        return -1;
    setStateOfGearItem(&(repository->arrayOfGears[indexOfGear]), newState);
    setTypeOfGearItem(&(repository->arrayOfGears[indexOfGear]),newType);
    setValueOfGearItem(&(repository->arrayOfGears[indexOfGear]), newValue);
    return 0;
}

Gear* getListOfExistingGears(Repository* repository){
    return repository->arrayOfGears;
}

int getNumberOfExistingGears(Repository* repository){
    return repository->lenght;
}

void testRepository(){
    Repository* repository = createRepository();
    Gear gearItem = createItemOfTypeGear(23, "used", "cogwheel", 45.08);
    Gear anotherGearItem = createItemOfTypeGear(25, "new", "wheel", 76.88);
    addGear(repository, gearItem);
    addGear(repository, anotherGearItem);
    assert(repository->lenght == 2);
    removeGear(repository, getCatalogueNumber(gearItem));
    assert(repository->lenght == 1);

    int status = updateGear(repository, 25, "semi-used", "wheel2", 76);
    assert(status == 0);
    //printf("%s", getStateOfGearItem(&repository->arrayOfGears[0]));
    assert(strcmp(getStateOfGearItem(&repository->arrayOfGears[0]), "semi-used") == 0);
    assert(strcmp(getTypeOfGearItem(&repository->arrayOfGears[0]), "wheel2") == 0);
    assert(getValueOfGearItem(repository->arrayOfGears[0]) == 76);
    destroyRepository(repository);
}