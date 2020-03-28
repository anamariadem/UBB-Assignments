//
// Created by Ana Maria on 27/03/2020.
//

#include "UnitTests.h"

void UnitTests::AddToDynamicVector_ValidInput_AddsToVector() {
    DynamicVector<int> v1{ 2 };
    v1.addToDynamicVector(10);
    v1.addToDynamicVector(20);
    assert(v1.getSizeOfVector() == 2);
}

void UnitTests::RemoveFromDynamicVector_ValidInput_RemovesFromVector() {
    DynamicVector<int> v1{ 2 };
    v1.addToDynamicVector(10);
    v1.addToDynamicVector(20);
    int position = 0;
    v1.deleteFromDynamicVector(position);
    assert(v1.getSizeOfVector() == 1);
}

void UnitTests::UpdateFromDynamicVector_ValidInput_UpdatesFromVector() {
    DynamicVector<int> v1{ 2 };
    v1.addToDynamicVector(10);
    v1.addToDynamicVector(20);
    int position = 0;
    v1.updateElementInDynamicArray(position, 30);
    assert(v1[0] == 30);
}

void UnitTests::DynamicVectorIteratorBegin_ValidInput_IteratesThroughVector() {
    DynamicVector<int> v1{ 2 };
    v1.addToDynamicVector(10);
    v1.addToDynamicVector(20);
    DynamicVector<int>::iterator it = v1.begin();
    assert(*it == 10);
}

void UnitTests::DynamicVectorIterator_ValidInput_IteratesThroughVector() {
    DynamicVector<int> v1{ 2 };
    v1.addToDynamicVector(10);
    v1.addToDynamicVector(20);
    DynamicVector<int>::iterator it = v1.begin();
    ++it;
    assert(*it == 20);
}

void UnitTests::testDynamicVector() {
    AddToDynamicVector_ValidInput_AddsToVector();
    RemoveFromDynamicVector_ValidInput_RemovesFromVector();
    UpdateFromDynamicVector_ValidInput_UpdatesFromVector();
    DynamicVectorIteratorBegin_ValidInput_IteratesThroughVector();
    DynamicVectorIterator_ValidInput_IteratesThroughVector();
}

void UnitTests::GetLocationOfTurret_ValidInput_ReturnsLocation(){
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    assert(turret.getLocationOfTurret() == "south-west");
}
void UnitTests::GetSizeOfTurret_ValidInput_ReturnsSize(){
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    assert(turret.getSizeOfTurret() == "medium");
}
void UnitTests::GetAuraLevelOfTurret_ValidInput_ReturnsAuraLevel(){
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    assert(turret.getAuraLevelOfTurret() == 500);
}
void UnitTests::GetNumberOfSeparatePartsOfTurret_ValidInput_ReturnsSeparateParts(){
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    assert(turret.getNumberOfSeparatePartsOfTurret() == 3030);
}
void UnitTests::GetVisionOfTurret_ValidInput_ReturnsVision(){
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    assert(turret.getVisionOfTurret() == "stone tower");
}

void UnitTests::SetSizeOfTurret_ValidInput_SetsSize(){
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    std::string newSize = "large";
    turret.setSizeOfTurret(newSize);
    assert(turret.getSizeOfTurret() == "large");
}
void UnitTests::SetAuraLevelOfTurret_ValidInput_SetsAuraLevel(){
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    turret.setAuraLevelOfTurret(654);
    assert(turret.getAuraLevelOfTurret() == 654);
}
void UnitTests::SetNumberOfSeparatePartsOfTurret_ValidInput_SetsSeparateParts(){
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    turret.setNumberOfSeparatePartsOfTurret(3040);
    assert(turret.getNumberOfSeparatePartsOfTurret() == 3040);
}
void UnitTests::SetVisionOfTurret_ValidInput_SetsVision(){
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    std::string newVision = "wood tower";
    turret.setVisionOfTurret(newVision);
    assert(turret.getVisionOfTurret() == "wood tower");
}

void UnitTests::testDomain(){
    GetLocationOfTurret_ValidInput_ReturnsLocation();
    GetSizeOfTurret_ValidInput_ReturnsSize();
    GetAuraLevelOfTurret_ValidInput_ReturnsAuraLevel();
    GetNumberOfSeparatePartsOfTurret_ValidInput_ReturnsSeparateParts();
    GetVisionOfTurret_ValidInput_ReturnsVision();
    SetSizeOfTurret_ValidInput_SetsSize();
    SetAuraLevelOfTurret_ValidInput_SetsAuraLevel();
    SetNumberOfSeparatePartsOfTurret_ValidInput_SetsSeparateParts();
    SetVisionOfTurret_ValidInput_SetsVision();
}

void UnitTests::AddTurret_ValidInput_AddsTurret(){
    Repository repository = Repository();
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    bool statusOfAdd = repository.addTurretToRepository(turret);
    assert(statusOfAdd == SUCCESS);
}
void UnitTests::AddTurret_DuplicateLocation_ReturnsError(){
    Repository repository = Repository();
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    repository.addTurretToRepository(turret);
    bool statusOfAdd = repository.addTurretToRepository(turret);
    assert(statusOfAdd == FAIL);
}
void UnitTests::RemoveTurret_ValidInput_RemovesTurret(){
    Repository repository = Repository();
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    repository.addTurretToRepository(turret);
    std::string  currentLocation = turret.getLocationOfTurret();
    bool statusOfRemove = repository.removeTurretFromRepository(currentLocation);
    assert(statusOfRemove == SUCCESS);
}
void UnitTests::RemoveTurret_NonexistentTurret_ReturnsError(){
    Repository repository = Repository();
    std::string currentLocation = "south-west";
    bool statusOfRemove = repository.removeTurretFromRepository(currentLocation);
    assert(statusOfRemove == FAIL);
}
void UnitTests::UpdateTurret_ValidInput_UpdatesTurret(){
    Repository repository = Repository();
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    repository.addTurretToRepository(turret);
    std::string currentLocation = turret.getLocationOfTurret();
    std::string newSize = "large";
    int newAuraLevel = 600;
    int newNumberOfSEparateParts = 3038;
    std::string newVision = "tower";
    bool statusOfUpdate = repository.updateTurretFromRepository(currentLocation, newSize, newAuraLevel, newNumberOfSEparateParts, newVision);
    assert(statusOfUpdate == SUCCESS);
}
void UnitTests::UpdateTurret_NonexistentTurret_ReturnsError(){
    Repository repository = Repository();
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    std::string currentLocation = turret.getLocationOfTurret();
    std::string newSize = "large";
    int newAuraLevel = 600;
    int newNumberOfSEparateParts = 3038;
    std::string newVision = "tower";
    bool statusOfUpdate = repository.updateTurretFromRepository(currentLocation, newSize, newAuraLevel, newNumberOfSEparateParts, newVision);
    assert(statusOfUpdate == FAIL);
}

void UnitTests::MoveToNextTurret_IncreasesTheIndex() {
    Repository repository = Repository();
    NorvenTurret turretOne = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    NorvenTurret turretTwo{ "north-west", "large", 560, 3400, "wood tower"};
    repository.addTurretToRepository(turretOne);
    repository.addTurretToRepository(turretTwo);
    repository.moveToNextTurret();

    assert(repository.getCurrentIndexInListOfTurrets() == 1);
}

void UnitTests::MoveToTheNextTurret_ResetsIndexToZero() {
    Repository repository = Repository();
    NorvenTurret turretOne = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    NorvenTurret turretTwo{ "north-west", "large", 560, 3400, "wood tower"};
    repository.addTurretToRepository(turretOne);
    repository.addTurretToRepository(turretTwo);
    repository.moveToNextTurret();
    repository.moveToNextTurret();

    assert(repository.getCurrentIndexInListOfTurrets() == 0);
}

void UnitTests::SaveTurret_ValidInput_SavesTheTurret() {
    Repository repository = Repository();
    NorvenTurret turretOne = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    NorvenTurret turretTwo{ "north-west", "large", 560, 3400, "wood tower"};
    repository.addTurretToRepository(turretOne);
    repository.addTurretToRepository(turretTwo);

    bool statusOfSave = repository.saveTurret("south-west");
    assert(statusOfSave == SUCCESS);
}

void UnitTests::SaveTurret_TurretAlreadySaved_ReturnsError() {
    Repository repository = Repository();
    NorvenTurret turretOne = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    NorvenTurret turretTwo{ "north-west", "large", 560, 3400, "wood tower"};
    repository.addTurretToRepository(turretOne);
    repository.addTurretToRepository(turretTwo);

    repository.saveTurret("south-west");
    bool statusOfSave = repository.saveTurret("south-west");
    assert(statusOfSave == FAIL);
}

void UnitTests::testRepository(){
    AddTurret_ValidInput_AddsTurret();
    AddTurret_DuplicateLocation_ReturnsError();
    RemoveTurret_ValidInput_RemovesTurret();
    RemoveTurret_NonexistentTurret_ReturnsError();
    UpdateTurret_ValidInput_UpdatesTurret();
    UpdateTurret_NonexistentTurret_ReturnsError();
    MoveToNextTurret_IncreasesTheIndex();
    MoveToTheNextTurret_ResetsIndexToZero();
    SaveTurret_ValidInput_SavesTheTurret();
    SaveTurret_TurretAlreadySaved_ReturnsError();
}

void UnitTests::AddTurretService_ValidInput_AddsTurret(){
    Repository repository = Repository();
    Service service = Service(repository);
    std::string mode = "A";
    service.setApplicationMode(mode);
    std::string currentLocation = "south-west";
    std::string size = "large";
    int auraLevel = 600;
    int numberOfSeparateParts = 3038;
    std::string vision = "tower";
    bool statusOfAdd = service.addTurret(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
    assert(statusOfAdd == SUCCESS);
}
void UnitTests::AddTurretService_DuplicateLocation_ReturnsError(){
    Repository repository = Repository();
    Service service = Service(repository);
    std::string mode = "A";
    service.setApplicationMode(mode);
    std::string currentLocation = "south-west";
    std::string size = "large";
    int auraLevel = 600;
    int numberOfSeparateParts = 3038;
    std::string vision = "tower";
    service.addTurret(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
    std::string anotherSize = "small";
    int anotherAuraLevel = 346;
    int statusOfAdd = service.addTurret(currentLocation, anotherSize, anotherAuraLevel, numberOfSeparateParts, vision);
    assert(statusOfAdd == FAIL);
}

void UnitTests::AddTurretService_InvalidMode_ThrowsError(){
    Repository repository = Repository();
    Service service = Service(repository);
    try {
        std::string currentLocation = "south-west";
        std::string size = "large";
        int auraLevel = 600;
        int numberOfSeparateParts = 3038;
        std::string vision = "tower";
        service.addTurret(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
        assert(false);
    }catch (std::exception&){
        assert(true);
    }

}

void UnitTests::RemoveTurretService_ValidInput_RemovesTurret(){
    Repository repository = Repository();
    Service service = Service(repository);
    std::string mode = "A";
    service.setApplicationMode(mode);
    std::string currentLocation = "south-west";
    std::string size = "large";
    int auraLevel = 600;
    int numberOfSeparateParts = 3038;
    std::string vision = "tower";
    service.addTurret(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
    bool statusOfRemove = service.removeTurret(currentLocation);
    assert(statusOfRemove == SUCCESS);
}
void UnitTests::RemoveTurretService_NonexistentTurret_ReturnsError(){
    Repository repository = Repository();
    Service service = Service(repository);
    std::string mode = "A";
    service.setApplicationMode(mode);
    std::string currentLocation = "south-west";
    bool statusOfRemove = service.removeTurret(currentLocation);
    assert(statusOfRemove == FAIL);
}

void UnitTests::RemoveTurretService_InvalidMode_ThrowsError(){
    Repository repository = Repository();
    Service service = Service(repository);
    try {
        std::string currentLocation = "south-west";
        std::string size = "large";
        int auraLevel = 600;
        int numberOfSeparateParts = 3038;
        std::string vision = "tower";
        service.addTurret(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
        service.removeTurret(currentLocation);
        assert(false);
    }catch (std::exception&){
        assert(true);
    }

}
void UnitTests::UpdateTurretService_ValidInput_UpdatesTurret(){
    Repository repository = Repository();
    Service service = Service(repository);
    std::string mode = "A";
    service.setApplicationMode(mode);
    std::string currentLocation = "south-west";
    std::string size = "large";
    int auraLevel = 600;
    int numberOfSeparateParts = 3038;
    std::string vision = "tower";
    service.addTurret(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
    std::string anotherSize = "small";
    int anotherAuraLevel = 346;
    int statusOfUpdate = service.updateTurret(currentLocation, anotherSize, anotherAuraLevel, numberOfSeparateParts, vision);
    assert(statusOfUpdate == SUCCESS);
}
void UnitTests::UpdateTurretService_NonexistentTurret_ReturnsError(){
    Repository repository = Repository();
    Service service = Service(repository);
    std::string mode = "A";
    service.setApplicationMode(mode);
    std::string currentLocation = "south-west";
    std::string size = "large";
    int auraLevel = 600;
    int numberOfSeparateParts = 3038;
    std::string vision = "tower";
    bool statusOfUpdate = service.updateTurret(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
    assert(statusOfUpdate == FAIL);
}

void UnitTests::UpdateTurretService_InvalidMode_ThrowsError(){
    Repository repository = Repository();
    Service service = Service(repository);
    try {
        std::string currentLocation = "south-west";
        std::string size = "large";
        int auraLevel = 600;
        int numberOfSeparateParts = 3038;
        std::string vision = "tower";
        service.addTurret(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
        std::string anotherSize = "small";
        int anotherAuraLevel = 346;
        service.updateTurret(currentLocation, anotherSize, anotherAuraLevel, numberOfSeparateParts, vision);
        assert(false);
    }catch (std::exception&){
        assert(true);
    }
}

void UnitTests::MoveToTheNextTurret_InvalidMode_ThrowsError() {
    Repository repository = Repository();
    Service service = Service(repository);
    try {
        std::string currentLocation = "south-west";
        std::string size = "large";
        int auraLevel = 600;
        int numberOfSeparateParts = 3038;
        std::string vision = "tower";
        service.addTurret(currentLocation, size, auraLevel, numberOfSeparateParts, vision);

        service.moveToNextTurret();

        assert(false);
    } catch (std::exception&){
        assert(true);
    }

}

void UnitTests::SaveTurret_InvalidMode_ThrowsError() {
    Repository repository = Repository();
    Service service = Service(repository);
    try {
        std::string currentLocation = "south-west";
        std::string size = "large";
        int auraLevel = 600;
        int numberOfSeparateParts = 3038;
        std::string vision = "tower";
        service.addTurret(currentLocation, size, auraLevel, numberOfSeparateParts, vision);

        service.saveTurret(currentLocation);
        assert(false);
    } catch (std::exception&){
        assert(true);
    }
}

void UnitTests::testService(){
    AddTurretService_ValidInput_AddsTurret();
    AddTurretService_DuplicateLocation_ReturnsError();
    AddTurretService_InvalidMode_ThrowsError();
    RemoveTurretService_ValidInput_RemovesTurret();
    RemoveTurretService_NonexistentTurret_ReturnsError();
    RemoveTurretService_InvalidMode_ThrowsError();
    UpdateTurretService_ValidInput_UpdatesTurret();
    UpdateTurretService_NonexistentTurret_ReturnsError();
    UpdateTurretService_InvalidMode_ThrowsError();
    MoveToTheNextTurret_InvalidMode_ThrowsError();
    SaveTurret_InvalidMode_ThrowsError();
}

void UnitTests::RunAllTests() {
    testDynamicVector();
    testRepository();
    testService();
    testDomain();
}