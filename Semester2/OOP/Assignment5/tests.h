//
// Created by Ana Maria on 19/03/2020.
//

#ifndef ASSIGNMENT5_TESTS_H
#define ASSIGNMENT5_TESTS_H
#define SUCCESS true
#define FAIL false

#include "DynamicVector.h"
#include "Repository.h"
#include "Service.h"

void GetLocationOfTurret_ValidInput_ReturnsLocation();
void GetSizeOfTurret_ValidInput_ReturnsSize();
void GetAuraLevelOfTurret_ValidInput_ReturnsAuraLevel();
void GetNumberOfSeparatePartsOfTurret_ValidInput_ReturnsSeparateParts();
void GetVisionOfTurret_ValidInput_ReturnsVision();

void SetSizeOfTurret_ValidInput_SetsSize();
void SetAuraLevelOfTurret_ValidInput_SetsAuraLevel();
void SetNumberOfSeparatePartsOfTurret_ValidInput_SetsSeparateParts();
void SetVisionOfTurret_ValidInput_SetsVision();

void AddTurret_ValidInput_AddsTurret();
void AddTurret_DuplicateLocation_ReturnsError();
void RemoveTurret_ValidInput_RemovesTurret();
void RemoveTurret_NonexistentTurret_ReturnsError();
void UpdateTurret_ValidInput_UpdatesTurret();
void UpdateTurret_NonexistentTurret_ReturnsError();

void AddTurretService_ValidInput_AddsTurret();
void AddTurretService_DuplicateLocation_ReturnsError();
void AddTurretService_InvalidMode_ThrowsError();
void RemoveTurretService_ValidInput_RemovesTurret();
void RemoveTurretService_NonexistentTurret_ReturnsError();
void RemoveTurretService_InvalidMode_ThrowsError();
void UpdateTurretService_ValidInput_UpdatesTurret();
void UpdateTurretService_NonexistentTurret_ReturnsError();
void UpdateTurretService_InvalidMode_ThrowsError();

void testDomain();
void testRepository();
void testService();
void RunAllTests();
#endif //ASSIGNMENT5_TESTS_H
