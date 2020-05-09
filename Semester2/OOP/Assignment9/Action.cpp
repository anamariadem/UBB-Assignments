//
// Created by Ana Maria on 05/05/2020.
//

#include "Action.h"

void ActionAdd::executeUndo() {
    this->repository->removeTurret(this->addedTurret.getLocationOfTurret());
}

void ActionAdd::executeRedo() {
    this->repository->addTurret(this->addedTurret);
}

void ActionRemove::executeUndo() {
    this->repository->addTurret(this->removedTurret);
}

void ActionRemove::executeRedo() {
    this->repository->removeTurret(this->removedTurret.getLocationOfTurret());
}

void ActionUpdate::executeUndo() {
    this->repository->updateTurret(this->beforeUpdateTurret.getLocationOfTurret(), this->beforeUpdateTurret.getSizeOfTurret(), this->beforeUpdateTurret.getAuraLevelOfTurret(), this->beforeUpdateTurret.getNumberOfSeparatePartsOfTurret(), this->beforeUpdateTurret.getVisionOfTurret());
}

void ActionUpdate::executeRedo() {
    this->repository->updateTurret(this->afterUpdatedTurret.getLocationOfTurret(), this->afterUpdatedTurret.getSizeOfTurret(), this->afterUpdatedTurret.getAuraLevelOfTurret(), this->afterUpdatedTurret.getNumberOfSeparatePartsOfTurret(), this->afterUpdatedTurret.getVisionOfTurret());
}
