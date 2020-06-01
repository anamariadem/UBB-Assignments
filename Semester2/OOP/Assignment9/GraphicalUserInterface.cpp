//
// Created by Ana Maria on 09/05/2020.
//

#include <QVBoxLayout>
#include <qlayout.h>
#include <QTabWidget>
#include <QFormLayout>
#include <QMessageBox>
#include <iostream>
#include <QtCore>
#include <QFileSystemWatcher>

#include "GraphicalUserInterface.h"

GraphicalUserInterface::GraphicalUserInterface(TurretsTableModel* modelToBuild, Service &serviceToBuild):service{serviceToBuild} {
    this->turretsTableModel = modelToBuild;
    this->initializeGraphicalInterface();
    this->createAnalysis();
    this->populateList();
    this->populateSavedList();
    this->connectSignalsAndSlots();
}


void GraphicalUserInterface::initializeGraphicalInterface() {
    //QTabWidget* tabWidget;
    //    QWidget* administratorWidget;
    this->tabWidget = new QTabWidget{};
    this->administratorWidget = new QWidget{};
    this->analysisWidget = new QWidget{};
    this->userWidget = new QWidget{};
    this->secondWindowForMyList = new QWidget{};

    this->myListTableView = new QTableView{this->secondWindowForMyList};
    this->listOfTurrets = new QListWidget{};
    this->listOfSavedTurrets = new QListWidget{};
    this->currentTurret = new QLineEdit{};
    this->anotherLocationLineEdit = new QLineEdit{};
    this->anotherSizeLineEdit = new QLineEdit{};
    this->anotherPartsLineEdit = new QLineEdit{};
    this->locationLineEdit = new QLineEdit{};
    this->sizeLineEdit =  new QLineEdit{};
    this->auraLevelLineEdit = new QLineEdit{};
    this->separatePartsLineEdit =  new QLineEdit{};
    this->visionLineEdit =  new QLineEdit{};
    this->fileLineEdit = new QLineEdit{} ;
    this->savedTurretsFileLineEdit = new QLineEdit{};
    this->modeLineEdit = new QLineEdit{};
    this->addButton = new QPushButton{"Add"};
    this->deleteButton = new QPushButton{"Delete"};
    this->setModeButton = new QPushButton{"Set Mode"};
    this->updateFileButton = new QPushButton{"Set file"};
    this->updateSavedTurretsFileButton = new QPushButton{"Set file"};
    this->saveTurretButton = new QPushButton{"Save"};
    this->moveButton = new QPushButton{"Move"};
    this->updateButton = new QPushButton{"Update"};
    this->undoButton = new QPushButton{"Undo"};
    this->redoButton = new QPushButton{"Redo"};
    this->undoMyListButton = new QPushButton{"Undo"};
    this->redoMyListButton = new QPushButton{"Redo"};
    this->showButton = new QPushButton{"Show turrets with properties"};
    this->openMainFile = new QPushButton{"Open"};
    this->openSavedFile = new QPushButton{"Open"};
    this->openSecondWindowButton = new QPushButton{"Open second window"};
    this->listOfTurretsWithProperty = new QListWidget{};

    QGridLayout* userLayout = new QGridLayout{this->userWidget};
    userLayout->addWidget(this->listOfSavedTurrets, 0 ,0);
    userLayout->addWidget(this->listOfTurretsWithProperty, 1, 0);

    QFormLayout* savedTurretsForm = new QFormLayout{};
    savedTurretsForm->addRow("File", this->savedTurretsFileLineEdit);
    savedTurretsForm->addRow("Location", this->anotherLocationLineEdit);
    savedTurretsForm->addRow("Current Turret", this->currentTurret);
    savedTurretsForm->addRow("Size", this->anotherSizeLineEdit);
    savedTurretsForm->addRow("Separate parts", this->anotherPartsLineEdit);

    userLayout->addLayout(savedTurretsForm, 0,1,2,1);

    QGridLayout* userButtonsLayout = new QGridLayout{};
    userButtonsLayout->addWidget(this->updateSavedTurretsFileButton, 0,0);
    userButtonsLayout->addWidget(this->openSavedFile, 0,1);
    userButtonsLayout->addWidget(this->saveTurretButton, 1,0);
    userButtonsLayout->addWidget(this->moveButton, 1, 1);
    userButtonsLayout->addWidget(this->showButton, 2,0,1,2);
    userButtonsLayout->addWidget(this->undoMyListButton, 3,0);
    userButtonsLayout->addWidget(this->redoMyListButton,3, 1);
    userButtonsLayout->addWidget(this->openSecondWindowButton, 4, 0,1,2);

    userLayout->addLayout(userButtonsLayout, 1, 1);
    QGridLayout* mainLayout = new QGridLayout{this->administratorWidget};

    mainLayout->addWidget(this->listOfTurrets,0,0);


    QFormLayout* turretAttributesLayout = new QFormLayout{};
    turretAttributesLayout->addRow("File", this->fileLineEdit);
    turretAttributesLayout->addRow("Mode", this->modeLineEdit);
    turretAttributesLayout->addRow("Location", this->locationLineEdit);
    turretAttributesLayout->addRow("Size", this->sizeLineEdit);
    turretAttributesLayout->addRow("Aura Level", this->auraLevelLineEdit);
    turretAttributesLayout->addRow("Separate parts", this->separatePartsLineEdit);
    turretAttributesLayout->addRow("Vision", this->visionLineEdit);


    mainLayout->addLayout(turretAttributesLayout,0,1, 2,1);

    QGridLayout* userCommandsLayout = new QGridLayout{};
    userCommandsLayout->addWidget(this->setModeButton, 0 , 0, 1, 2);
    userCommandsLayout->addWidget(this->updateFileButton, 1, 0);
    userCommandsLayout->addWidget(this->openMainFile, 1,1);
    userCommandsLayout->addWidget(this->addButton, 2, 0);
    userCommandsLayout->addWidget(this->deleteButton, 2 ,1);
    userCommandsLayout->addWidget(this->updateButton, 3,0, 1,2);
    userCommandsLayout->addWidget(this->undoButton, 4, 0);
    userCommandsLayout->addWidget(this->redoButton, 4, 1);

    mainLayout->addLayout(userCommandsLayout,1,0);


    QHBoxLayout* tabLayout = new QHBoxLayout{this};
    tabLayout->addWidget(this->tabWidget);
    this->tabWidget->addTab(this->administratorWidget, "General");
    this->tabWidget->addTab(this->userWidget, "User");
    this->tabWidget->addTab(this->analysisWidget, "Analysis");

    this->barSeries = new QBarSeries{};
    this->chart = new QChart{};
    this->axisX = new QBarCategoryAxis();
    this->axisY = new QValueAxis{};
    this->chartView = new QChartView(this->chart);

    this->chart->addSeries(this->barSeries);
    this->chart->setTitle(QString::fromStdString("Turret data analysis"));
    this->chart->setAnimationOptions(QChart::SeriesAnimations);

    QString locations = QString::fromStdString("locations");

    this->axisX->append(locations);
    this->chart->addAxis(axisX, Qt::AlignBottom);
    this->barSeries->attachAxis(axisX);

    this->axisY->setRange(0,500);
    this->axisY->setTitleText(QString::fromStdString("Aura Level"));
    this->chart->addAxis(axisY, Qt::AlignLeft);
    this->barSeries->attachAxis(axisY);

    this->chart->legend()->setVisible(true);
    this->chart->legend()->setAlignment(Qt::AlignBottom);

    this->chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout* analysisLayout = new QVBoxLayout{this->analysisWidget};
    analysisLayout->addWidget(this->chartView);

    QVBoxLayout* secondWindowLayout = new QVBoxLayout{this->secondWindowForMyList};
    secondWindowLayout->addWidget(this->myListTableView);

    this->myListTableView->setModel(this->turretsTableModel);
    this->myListTableView->update();

}

void GraphicalUserInterface::populateList() {
    this->listOfTurrets->clear();

    auto turrets = this->service.getAllTurretsInRepository();
    QFont font{};
    font.setWeight(QFont::Bold);
    for(auto& turret:turrets){
        QListWidgetItem* item = new QListWidgetItem{};
        item->setText(QString::fromStdString(turret.toString()));
        if(turret.getLocationOfTurret() == "north") {
            item->setFont(font);
            this->listOfTurrets->addItem(item);
        }else{
            font.setWeight(QFont::Normal);
            item->setFont(font);
            this->listOfTurrets->addItem(item);
        }
    }
}

void GraphicalUserInterface::connectSignalsAndSlots() {

    QShortcut* undoShortcut = new QShortcut{QKeySequence("CTRL+Z"), this->administratorWidget};
    QShortcut* redoShortcut = new QShortcut{QKeySequence("CTRL+Y"), this->administratorWidget};

    QObject::connect(undoShortcut, &QShortcut::activated, this, &GraphicalUserInterface::undo);
    QObject::connect(redoShortcut, &QShortcut::activated, this, &GraphicalUserInterface::redo);

    QShortcut* undoMyListShortcut = new QShortcut{QKeySequence("CTRL+Z"), this->userWidget};
    QShortcut* redoMyListShortcut = new QShortcut{QKeySequence("CTRL+Y"), this->userWidget};

    QObject::connect(undoMyListShortcut, &QShortcut::activated, this, &GraphicalUserInterface::undoMyList);
    QObject::connect(redoMyListShortcut, &QShortcut::activated, this, &GraphicalUserInterface::redoMyList);

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

    QObject::connect(this->updateSavedTurretsFileButton, &QPushButton::clicked, this, &GraphicalUserInterface::updateSavedTurretsFile);
    QObject::connect(this->saveTurretButton, &QPushButton::clicked, this, &GraphicalUserInterface::saveTurret);
    QObject::connect(this->moveButton, &QPushButton::clicked, this, &GraphicalUserInterface::moveToTheNextTurret);
    QObject::connect(this->showButton, &QPushButton::clicked, this, &GraphicalUserInterface::showTurretsWithProperties);

    QObject::connect(this->openMainFile, &QPushButton::clicked, this, &GraphicalUserInterface::openAllTurretsFile);
    QObject::connect(this->openSavedFile, &QPushButton::clicked, this, &GraphicalUserInterface::openSavedTurretsFile);

    QObject::connect(this->undoMyListButton, &QPushButton::clicked, this, &GraphicalUserInterface::undoMyList);
    QObject::connect(this->redoMyListButton, &QPushButton::clicked, this, &GraphicalUserInterface::redoMyList);

    QObject::connect(this->openSecondWindowButton, &QPushButton::clicked, this, &GraphicalUserInterface::openSecondWindow);


    /*std::string fileName = this->service.getSavedTurretsFileName();
    QStringList paths;
    paths.push_back(QString::fromStdString(fileName));
    if (!fileName.empty()){
        auto fileCheck = QFileSystemWatcher(paths);
        //QObject::connect(fileCheck, &QFileSystemWatcher::fileChanged, this, &GraphicalUserInterface::populateSavedList);
    }*/

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
    /*std::string fileName = this->service.getAllTurretsFileName();
    if(fileName.empty())
        QMessageBox::critical(this, "File Error", "No file was provided");*/
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

    this->createAnalysis();

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
    try {
        std::string fileName = this->fileLineEdit->text().toStdString();
        //QMessageBox::critical(this, "Mode Error", QString::fromStdString(fileName));
        this->service.updateAllTurretsFile(fileName);
        std::ofstream newFile{fileName, std::ios::app};
        newFile.close();
        this->fileLineEdit->clear();
        this->populateList();
        this->createAnalysis();
    }catch (MyException& exception){
        QMessageBox::critical(this, "File Error", exception.what());
    }

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
    this->createAnalysis();
}

void GraphicalUserInterface::undo() {
    try {
        this->service.undo();
    }catch (MyException& exception){
        QMessageBox::critical(this, "Undo Error", exception.what());
    }
    this->populateList();
    this->createAnalysis();
}

void GraphicalUserInterface::redo() {
    try {
        this->service.redo();
    }catch (MyException& exception){
        QMessageBox::critical(this, "Redo Error", exception.what());
    }
    this->populateList();
    this->createAnalysis();
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
    this->createAnalysis();
}

void GraphicalUserInterface::clearFields() {
    this->locationLineEdit->clear();
    this->sizeLineEdit->clear();
    this->auraLevelLineEdit->clear();
    this->separatePartsLineEdit->clear();
    this->visionLineEdit->clear();
}

void GraphicalUserInterface::createAnalysis() {
    auto turretsFromRepository = this->service.getAllTurretsInRepository();
    //this->barSeries = new QBarSeries{};
    //this->chart = new QChart{};
    this->barSeries->clear();
    for(auto& turret: turretsFromRepository){
        QBarSet* currentSet = new QBarSet(QString::fromStdString(turret.getLocationOfTurret()));
        *currentSet << turret.getAuraLevelOfTurret();
        this->barSeries->append(currentSet);
    }

}

void GraphicalUserInterface::populateSavedList() {
    this->myListTableView->update();
    this->listOfSavedTurrets->clear();
    auto turrets = this->service.getAllSavedTurrets();
    if(turrets.empty())
        return;
    //int row = 0;
    for(auto& turret:turrets){
        this->listOfSavedTurrets->addItem(QString::fromStdString(turret.toString()));
    }
}

void GraphicalUserInterface::updateSavedTurretsFile() {
    try {
        std::string fileName = this->savedTurretsFileLineEdit->text().toStdString();
        //QMessageBox::critical(this, "Mode Error", QString::fromStdString(fileName));
        this->service.updateSavedTurretsFile(fileName);
        std::ofstream newFile{fileName, std::ios::app};
        newFile.close();
        this->savedTurretsFileLineEdit->clear();
        this->populateSavedList();
        this->myListTableView->update();
    }catch (MyException& exception){
        QMessageBox::critical(this, "File Error", exception.what());
    }

}

void GraphicalUserInterface::saveTurret() {
    //this->myListTableView->reset();
    std::string location = this->anotherLocationLineEdit->text().toStdString();
    try {
        this->service.saveTurret(location);
    }catch (MyException& exception){
        QMessageBox::critical(this, "Mode Error", exception.what());
    }

    this->populateSavedList();
    this->myListTableView->setModel(this->turretsTableModel);
    this->anotherLocationLineEdit->clear();
}

void GraphicalUserInterface::moveToTheNextTurret() {
    auto turrets = this->service.getAllTurretsInRepository();
    try {
        this->service.moveToNextTurret();
        auto index = this->service.getCurrentIndexInListOfTurrets();
        this->currentTurret->setText(QString::fromStdString(turrets[index].getLocationOfTurret()));
    }catch (MyException& exception){
        QMessageBox::critical(this, "Mode Error", exception.what());
    }
}

void GraphicalUserInterface::showTurretsWithProperties() {
    std::string size = this->anotherSizeLineEdit->text().toStdString();
    int separateParts = std::stoi(this->anotherPartsLineEdit->text().toStdString());


    try {
        auto turrets = this->service.getListOfTurretsWithAGivenSizeAndAtLeastAGivenNumberOfParts(size, separateParts);
        for(auto& turret:turrets)
            this->listOfTurretsWithProperty->addItem(QString::fromStdString(turret.toString()));
    }catch (MyException& exception){
        QMessageBox::critical(this, "Mode Error", exception.what());
    }
    this->anotherSizeLineEdit->clear();
    this->anotherPartsLineEdit->clear();

}

void GraphicalUserInterface::openSavedTurretsFile() {
    //this->myListTableView->reset();
    std::string fileName = this->service.getSavedTurretsFileName();
    if(!fileName.empty())
        system(("open \"" + fileName + "\"").c_str());
    else
        QMessageBox::critical(this, "File Error", "No file to open");

}

void GraphicalUserInterface::openAllTurretsFile() {
    std::string fileName = this->service.getAllTurretsFileName();
    if(!fileName.empty())
        system(("open \"" + fileName + "\"").c_str());
    else
        QMessageBox::critical(this, "File Error", "No file to open");
}

void GraphicalUserInterface::redoMyList() {
    try {
        this->service.redoMyList();
    }catch (MyException& exception){
        QMessageBox::critical(this, "Redo Error", exception.what());
    }
    this->populateSavedList();
}

void GraphicalUserInterface::undoMyList() {
    try {
        this->service.undoMyList();
    }catch (MyException& exception){
        QMessageBox::critical(this, "Undo Error", exception.what());
    }
    this->populateSavedList();
}

void GraphicalUserInterface::openSecondWindow() {
    //this->secondWindowForMyList->setModal(true);
    //this->secondWindowForMyList->exec();
    //this->turretsTableModel->removeRows(0, this->turretsTableModel->rowCount());
    //this->myListTableView->setModel(this->turretsTableModel);
    //this->myListTableView.
    this->secondWindowForMyList->show();
}
