//
// Created by Ana Maria on 14/03/2020.
//

#ifndef ASSIGNMENT4_UNITTESTS_H
#define ASSIGNMENT4_UNITTESTS_H

#include "service.h"

void DomainTest_GetCatalogueNumber();
void DomainTest_GetStateOfGear();
void DomainTest_GetTypeOfGear();
void DomainTest_GetValueOfGear();
void testDomain();

void RepositoryTest_AddGear_ValidInput_AddedToList();
void RepositoryTest_AddGear_Duplicated_ReturnError();
void RepositoryTest_RemoveGear_ValidInput_RemovesFromList();
void RepositoryTest_RemoveGear_InvalidInput_ReturnsError();
void RepositoryTest_UpdateGear_ValidInput_UpdatesGear();
void RepositoryTest_UpdateGear_InvalidInput_ReturnsError();
void testRepository();

void ServiceTest_AddGear_ValidInput_AddedToList();
void ServiceTest_AddGear_Duplicated_ReturnError();
void ServiceTest_RemoveGear_ValidInput_RemovesFromList();
void ServiceTest_RemoveGear_InvalidInput_ReturnsError();
void ServiceTest_UpdateGear_ValidInput_UpdatesGear();
void ServiceTest_UpdateGear_InvalidInput_ReturnsError();
void ServiceTest_UndoOperation_Valid_DoesTheUndo();
void ServiceTest_UndoOperation_Invalid_ReturnsError();
void ServiceTest_RedoOperation_Valid_DoesTheRedo();
void ServiceTest_RedoOperation_Invalid_ReturnsError();
void testService();

void RunAllTests();
#endif //ASSIGNMENT4_UNITTESTS_H
