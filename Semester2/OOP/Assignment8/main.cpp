#include <iostream>
#include <fstream>
#include "TextFileRepository.h"
#include "TurretValidator.h"
#include "Service.h"
#include "UserInterface.h"
//#include <crtdbg.h>
using namespace std;


int main() {
    {
        Service service{};
        UserInterface ui{ service };
        ui.startApplication();
    }
    //_CrtDumpMemoryLeaks();
    return 0;
}
