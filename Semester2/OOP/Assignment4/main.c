
#include <stdio.h>
#include "userInterface.h"
#include "unitTests.h"

int main() {
    RunAllTests();

    Repository* repository = createRepository(2);
    Service* service = createService(repository);
    UserInterface* ui = createUserInterface(service);

    startApp(ui);

    destroyUserInterface(ui);
    destroyService(service);
    destroyRepository(repository);

    return 0;
}
