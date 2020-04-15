#include <iostream>
#include <fstream>
#include <cassert>
#include  "Turret.h"
#include "FileRepository.h"
#include "Service.h"
#include "UserInterface.h"
#include "UnitTests.h"
using namespace std;

int main() {
    UnitTests ut{};
    ut.testAll();

    FileRepository repo{""};
    Service service{repo};
    UserInterface ui{service};
    ui.startApplication();

    return 0;
}
