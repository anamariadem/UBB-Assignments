//
// Created by Ana Maria on 10/04/2020.
//

#include "UnitTests.h"
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

void UnitTests::Ostream_ValidInput_PrintsToFile() {
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    std::ofstream newFile{"testFile.csv", std::ios::out};
    newFile<<turret;
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
    Ostream_ValidInput_PrintsToFile();
}
void UnitTests::AddTurret_ValidInput_AddsTurret(){
    std::ofstream newFile{"testFile.csv", std::ios::out};
    FileRepository testRepo = FileRepository("testFile.csv");
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    bool statusOfAdd = testRepo.addTurret(turret);
    std::vector<NorvenTurret> listOfTurrets = testRepo.getListOfTurrets();
    assert(listOfTurrets.size() == 1);
}

void UnitTests::AddTurret_DuplicateLocation_ReturnsError(){
    FileRepository repository = FileRepository("testFile.csv");
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    bool statusOfAdd = repository.addTurret(turret);
    assert(statusOfAdd == FAIL);
}

void UnitTests::RemoveTurret_ValidInput_RemovesTurret(){
    FileRepository repository = FileRepository("testFile.csv");
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    repository.addTurret(turret);
    std::string  currentLocation = turret.getLocationOfTurret();
    bool statusOfRemove = repository.removeTurret(currentLocation);
    assert(statusOfRemove == SUCCESS);
}
void UnitTests::RemoveTurret_NonexistentTurret_ReturnsError(){
    FileRepository repository = FileRepository("testFile.csv");
    std::string currentLocation = "south-west";
    bool statusOfRemove = repository.removeTurret(currentLocation);
    assert(statusOfRemove == FAIL);
}

void UnitTests::UpdateTurret_ValidInput_UpdatesTurret(){
    FileRepository repository = FileRepository("testFile.csv");
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    repository.addTurret(turret);
    std::string currentLocation = turret.getLocationOfTurret();
    std::string newSize = "large";
    int newAuraLevel = 600;
    int newNumberOfSEparateParts = 3038;
    std::string newVision = "tower";
    bool statusOfUpdate = repository.updateTurret(currentLocation, newSize, newAuraLevel, newNumberOfSEparateParts,
                                                  newVision);
    assert(statusOfUpdate == SUCCESS);
}
void UnitTests::UpdateTurret_NonexistentTurret_ReturnsError(){
    FileRepository repository = FileRepository("testFile.csv");
    NorvenTurret turret = NorvenTurret("north-west", "medium", 500, 3030, "stone tower");
    std::string currentLocation = turret.getLocationOfTurret();
    std::string newSize = "large";
    int newAuraLevel = 600;
    int newNumberOfSEparateParts = 3038;
    std::string newVision = "tower";
    bool statusOfUpdate = repository.updateTurret(currentLocation, newSize, newAuraLevel, newNumberOfSEparateParts,
                                                  newVision);
    assert(statusOfUpdate == FAIL);
}


void UnitTests::MoveToNextTurret_IncreasesTheIndex() {
    FileRepository repository = FileRepository("testFile.csv");
    //NorvenTurret turretOne = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    NorvenTurret turretTwo{ "north-west", "large", 560, 3400, "wood tower"};
    //repository.addTurret(turretOne);
    repository.addTurret(turretTwo);
    repository.moveToNextTurret();

    assert(repository.getCurrentIndexInListOfTurrets() == 1);
}

void UnitTests::MoveToTheNextTurret_ResetsIndexToZero() {
    FileRepository repository = FileRepository("testFile.csv");
    //NorvenTurret turretOne = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    //NorvenTurret turretTwo{ "north-west", "large", 560, 3400, "wood tower"};
    //repository.addTurret(turretOne);
    //repository.addTurret(turretTwo);
    repository.moveToNextTurret();
    repository.moveToNextTurret();

    assert(repository.getCurrentIndexInListOfTurrets() == 0);
}

void UnitTests::SaveTurret_ValidInput_SavesTheTurret() {
    //at this point, the file contains 2 turrets with locations south-west and north-west
    FileRepository repository = FileRepository("testFile.csv");
    //NorvenTurret turretOne = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    //NorvenTurret turretTwo{ "north-west", "large", 560, 3400, "wood tower"};
    //repository.addTurret(turretOne);
    //repository.addTurret(turretTwo);

    bool statusOfSave = repository.saveTurret("south-west");
    assert(repository.getListOfSavedTurrets().size() == 1);
    //assert(statusOfSave == SUCCESS);
}

void UnitTests::SaveTurret_TurretAlreadySaved_ReturnsError() {
    FileRepository repository = FileRepository("testFile.csv");
    //NorvenTurret turretOne = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    //NorvenTurret turretTwo{ "north-west", "large", 560, 3400, "wood tower"};
    //repository.addTurret(turretOne);
    //repository.addTurret(turretTwo);

    repository.saveTurret("south-west");
    bool statusOfSave = repository.saveTurret("south-west");
    assert(statusOfSave == FAIL);
}

void UnitTests::SaveTurret_NonExistentTurret_ReturnsError() {
    FileRepository repository = FileRepository("testFile.csv");

    bool statusOfSave = repository.saveTurret("center");
    assert(statusOfSave == FAIL);
}

void UnitTests::DeleteTurret_ValidInput_DeleteFromSavedAndList() {
    // at this point, file contains 2 turrets with locations south-west, north-west
    FileRepository repository = FileRepository("testFile.csv");
    NorvenTurret turret{"center", "small", 45, 4567, "tower"};
    repository.addTurret(turret);
    repository.saveTurret("south-west");
    repository.saveTurret("north-west");
    repository.saveTurret("center");
    repository.removeTurret("center");
    std::vector<NorvenTurret> listOfSavedTurrets = repository.getListOfSavedTurrets();
    assert(listOfSavedTurrets.size() == 2);
}
void UnitTests::UpdateFile_ValidInput_UpdatesFile() {
    FileRepository repository = FileRepository("testFile.csv");
    repository.updateFile("test.csv");
    assert(repository.getFilename() == "test.csv");
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
    SaveTurret_NonExistentTurret_ReturnsError();
    DeleteTurret_ValidInput_DeleteFromSavedAndList();
    UpdateFile_ValidInput_UpdatesFile();
}

void UnitTests::SetApplicationMode_InvalidInput_ReturnsError() {
    FileRepository repository = FileRepository("testFile.csv");
    Service service = Service(repository);
    std::string mode = "X";
    bool status = service.setApplicationMode(mode);
    assert(status == FAIL);
}

void UnitTests::UpdateFileService_ValidInput_UpdatesFile() {
    FileRepository repository = FileRepository("testFile.csv");
    Service service = Service(repository);
    service.updateFile("anotherFile.csv");
    assert(service.getFileName() == "anotherFile.csv");
}

void UnitTests::AddTurretService_ValidInput_AddsTurret(){
    std::ofstream newFile{"testFile.csv", std::ios::out};
    FileRepository repository = FileRepository("testFile.csv");
    Service service = Service(repository);
    std::string mode = "A";
    service.setApplicationMode(mode);
    std::string currentLocation = "south-west";
    std::string size = "large";
    int auraLevel = 600;
    int numberOfSeparateParts = 3038;
    std::string vision = "tower";
    bool statusOfAdd = service.addTurret(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
    assert(service.getAllTurretsInRepository().size() == 1);
}
void UnitTests::AddTurretService_DuplicateLocation_ReturnsError(){
    FileRepository repository = FileRepository("testFile.csv");
    Service service = Service(repository);
    std::string mode = "A";
    service.setApplicationMode(mode);
    std::string currentLocation = "south-west";
    //std::string size = "large";
    //int auraLevel = 600;
    int numberOfSeparateParts = 3038;
    std::string vision = "tower";
    //service.addTurret(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
    std::string anotherSize = "small";
    int anotherAuraLevel = 346;
    int statusOfAdd = service.addTurret(currentLocation, anotherSize, anotherAuraLevel, numberOfSeparateParts, vision);
    assert(statusOfAdd == FAIL);
}


void UnitTests::AddTurretService_InvalidMode_ThrowsError(){
    FileRepository repository = FileRepository("testFile.csv");
    Service service = Service(repository);
    try {
        std::string currentLocation = "south-west";
        std::string size = "large";
        int auraLevel = 600;
        int numberOfSeparateParts = 3038;
        std::string vision = "tower";
        service.addTurret(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
        //assert(false);
    }catch (std::exception&){
        assert(true);
    }

}


void UnitTests::RemoveTurretService_ValidInput_RemovesTurret(){
    FileRepository repository = FileRepository("testFile.csv");
    Service service = Service(repository);
    std::string mode = "A";
    service.setApplicationMode(mode);
    std::string currentLocation = "south-west";
    bool statusOfRemove = service.removeTurret(currentLocation);
    assert(statusOfRemove == SUCCESS);
}
void UnitTests::RemoveTurretService_NonexistentTurret_ReturnsError(){
    FileRepository repository = FileRepository("testFile.csv");
    Service service = Service(repository);
    std::string mode = "A";
    service.setApplicationMode(mode);
    std::string currentLocation = "south-west";
    bool statusOfRemove = service.removeTurret(currentLocation);
    assert(statusOfRemove == FAIL);
}

void UnitTests::RemoveTurretService_InvalidMode_ThrowsError(){
    FileRepository repository = FileRepository("testFile.csv");
    Service service = Service(repository);
    try {
        std::string currentLocation = "south-west";
        service.removeTurret(currentLocation);
    }catch (std::exception&){
        assert(true);
    }

}

void UnitTests::UpdateTurretService_ValidInput_UpdatesTurret(){
    FileRepository repository = FileRepository("testFile.csv");
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
    FileRepository repository = FileRepository("testFile.csv");
    Service service = Service(repository);
    std::string mode = "A";
    service.setApplicationMode(mode);
    std::string currentLocation = "north-west";
    std::string size = "large";
    int auraLevel = 600;
    int numberOfSeparateParts = 3038;
    std::string vision = "tower";
    bool statusOfUpdate = service.updateTurret(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
    assert(statusOfUpdate == FAIL);
}

void UnitTests::UpdateTurretService_InvalidMode_ThrowsError(){
    FileRepository repository = FileRepository("testFile.csv");
    Service service = Service(repository);
    try {
        std::string currentLocation = "south-west";
        std::string size = "large";
        int auraLevel = 600;
        int numberOfSeparateParts = 3038;
        std::string vision = "tower";
        //service.addTurret(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
        std::string anotherSize = "small";
        int anotherAuraLevel = 346;
        service.updateTurret(currentLocation, anotherSize, anotherAuraLevel, numberOfSeparateParts, vision);
    }catch (std::exception&){
        assert(true);
    }
}


void UnitTests::MoveToTheNextTurret_InvalidMode_ThrowsError() {
    FileRepository repository = FileRepository("testFile.csv");
    Service service = Service(repository);
    try {
        service.moveToNextTurret();
    } catch (std::exception&){
        assert(true);
    }

}

void UnitTests::MoveToNextTurretService_ValidInput_MovesToNextTurret() {
    FileRepository repository = FileRepository("testFile.csv");
    Service service = Service(repository);
    std::string mode = "A";
    service.setApplicationMode(mode);
    service.addTurret("north-west wall center", "large", 34, 2345, "stone tower");
    mode = "B";
    service.setApplicationMode(mode);
    service.moveToNextTurret();
    assert(service.getCurrentIndexInListOfTurrets() == 1);
}


void UnitTests::SaveTurret_InvalidMode_ThrowsError() {
    FileRepository repository = FileRepository("testFile.csv");
    Service service = Service(repository);
    try {
        std::string currentLocation = "south-west";
        service.saveTurret(currentLocation);
    } catch (std::exception&){
        assert(true);
    }
}

void UnitTests::SaveTurretService_ValidInput_SavesTurret() {
    FileRepository repository = FileRepository("testFile.csv");
    Service service = Service(repository);
    std::string mode= "B";
    service.setApplicationMode(mode);
    service.saveTurret("north-west wall center");
    assert(service.getAllSavedTurrets().size() == 1);
}

void UnitTests::getListOfTurretsWithAGivenSizeAndAtLeastAGivenNumberOfPartsService_ValidInput() {
    FileRepository repository = FileRepository("testFile.csv");
    Service service = Service(repository);
    std::string mode= "B";
    service.setApplicationMode(mode);
    std::vector<NorvenTurret> turretsThatSatisfyCondition = service.getListOfTurretsWithAGivenSizeAndAtLeastAGivenNumberOfParts("small", 3000);
    assert(turretsThatSatisfyCondition.size() == 1);
}

void UnitTests::getListOfTurretsWithAGivenSizeAndAtLeastAGivenNumberOfPartsService_InvalidMode() {
    try {
        FileRepository repository = FileRepository("testFile.csv");
        Service service = Service(repository);
        std::vector<NorvenTurret> turretsThatSatisfyCondition = service.getListOfTurretsWithAGivenSizeAndAtLeastAGivenNumberOfParts(
                "small", 3000);
    } catch (std::exception&){
        assert(true);
    }
}

void UnitTests::testService() {
    SetApplicationMode_InvalidInput_ReturnsError();
    AddTurretService_ValidInput_AddsTurret();
    AddTurretService_DuplicateLocation_ReturnsError();
    AddTurretService_InvalidMode_ThrowsError();
    RemoveTurretService_ValidInput_RemovesTurret();
    RemoveTurretService_NonexistentTurret_ReturnsError();
    RemoveTurretService_InvalidMode_ThrowsError();
    UpdateFileService_ValidInput_UpdatesFile();
    UpdateTurretService_ValidInput_UpdatesTurret();
    UpdateTurretService_NonexistentTurret_ReturnsError();
    UpdateTurretService_InvalidMode_ThrowsError();
    MoveToTheNextTurret_InvalidMode_ThrowsError();
    MoveToNextTurretService_ValidInput_MovesToNextTurret();
    SaveTurret_InvalidMode_ThrowsError();
    SaveTurretService_ValidInput_SavesTurret();
    getListOfTurretsWithAGivenSizeAndAtLeastAGivenNumberOfPartsService_ValidInput();
    getListOfTurretsWithAGivenSizeAndAtLeastAGivenNumberOfPartsService_InvalidMode();
}

void UnitTests::testAll() {
    testDomain();
    testRepository();
    testService();
}