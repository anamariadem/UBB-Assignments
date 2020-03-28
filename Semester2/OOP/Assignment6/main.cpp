#include <iostream>
#include "DynamicVector.h"
#include "UnitTests.h"
#include "UserInterface.h"

int main() {
    UnitTests ut = UnitTests();
    ut.RunAllTests();

    Repository repository = Repository();
    Service service = Service(repository);
    UserInterface ui = UserInterface(service);

    ui.startApplication();
    return 0;
}