#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include "DynamicVector.h"
#include "tests.h"
#include "UserInterface.h"
using namespace std;

int main() {

    RunAllTests();
    Repository repository = Repository();
    Service service = Service(repository);
    UserInterface ui = UserInterface(service);

    ui.startApplication();

    return 0;
}
