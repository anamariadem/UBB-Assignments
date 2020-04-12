//
// Created by Ana Maria on 10/04/2020.
//

#ifndef ASSIGNMENT7_UNITTESTS_H
#define ASSIGNMENT7_UNITTESTS_H

#define SUCCESS true
#define FAIL false

#include "Turret.h"
#include "Repository.h"
#include "FileRepository.h"
#include "Service.h"

class UnitTests {
private:
    static void GetLocationOfTurret_ValidInput_ReturnsLocation();
    static void GetSizeOfTurret_ValidInput_ReturnsSize();
    static void GetAuraLevelOfTurret_ValidInput_ReturnsAuraLevel();
    static void GetNumberOfSeparatePartsOfTurret_ValidInput_ReturnsSeparateParts();
    static void GetVisionOfTurret_ValidInput_ReturnsVision();

    static void SetSizeOfTurret_ValidInput_SetsSize();
    static void SetAuraLevelOfTurret_ValidInput_SetsAuraLevel();
    static void SetNumberOfSeparatePartsOfTurret_ValidInput_SetsSeparateParts();
    static void SetVisionOfTurret_ValidInput_SetsVision();
    static void Ostream_ValidInput_PrintsToFile();
    static void testDomain();

    static void AddTurret_ValidInput_AddsTurret();
    static void AddTurret_DuplicateLocation_ReturnsError();
    static void RemoveTurret_ValidInput_RemovesTurret();
    static void RemoveTurret_NonexistentTurret_ReturnsError();
    static void UpdateTurret_ValidInput_UpdatesTurret();
    static void UpdateTurret_NonexistentTurret_ReturnsError();
    static void MoveToNextTurret_IncreasesTheIndex();
    static void MoveToTheNextTurret_ResetsIndexToZero();
    static void SaveTurret_ValidInput_SavesTheTurret();
    static void SaveTurret_TurretAlreadySaved_ReturnsError();
    static void SaveTurret_NonExistentTurret_ReturnsError();
    static void DeleteTurret_ValidInput_DeleteFromSavedAndList();
    static void UpdateFile_ValidInput_UpdatesFile();

    static void testRepository();

    static void UpdateFileService_ValidInput_UpdatesFile();
    static void SetApplicationMode_InvalidInput_ReturnsError();
    static void AddTurretService_ValidInput_AddsTurret();
    static void AddTurretService_DuplicateLocation_ReturnsError();
    static void AddTurretService_InvalidMode_ThrowsError();
    static void RemoveTurretService_ValidInput_RemovesTurret();
    static void RemoveTurretService_NonexistentTurret_ReturnsError();
    static void RemoveTurretService_InvalidMode_ThrowsError();
    static void UpdateTurretService_ValidInput_UpdatesTurret();
    static void UpdateTurretService_NonexistentTurret_ReturnsError();
    static void UpdateTurretService_InvalidMode_ThrowsError();
    static void MoveToTheNextTurret_InvalidMode_ThrowsError();
    static void MoveToNextTurretService_ValidInput_MovesToNextTurret();
    static void SaveTurret_InvalidMode_ThrowsError();
    static void SaveTurretService_ValidInput_SavesTurret();
    static void getListOfTurretsWithAGivenSizeAndAtLeastAGivenNumberOfPartsService_ValidInput();
    static void getListOfTurretsWithAGivenSizeAndAtLeastAGivenNumberOfPartsService_InvalidMode();

    static void testService();
public:
    void testAll();
};


#endif //ASSIGNMENT7_UNITTESTS_H
