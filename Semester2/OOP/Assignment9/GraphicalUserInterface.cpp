//
// Created by Ana Maria on 09/05/2020.
//

#include <QVBoxLayout>
#include <qlayout.h>
#include <QFormLayout>
#include <QMessageBox>
#include "GraphicalUserInterface.h"

GraphicalUserInterface::GraphicalUserInterface(Service &serviceToBuild):service{serviceToBuild} {
    this->initializeGraphicalInterface();
    this->populateList();
    this->connectSignalsAndSlots();
}

void GraphicalUserInterface::initializeGraphicalInterface() {
    this->listOfTurrets = new QListWidget{};
    this->locationLineEdit = new QLineEdit{};
    this->sizeLineEdit =  new QLineEdit{};
    this->auraLevelLineEdit = new QLineEdit{};
    this->separatePartsLineEdit =  new QLineEdit{};
    this->visionLineEdit =  new QLineEdit{};
    this->fileLineEdit = new QLineEdit{} ;
    this->modeLineEdit = new QLineEdit{};
    this->addButton = new QPushButton{"Add"};
    this->deleteButton = new QPushButton{"Delete"};
    this->setModeButton = new QPushButton{"Set Mode"};
    this->updateFileButton = new QPushButton{"Set file"};
    this->updateButton = new QPushButton{"Update"};
    this->undoButton = new QPushButton{"Undo"};
    this->redoButton = new QPushButton{"Redo"};

    QVBoxLayout* mainLayout = new QVBoxLayout{this};
    mainLayout->addWidget(this->listOfTurrets);

    QFormLayout* turretAttributesLayout = new QFormLayout{};
    turretAttributesLayout->addRow("Location", this->locationLineEdit);
    turretAttributesLayout->addRow("Size", this->sizeLineEdit);
    turretAttributesLayout->addRow("Aura Level", this->auraLevelLineEdit);
    turretAttributesLayout->addRow("Separate parts", this->separatePartsLineEdit);
    turretAttributesLayout->addRow("Vision", this->visionLineEdit);
    turretAttributesLayout->addRow("Mode", this->modeLineEdit);
    turretAttributesLayout->addRow("File", this->fileLineEdit);

    mainLayout->addLayout(turretAttributesLayout);

    QGridLayout* userCommandsLayout = new QGridLayout{};
    userCommandsLayout->addWidget(this->setModeButton, 0 , 0, 1, 2);
    userCommandsLayout->addWidget(this->updateFileButton, 1, 0, 1, 2);
    userCommandsLayout->addWidget(this->addButton, 2, 0);
    userCommandsLayout->addWidget(this->deleteButton, 2 ,1);
    userCommandsLayout->addWidget(this->updateButton, 3,0, 1,2);
    userCommandsLayout->addWidget(this->undoButton, 4, 0);
    userCommandsLayout->addWidget(this->redoButton, 4, 1);

    mainLayout->addLayout(userCommandsLayout);
}

void GraphicalUserInterface::populateList() {
    this->listOfTurrets->clear();

    auto turrets = this->service.getAllTurretsInRepository();
    for(auto& turret:turrets){
         this->listOfTurrets->addItem(QString::fromStdString(turret.toString()));
    }
}

void GraphicalUserInterface::connectSignalsAndSlots() {
    QObject::connect(this->listOfTurrets, &QListWidget::itemSelectionChanged, [this](){
        int selectedIndex = this->getSelectedIndex();
        if(selectedIndex < 0)
            return;

        NorvenTurret turret = this->service.getAllTurretsInRepository()[selectedIndex];
        this->locationLineEdit->setText(QString::fromStdString(turret.getLocationOfTurret()));
        this->sizeLineEdit->setText(QString::fromStdString(turret.getSizeOfTurret()));
        this->auraLevelLineEdit->setText(QString::fromStdString(std::to_string(turret.getAuraLevelOfTurret())));
        this->separatePartsLineEdit->setText(QString::fromStdString (std::to_string(turret.getNumberOfSeparatePartsOfTurret())));
        this->visionLineEdit->setText((QString::fromStdString(turret.getVisionOfTurret())));
    });

    QObject::connect(this->addButton, &QPushButton::clicked, this, &GraphicalUserInterface::addTurret);
    QObject::connect(this->setModeButton, &QPushButton::clicked, this, &GraphicalUserInterface::setMode);
    QObject::connect(this->updateFileButton, &QPushButton::clicked, this, &GraphicalUserInterface::updateFile);
    QObject::connect(this->deleteButton, &QPushButton::clicked, this, &GraphicalUserInterface::deleteTurret);
    QObject::connect(this->undoButton, &QPushButton::clicked, this, &GraphicalUserInterface::undo);
    QObject::connect(this->redoButton, &QPushButton::clicked, this, &GraphicalUserInterface::redo);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &GraphicalUserInterface::updateTurret);
}

int GraphicalUserInterface::getSelectedIndex() const {
     QModelIndexList selectedIndexes = this->listOfTurrets->selectionModel()->selectedIndexes();
      if(selectedIndexes.size() == 0) {
          this->locationLineEdit->clear();
          this->sizeLineEdit->clear();
          this->auraLevelLineEdit->clear();
          this->separatePartsLineEdit->clear();
          this->visionLineEdit->clear();
          return -1;
      }
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void GraphicalUserInterface::  addTurret() {
    std::string location = this->locationLineEdit->text().toStdString();
    std::string size = this->sizeLineEdit->text().toStdString();
    std::string auraLevelAsString = this->auraLevelLineEdit->text().toStdString();
    int auraLevel = std::stoi(auraLevelAsString);
    std::string separatePartsAsString = this->separatePartsLineEdit->text().toStdString();
    int separateParts = std::stoi(separatePartsAsString);
    std::string vision = this->visionLineEdit->text().toStdString();

    try {
        this->service.addTurret(location, size, auraLevel, separateParts, vision);
    } catch (MyException& exception){
        QMessageBox::critical(this, "Add Error", exception.what());
    }

    this->populateList();

    int lastElement = this->service.getAllTurretsInRepository().size()-1;
    this->listOfTurrets->setCurrentRow(lastElement);

    this->clearFields();
}

void GraphicalUserInterface::setMode() {
    std::string mode = this->modeLineEdit->text().toStdString();
    try {
        this->service.setApplicationMode(mode);
    }catch (MyException& exception){
        QMessageBox::critical(this, "Mode Error", exception.what());
    }

    this->modeLineEdit->clear();
}

void GraphicalUserInterface::updateFile() {
    std::string fileName = this->fileLineEdit->text().toStdString();
    this->service.updateAllTurretsFile(fileName);
    this->fileLineEdit->clear();
    this->populateList();
}

void GraphicalUserInterface::deleteTurret() {
    int selectedIndex = this->getSelectedIndex();
    if(selectedIndex < 0){
        QMessageBox::critical(this, "Error", "No song was slected!");
        return;
    }

    NorvenTurret turret = this->service.getAllTurretsInRepository()[selectedIndex];
    try {
        this->service.removeTurret(turret.getLocationOfTurret());
    }catch (MyException& exception){
        QMessageBox::critical(this, "Delete Error", exception.what());
    }
    this->populateList();
}

void GraphicalUserInterface::undo() {
    try {
        this->service.undo();
    }catch (MyException& exception){
        QMessageBox::critical(this, "Undo Error", exception.what());
    }
    this->populateList();
}

void GraphicalUserInterface::redo() {
    try {
        this->service.redo();
    }catch (MyException& exception){
        QMessageBox::critical(this, "Redo Error", exception.what());
    }
    this->populateList();
}

void GraphicalUserInterface::updateTurret() {
    int selectedIndex = this->getSelectedIndex();
    if(selectedIndex < 0){
        QMessageBox::critical(this, "Error", "No song was slected!");
        return;
    }

    NorvenTurret turret = this->service.getAllTurretsInRepository()[selectedIndex];
    try {
        std::string location = this->locationLineEdit->text().toStdString();
        std::string size = this->sizeLineEdit->text().toStdString();
        std::string auraLevelAsString = this->auraLevelLineEdit->text().toStdString();
        int auraLevel = std::stoi(auraLevelAsString);
        std::string separatePartsAsString = this->separatePartsLineEdit->text().toStdString();
        int separateParts = std::stoi(separatePartsAsString);
        std::string vision = this->visionLineEdit->text().toStdString();

        this->service.updateTurret(location, size, auraLevel, separateParts, vision);

    }catch (MyException& exception){
        QMessageBox::critical(this, "Update Error", exception.what());
    }

    this->clearFields();
    this->populateList();
}

void GraphicalUserInterface::clearFields() {
    this->locationLineEdit->clear();
    this->sizeLineEdit->clear();
    this->auraLevelLineEdit->clear();
    this->separatePartsLineEdit->clear();
    this->visionLineEdit->clear();
}
