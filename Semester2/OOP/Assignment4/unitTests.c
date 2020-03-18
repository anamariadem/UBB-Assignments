//
// Created by Ana Maria on 14/03/2020.
//

#include "unitTests.h"
#include <assert.h>
#include <string.h>


void DomainTest_GetCatalogueNumber(){
    Gear* gear = createItemOfTypeGear(1,"used","wheel", 45.08);
    assert(getCatalogueNumber(gear) == 1);
    destroyGear(gear);
}
void DomainTest_GetStateOfGear(){
    Gear* gear = createItemOfTypeGear(1,"used","wheel", 45.08);
    assert(strcmp(getStateOfGearItem(gear), "used") ==0);
    destroyGear(gear);
}
void DomainTest_GetTypeOfGear(){
    Gear* gear = createItemOfTypeGear(1,"used","wheel", 45.08);
    assert(strcmp(getTypeOfGearItem(gear), "wheel") ==0);
    destroyGear(gear);
}
void DomainTest_GetValueOfGear(){
    Gear* gear = createItemOfTypeGear(1,"used","wheel", 45.08);
    assert(getValueOfGearItem(gear) == 45.08);
    destroyGear(gear);
}
void testDomain(){
    DomainTest_GetCatalogueNumber();
    DomainTest_GetStateOfGear();
    DomainTest_GetTypeOfGear();
    DomainTest_GetValueOfGear();
}

void RepositoryTest_AddGear_ValidInput_AddedToList(){
    Repository* repository = createRepository(5);
    Gear* gearItem = createItemOfTypeGear(23, "used", "cogwheel", 45.08);
    //int statusOfAdd =
    addGear(repository, gearItem);
    assert(getSizeOfDynamicArray(repository->arrayOfGears) == 1);
    //assert(statusOfAdd == 1);
    destroyRepository(repository);
}

void RepositoryTest_AddGear_Duplicated_ReturnError(){
    Repository* repository = createRepository(5);
    Gear* gearItem = createItemOfTypeGear(23, "used", "cogwheel", 45.08);
    addGear(repository, gearItem);
    int statusOfSecondAdd = addGear(repository, gearItem);
    //assert(getSizeOfDynamicArray(repository->arrayOfGears) == 1);
    assert(statusOfSecondAdd == -1);
    //destroyRepository(repository);
}

void RepositoryTest_RemoveGear_ValidInput_RemovesFromList(){
    Repository* repository = createRepository(5);
    Gear* gearItem = createItemOfTypeGear(23, "used", "cogwheel", 45.08);
    Gear* anotherGearItem = createItemOfTypeGear(25, "new", "wheel", 76.88);
    addGear(repository, gearItem);
    addGear(repository, anotherGearItem);
    //assert(getSizeOfDynamicArray(repository->arrayOfGears) == 2);
    removeGear(repository, getCatalogueNumber(gearItem));
    assert(getSizeOfDynamicArray(repository->arrayOfGears) == 1);
    destroyRepository(repository);
}

void RepositoryTest_RemoveGear_InvalidInput_ReturnsError(){
    Repository* repository = createRepository(5);
    Gear* gearItem = createItemOfTypeGear(23, "used", "cogwheel", 45.08);
    addGear(repository, gearItem);
    int statusOfRemove = removeGear(repository, 25);
    assert(statusOfRemove == -1);
    destroyRepository(repository);
}

void RepositoryTest_UpdateGear_ValidInput_UpdatesGear(){
    Repository* repository = createRepository(5);
    Gear* anotherGearItem = createItemOfTypeGear(25, "new", "wheel", 76.88);
    addGear(repository, anotherGearItem);
    int status = updateGear(repository, 25, "semi-used", "wheel2", 76);
    //assert(status == 1);
    //assert(strcmp(getStateOfGearItem(getElement(repository->arrayOfGears,0)), "semi-used") == 0);
    assert(strcmp(getTypeOfGearItem(getElement(repository->arrayOfGears,0)), "wheel2") == 0);
    //assert(getValueOfGearItem(getElement(repository->arrayOfGears,0)) == 76);
    destroyRepository(repository);
}

void RepositoryTest_UpdateGear_InvalidInput_ReturnsError(){
    Repository* repository = createRepository(5);
    Gear* anotherGearItem = createItemOfTypeGear(25, "new", "wheel", 76.88);
    addGear(repository, anotherGearItem);
    int status = updateGear(repository, 35, "semi-used", "wheel2", 76);
    assert(status == -1);
    destroyRepository(repository);
}

void testRepository() {
    RepositoryTest_AddGear_ValidInput_AddedToList();
    RepositoryTest_AddGear_Duplicated_ReturnError();
    RepositoryTest_RemoveGear_ValidInput_RemovesFromList();
    RepositoryTest_RemoveGear_InvalidInput_ReturnsError();
    RepositoryTest_UpdateGear_ValidInput_UpdatesGear();
    RepositoryTest_UpdateGear_InvalidInput_ReturnsError();
}

void ServiceTest_AddGear_ValidInput_AddedToList(){
    Repository* repository = createRepository(3);
    Service* service = createService(repository);
    int catalogueNumber = 1;
    char state[25] = "used";
    char type[25] = "wheel";
    double value = 23.45;
    int statusOfAdd = addGearService(service, catalogueNumber, state, type, value);
    assert(statusOfAdd == 1);
    destroyService(service);
    destroyRepository(repository);
}
void ServiceTest_AddGear_Duplicated_ReturnError(){
    Repository* repository = createRepository(3);
    Service* service = createService(repository);
    int catalogueNumber = 1, secondCatalogueNumber = 1;
    char state[25] = "used", secondState[25] = "new";
    char type[25] = "wheel", secondType[25] = "wheel";
    double value = 23.45, secondValue = 736.4;
    addGearService(service, catalogueNumber, state, type, value);
    int statusOfAdd = addGearService(service, secondCatalogueNumber, secondState, secondType, secondValue);
    assert(statusOfAdd == -1);
    destroyService(service);
    destroyRepository(repository);
}
void ServiceTest_RemoveGear_ValidInput_RemovesFromList(){
    Repository* repository = createRepository(3);
    Service* service = createService(repository);
    int catalogueNumber = 1;
    char state[25] = "used";
    char type[25] = "wheel";
    double value = 23.45;
    addGearService(service, catalogueNumber, state, type, value);
    int statusOfRemove = removeGearService(service, catalogueNumber);
    assert(statusOfRemove == 1);
    destroyService(service);
    destroyRepository(repository);
}
void ServiceTest_RemoveGear_InvalidInput_ReturnsError(){
    Repository* repository = createRepository(3);
    Service* service = createService(repository);
    int statusOfRemove = removeGearService(service, 1);
    assert(statusOfRemove == -1);
    destroyService(service);
    destroyRepository(repository);
}
void ServiceTest_UpdateGear_ValidInput_UpdatesGear(){
    Repository* repository = createRepository(3);
    Service* service = createService(repository);
    int catalogueNumber = 1;
    char state[25] = "used";
    char type[25] = "wheel";
    double value = 23.45;
    addGearService(service, catalogueNumber, state, type, value);
    int statusOfUpdate = updateGearService(service, catalogueNumber, "new", "wheel", 3476);
    assert(statusOfUpdate == 1);
    destroyService(service);
    destroyRepository(repository);
}
void ServiceTest_UpdateGear_InvalidInput_ReturnsError(){
    Repository* repository = createRepository(3);
    Service* service = createService(repository);
    int statusOfUpdate = updateGearService(service, 1, "new", "wheel", 23.3);
    assert(statusOfUpdate == -1);
    destroyService(service);
    destroyRepository(repository);
}
void ServiceTest_UndoOperation_Valid_DoesTheUndo(){
    Repository* repository = createRepository(5);
    Service* service =  createService(repository);
    addGearService(service, 23, "used", "cogwheel", 45.08);
    addGearService(service, 25, "new", "wheel", 76.08);
    int statusOfUndo = undoTheLastOperation(service);
    assert(statusOfUndo == 1);
    destroyService(service);
    destroyRepository(repository);
}
void ServiceTest_UndoOperation_Invalid_ReturnsError(){
    Repository* repository = createRepository(5);
    Service* service =  createService(repository);
    int statusOfUndo = undoTheLastOperation(service);
    assert(statusOfUndo == -1);
    destroyService(service);
    destroyRepository(repository);
}
void ServiceTest_RedoOperation_Valid_DoesTheRedo(){
    Repository* repository = createRepository(5);
    Service* service =createService(repository);
    addGearService(service, 23, "used", "cogwheel", 45.08);
    addGearService(service, 25, "new", "wheel", 76.08);
    undoTheLastOperation(service);
    int statusOfRedo = redoTheLastOperation(service);
    assert(statusOfRedo == 1);
    destroyService(service);
    destroyRepository(repository);
}
void ServiceTest_RedoOperation_Invalid_ReturnsError(){
    Repository* repository = createRepository(5);
    Service* service =createService(repository);
    int statusOfRedo = redoTheLastOperation(service);
    assert(statusOfRedo == -1);
    destroyService(service);
    destroyRepository(repository);
}
void testService(){
    ServiceTest_AddGear_ValidInput_AddedToList();
    ServiceTest_AddGear_Duplicated_ReturnError();
    ServiceTest_RemoveGear_ValidInput_RemovesFromList();
    ServiceTest_RemoveGear_InvalidInput_ReturnsError();
    ServiceTest_UpdateGear_ValidInput_UpdatesGear();
    ServiceTest_UpdateGear_InvalidInput_ReturnsError();
    ServiceTest_UndoOperation_Valid_DoesTheUndo();
    ServiceTest_UndoOperation_Invalid_ReturnsError();
    ServiceTest_RedoOperation_Valid_DoesTheRedo();
    ServiceTest_RedoOperation_Invalid_ReturnsError();
}

void RunAllTests(){
    testDomain();
    testRepository();
    testService();
}