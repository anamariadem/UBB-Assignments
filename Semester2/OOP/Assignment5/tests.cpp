//
// Created by Ana Maria on 19/03/2020.
//

#include "tests.h"
#include <cassert>

void GetLocationOfTurret_ValidInput_ReturnsLocation(){
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    assert(turret.getLocationOfTurret() == "south-west");
}
void GetSizeOfTurret_ValidInput_ReturnsSize(){
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    assert(turret.getSizeOfTurret() == "medium");
}
void GetAuraLevelOfTurret_ValidInput_ReturnsAuraLevel(){
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    assert(turret.getAuraLevelOfTurret() == 500);
}
void GetNumberOfSeparatePartsOfTurret_ValidInput_ReturnsSeparateParts(){
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    assert(turret.getNumberOfSeparatePartsOfTurret() == 3030);
}
void GetVisionOfTurret_ValidInput_ReturnsVision(){
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    assert(turret.getVisionOfTurret() == "stone tower");
}

void SetSizeOfTurret_ValidInput_SetsSize(){
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    turret.setSizeOfTurret("large");
    assert(turret.getSizeOfTurret() == "large");
}
void SetAuraLevelOfTurret_ValidInput_SetsAuraLevel(){
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    turret.setAuraLevelOfTurret(654);
    assert(turret.getAuraLevelOfTurret() == 654);
}
void SetNumberOfSeparatePartsOfTurret_ValidInput_SetsSeparateParts(){
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    turret.setNumberOfSeparatePartsOfTurret(3040);
    assert(turret.getNumberOfSeparatePartsOfTurret() == 3040);
}
void SetVisionOfTurret_ValidInput_SetsVision(){
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    turret.setVisionOfTurret("wood tower");
    assert(turret.getVisionOfTurret() == "wood tower");
}

void testDomain(){
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

void AddTurret_ValidInput_AddsTurret(){
    Repository repository = Repository();
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    bool statusOfAdd = repository.addTurretToRepository(turret);
    assert(statusOfAdd == SUCCESS);
}
void AddTurret_DuplicateLocation_ReturnsError(){
    Repository repository = Repository();
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    repository.addTurretToRepository(turret);
    bool statusOfAdd = repository.addTurretToRepository(turret);
    assert(statusOfAdd == FAIL);
}
void RemoveTurret_ValidInput_RemovesTurret(){
    Repository repository = Repository();
    NorvenTurret turret = NorvenTurret("south-west", "medium", 500, 3030, "stone tower");
    repository.addTurretToRepository(turret);
    std::string  currentLocation = turret.getLocationOfTurret();
    bool statusOfRemove = repository.removeTurretFromRepository(currentLocation);
    assert(statusOfRemove == SUCCESS);
}
void RemoveTurret_NonexistentTurret_ReturnsError(){
    Repository repository = Repository();
    std::string currentLocation = "south-west";
    bool statusOfRemove = repository.removeTurretFromRepository(currentLocation);
    assert(statusOfRemove == FAIL);
}
void UpdateTurret_ValidInput_UpdatesTurret(){
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
void UpdateTurret_NonexistentTurret_ReturnsError(){
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

void testRepository(){
    AddTurret_ValidInput_AddsTurret();
    AddTurret_DuplicateLocation_ReturnsError();
    RemoveTurret_ValidInput_RemovesTurret();
    RemoveTurret_NonexistentTurret_ReturnsError();
    UpdateTurret_ValidInput_UpdatesTurret();
    UpdateTurret_NonexistentTurret_ReturnsError();
}

void AddTurretService_ValidInput_AddsTurret(){
    Repository repository = Repository();
    Service service = Service(repository);
    service.setApplicationMode("A");
    std::string currentLocation = "south-west";
    std::string size = "large";
    int auraLevel = 600;
    int numberOfSeparateParts = 3038;
    std::string vision = "tower";
    bool statusOfAdd = service.addTurretService(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
    assert(statusOfAdd == SUCCESS);
}
void AddTurretService_DuplicateLocation_ReturnsError(){
    Repository repository = Repository();
    Service service = Service(repository);
    service.setApplicationMode("A");
    std::string currentLocation = "south-west";
    std::string size = "large";
    int auraLevel = 600;
    int numberOfSeparateParts = 3038;
    std::string vision = "tower";
    service.addTurretService(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
    std::string anotherSize = "small";
    int anotherAuraLevel = 346;
    int statusOfAdd = service.addTurretService(currentLocation, anotherSize, anotherAuraLevel, numberOfSeparateParts, vision);
    assert(statusOfAdd == FAIL);
}

void AddTurretService_InvalidMode_ThrowsError(){
    Repository repository = Repository();
    Service service = Service(repository);
    try {
        std::string currentLocation = "south-west";
        std::string size = "large";
        int auraLevel = 600;
        int numberOfSeparateParts = 3038;
        std::string vision = "tower";
        service.addTurretService(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
        assert(false);
    }catch (std::exception&){
        assert(true);
    }

}

void RemoveTurretService_ValidInput_RemovesTurret(){
    Repository repository = Repository();
    Service service = Service(repository);
    service.setApplicationMode("A");
    std::string currentLocation = "south-west";
    std::string size = "large";
    int auraLevel = 600;
    int numberOfSeparateParts = 3038;
    std::string vision = "tower";
    service.addTurretService(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
    bool statusOfRemove = service.removeTurretService(currentLocation);
    assert(statusOfRemove == SUCCESS);
}
void RemoveTurretService_NonexistentTurret_ReturnsError(){
    Repository repository = Repository();
    Service service = Service(repository);
    service.setApplicationMode("A");
    std::string currentLocation = "south-west";
    bool statusOfRemove = service.removeTurretService(currentLocation);
    assert(statusOfRemove == FAIL);
}

void RemoveTurretService_InvalidMode_ThrowsError(){
    Repository repository = Repository();
    Service service = Service(repository);
    try {
        std::string currentLocation = "south-west";
        std::string size = "large";
        int auraLevel = 600;
        int numberOfSeparateParts = 3038;
        std::string vision = "tower";
        service.addTurretService(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
        service.removeTurretService(currentLocation);
        assert(false);
    }catch (std::exception&){
        assert(true);
    }

}
void UpdateTurretService_ValidInput_UpdatesTurret(){
    Repository repository = Repository();
    Service service = Service(repository);
    service.setApplicationMode("A");
    std::string currentLocation = "south-west";
    std::string size = "large";
    int auraLevel = 600;
    int numberOfSeparateParts = 3038;
    std::string vision = "tower";
    service.addTurretService(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
    std::string anotherSize = "small";
    int anotherAuraLevel = 346;
    int statusOfUpdate = service.updateTurretService(currentLocation, anotherSize, anotherAuraLevel, numberOfSeparateParts, vision);
    assert(statusOfUpdate == SUCCESS);
}
void UpdateTurretService_NonexistentTurret_ReturnsError(){
    Repository repository = Repository();
    Service service = Service(repository);
    service.setApplicationMode("A");
    std::string currentLocation = "south-west";
    std::string size = "large";
    int auraLevel = 600;
    int numberOfSeparateParts = 3038;
    std::string vision = "tower";
    bool statusOfUpdate = service.updateTurretService(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
    assert(statusOfUpdate == FAIL);
}

void UpdateTurretService_InvalidMode_ThrowsError(){
    Repository repository = Repository();
    Service service = Service(repository);
    try {
        std::string currentLocation = "south-west";
        std::string size = "large";
        int auraLevel = 600;
        int numberOfSeparateParts = 3038;
        std::string vision = "tower";
        service.addTurretService(currentLocation, size, auraLevel, numberOfSeparateParts, vision);
        std::string anotherSize = "small";
        int anotherAuraLevel = 346;
        service.updateTurretService(currentLocation, anotherSize, anotherAuraLevel, numberOfSeparateParts, vision);
        assert(false);
    }catch (std::exception&){
        assert(true);
    }
}

void testService(){
    AddTurretService_ValidInput_AddsTurret();
    AddTurretService_DuplicateLocation_ReturnsError();
    AddTurretService_InvalidMode_ThrowsError();
    RemoveTurretService_ValidInput_RemovesTurret();
    RemoveTurretService_NonexistentTurret_ReturnsError();
    RemoveTurretService_InvalidMode_ThrowsError();
    UpdateTurretService_ValidInput_UpdatesTurret();
    UpdateTurretService_NonexistentTurret_ReturnsError();
    UpdateTurretService_InvalidMode_ThrowsError();
}
void RunAllTests(){
    testDomain();
    testRepository();
    testService();
}