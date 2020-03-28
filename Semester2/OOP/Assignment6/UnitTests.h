//
// Created by Ana Maria on 27/03/2020.
//

#ifndef ASSIGNMENT6_UNITTESTS_H
#define ASSIGNMENT6_UNITTESTS_H

#define SUCCESS true
#define FAIL false

#include <cassert>
#include "Domain.h"
#include "DynamicVector.h"
#include "Repository.h"
#include "Service.h"

class UnitTests {
private:
    static void AddToDynamicVector_ValidInput_AddsToVector();
    static void RemoveFromDynamicVector_ValidInput_RemovesFromVector();
    static void UpdateFromDynamicVector_ValidInput_UpdatesFromVector();
    static void DynamicVectorIteratorBegin_ValidInput_IteratesThroughVector();
    static void DynamicVectorIterator_ValidInput_IteratesThroughVector();

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
    void MoveToNextTurret_IncreasesTheIndex();
    void MoveToTheNextTurret_ResetsIndexToZero();
    void SaveTurret_ValidInput_SavesTheTurret();
    void SaveTurret_TurretAlreadySaved_ReturnsError();

    void AddTurretService_ValidInput_AddsTurret();
    void AddTurretService_DuplicateLocation_ReturnsError();
    void AddTurretService_InvalidMode_ThrowsError();
    void RemoveTurretService_ValidInput_RemovesTurret();
    void RemoveTurretService_NonexistentTurret_ReturnsError();
    void RemoveTurretService_InvalidMode_ThrowsError();
    void UpdateTurretService_ValidInput_UpdatesTurret();
    void UpdateTurretService_NonexistentTurret_ReturnsError();
    void UpdateTurretService_InvalidMode_ThrowsError();
    void MoveToTheNextTurret_InvalidMode_ThrowsError();
    void SaveTurret_InvalidMode_ThrowsError();

    void testDynamicVector();
    void testDomain();
    void testRepository();
    void testService();

public:
    void RunAllTests();
};


#endif //ASSIGNMENT6_UNITTESTS_H
