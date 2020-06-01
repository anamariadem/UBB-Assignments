#include <iostream>
#include <fstream>
#include "InMemoryRepository.h"
#include "TextFileRepository.h"
#include "Service.h"
#include "UserInterface.h"
#include "GraphicalUserInterface.h"
#include "TurretsTableModel.h"
#include <memory>
//#include <crtdbg.h>
using namespace std;

#include <QtWidgets/QApplication>

int main(int argc, char* argv[]) {

    ifstream file{"configuration.txt"};
    string configuration;
    file >> configuration;
    if(configuration == "memory"){
        QApplication a(argc, argv);

        Repository* allTurretsRepository = new InMemoryRepository();
        Repository* savedTurretsRepository = new InMemoryRepository();
        Service service{allTurretsRepository, savedTurretsRepository};
        TurretsTableModel* model = new TurretsTableModel{service};

        //UserInterface ui{service};
        //ui.startApplication();

        GraphicalUserInterface gui{model, service};
        gui.show();

        return a.exec();

    } else if (configuration == "file"){
        QApplication a(argc, argv);
        Repository* allTurretsRepository = new TextFileRepository();
        Repository* savedTurretsRepository = new TextFileRepository();
        Service service{allTurretsRepository, savedTurretsRepository};
        TurretsTableModel* model = new TurretsTableModel{service};

        //UserInterface ui{service};
        //ui.startApplication();

        GraphicalUserInterface gui{model, service};
        gui.show();

        return a.exec();
    }

    return 0;
}
