//
// Created by Ana Maria on 09/05/2020.
//

#ifndef ASSIGNMENT9_GRAPHICALUSERINTERFACE_H
#define ASSIGNMENT9_GRAPHICALUSERINTERFACE_H

#include <qWidget.h>
#include "Service.h"
#include "TurretsTableModel.h"
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QtCharts>
#include <QBarSet>

class GraphicalUserInterface: public QWidget {
private:
    Service& service;
    TurretsTableModel* turretsTableModel;

    QTabWidget* tabWidget;
    QWidget* administratorWidget;
    QWidget* userWidget;
    QWidget* analysisWidget;
    QWidget* secondWindowForMyList;

    QTableView* myListTableView;

    QBarSeries* barSeries;
    QChart* chart;
    QBarCategoryAxis *axisX;
    QValueAxis *axisY;
    QChartView *chartView;

    QListWidget* listOfTurrets;
    QListWidget* listOfSavedTurrets;
    QListWidget* listOfTurretsWithProperty;
    QLineEdit* currentTurret;
    QLineEdit* anotherLocationLineEdit;
    QLineEdit* anotherSizeLineEdit;
    QLineEdit* anotherPartsLineEdit;
    QLineEdit* locationLineEdit;
    QLineEdit* sizeLineEdit;
    QLineEdit* auraLevelLineEdit;
    QLineEdit* separatePartsLineEdit;
    QLineEdit* visionLineEdit;
    QLineEdit* fileLineEdit;
    QLineEdit* savedTurretsFileLineEdit;
    QLineEdit* modeLineEdit;

    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* setModeButton;
    QPushButton* updateFileButton;
    QPushButton* updateSavedTurretsFileButton;
    QPushButton* saveTurretButton;
    QPushButton* moveButton;
    QPushButton* updateButton;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QPushButton* undoMyListButton;
    QPushButton* redoMyListButton;
    QPushButton* showButton;
    QPushButton* openMainFile;
    QPushButton* openSavedFile;
    QPushButton* openSecondWindowButton;

public:
    GraphicalUserInterface(TurretsTableModel* modelToBuild, Service& serviceToBuild);

private:
      void initializeGraphicalInterface();
      void populateList();
      void populateSavedList();
      void createAnalysis();
      void connectSignalsAndSlots();

      int getSelectedIndex() const;
      void addTurret();
      void setMode();
      void updateFile();
      void updateSavedTurretsFile();
      void deleteTurret();
      void updateTurret();
      void saveTurret();
      void moveToTheNextTurret();
      void showTurretsWithProperties();
      void openAllTurretsFile();
      void openSavedTurretsFile();
      void undo();
      void redo();
      void undoMyList();
      void redoMyList();
      void clearFields();
      void openSecondWindow();
};


#endif //ASSIGNMENT9_GRAPHICALUSERINTERFACE_H
