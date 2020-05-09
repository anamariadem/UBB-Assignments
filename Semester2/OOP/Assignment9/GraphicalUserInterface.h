//
// Created by Ana Maria on 09/05/2020.
//

#ifndef ASSIGNMENT9_GRAPHICALUSERINTERFACE_H
#define ASSIGNMENT9_GRAPHICALUSERINTERFACE_H

#include <qWidget.h>
#include "Service.h"
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

class GraphicalUserInterface: public QWidget {
private:
    Service& service;

    QListWidget* listOfTurrets;
    QLineEdit* locationLineEdit;
    QLineEdit* sizeLineEdit;
    QLineEdit* auraLevelLineEdit;
    QLineEdit* separatePartsLineEdit;
    QLineEdit* visionLineEdit;
    QLineEdit* fileLineEdit;
    QLineEdit* modeLineEdit;

    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* setModeButton;
    QPushButton* updateFileButton;
    QPushButton* updateButton;
    QPushButton* undoButton;
    QPushButton* redoButton;

public:
    GraphicalUserInterface(Service& serviceToBuild);

private:
      void initializeGraphicalInterface();
      void populateList();
      void connectSignalsAndSlots();

      int getSelectedIndex() const;
      void addTurret();
      void setMode();
      void updateFile();
      void deleteTurret();
      void updateTurret();
      void undo();
      void redo();
      void clearFields();
};


#endif //ASSIGNMENT9_GRAPHICALUSERINTERFACE_H
