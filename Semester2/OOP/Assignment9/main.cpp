#include <iostream>
#include <fstream>
#include "Service.h"
#include "UserInterface.h"
#include "GraphicalUserInterface.h"
//#include <crtdbg.h>
using namespace std;

#include <QtWidgets/QApplication>

int main(int argc, char* argv[]) {

    QApplication a(argc, argv);
    Service service{};

    GraphicalUserInterface gui{service};
    gui.show();

    return a.exec();
}
