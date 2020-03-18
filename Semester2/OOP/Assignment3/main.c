#include <stdio.h>
#include "gear.h"
#include "repository.h"
#include "service.h"
#include "ui.h"

int main() {

    runTests();

    Repository* repository = createRepository();
    Service* service = createService(repository);
    UserInterface* ui = createUserInterface(service);

    start(ui);

    destroyUserInterface(ui);
    destroyService(service);
    destroyRepository(repository);
    return 0;
}
