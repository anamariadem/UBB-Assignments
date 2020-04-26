//
// Created by Ana Maria on 10/04/2020.
//

#include "Service.h"

void Service::setApplicationMode(std::string& newMode) {
    if(newMode!="A" && newMode!="B")
        throw MyException("Wrong mode! :(\n");
    this->applicationMode = newMode;
}

void Service::updateAllTurretsFile(const std::string &newFileName) {
    delete this->turretRepository;
    FileRepository* correctRepository = Service::createTurretRepositoryBasedOnFileExtension(newFileName);
    this->turretRepository = correctRepository;
    auto* pointerToFileRepository = dynamic_cast<FileRepository*>(this->turretRepository);
    pointerToFileRepository->updateFile(newFileName);
}

void Service::updateSavedTurretsFile(const std::string &newFileName) {
    delete this->savedTurretRepository;
    FileRepository* correctRepository = Service::createTurretRepositoryBasedOnFileExtension(newFileName);
    this->savedTurretRepository = correctRepository;
    auto* pointerToFileRepository = dynamic_cast<FileRepository*>(this->savedTurretRepository);
    pointerToFileRepository->updateFile(newFileName);
}

FileRepository* Service::createTurretRepositoryBasedOnFileExtension(const std::string &fileName) {
    auto indexOfLastDot = fileName.find_last_of('.');
    std::string fileExtension = fileName.substr(indexOfLastDot);

    if(fileExtension == ".txt")
        return new TextFileRepository;
    if(fileExtension == ".csv")
        return new CSVFileRepository;
    if(fileExtension == ".html")
       return new HTMLFileRepository;

    throw MyException("Invalid Extension! :(\n");
}


std::string Service::getFileName() const {
    auto* pointerToFileRepository = dynamic_cast<TextFileRepository*>(this->turretRepository);
    return pointerToFileRepository->getFilename();
}

void Service::addTurret(const std::string & location, const std::string & size, const int & auraLevel, const int & separateParts, const std::string & vision) {
    if(this->applicationMode != "A")
        throw MyException("Invalid operation unless in mode A! :(\n");
    NorvenTurret turretToAdd(location, size, auraLevel, separateParts, vision);
    TurretValidator::validateTurret(turretToAdd);
    this->turretRepository->addTurret(turretToAdd);
}

void Service::removeTurret(const std::string & location) {
    if(this->applicationMode != "A")
        throw MyException("Invalid operation unless in mode A! :(\n");
    this->turretRepository->removeTurret(location);
    try {
        this->savedTurretRepository->removeTurret(location);
    }catch (MyException&){}

}

void Service::updateTurret(const std::string & location, const std::string & size, const int & auraLevel, const int & separateParts, const std::string& vision) {
    if(this->applicationMode != "A")
        throw MyException("Invalid operation unless in mode A! :(\n");
    TurretValidator::validateTurret(NorvenTurret{location, size, auraLevel, separateParts, vision});
    this->turretRepository->updateTurret(location, size, auraLevel, separateParts, vision);

    try {
        this->savedTurretRepository->updateTurret(location, size, auraLevel, separateParts, vision);
    } catch (MyException&){}

}


void Service::moveToNextTurret() {
    if(this->applicationMode != "B")
        throw MyException("Invalid operation unless in mode B! :(\n");

    std::vector<NorvenTurret> listOfTurrets = this->turretRepository->getListOfTurrets();

    if(this->currentIndexInListOfTurrets == listOfTurrets.size()-1)
        this->currentIndexInListOfTurrets = 0;
    else
        this->currentIndexInListOfTurrets ++;
}

void Service::saveTurret(const std::string & location) {
    //std::string message = "Operation not allowed if not in mode B! :( \n";
    if(this->applicationMode != "B")
        throw MyException("Invalid operation unless in mode B! :(\n");

    this->savedTurretRepository->addTurret(this->turretRepository->findTurretByLocation(location));
}


std::vector<NorvenTurret> Service::getListOfTurretsWithAGivenSizeAndAtLeastAGivenNumberOfParts(const std::string & size, const int & separateParts) {
    if (this->applicationMode != "B")
        throw MyException("Invalid operation unless in mode B! :(\n");


    std::vector<NorvenTurret> listOfTurrets = this->turretRepository->getListOfTurrets();

    std::vector<NorvenTurret> turretsThatSatisfyTheCondition(listOfTurrets.size());
    /*
    for (auto &turret : listOfTurrets)
        if (turret.getSizeOfTurret() == size and turret.getNumberOfSeparatePartsOfTurret() >= separateParts)
            turretsThatSatisfyTheCondition.push_back(turret);*/

    auto iterator = std::copy_if(listOfTurrets.begin(), listOfTurrets.end(), turretsThatSatisfyTheCondition.begin(), [size, separateParts](const NorvenTurret& turret){ return turret.getSizeOfTurret() == size and turret.getNumberOfSeparatePartsOfTurret() >= separateParts;});

    turretsThatSatisfyTheCondition.resize(std::distance(turretsThatSatisfyTheCondition.begin(), iterator));

    return turretsThatSatisfyTheCondition;
}

Service::~Service() {
    delete this->turretRepository;
    delete this->savedTurretRepository;
}


