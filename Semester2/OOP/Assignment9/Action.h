//
// Created by Ana Maria on 05/05/2020.
//

#ifndef ASSIGNMENT8_REMASTERED_ACTION_H
#define ASSIGNMENT8_REMASTERED_ACTION_H

#include <utility>

#include "Turret.h"
#include "Repository.h"

class Action {
public:
    virtual void executeUndo()=0;
    virtual void executeRedo()=0;
    virtual ~Action() {}
};

class ActionAdd: public Action{
private:
    NorvenTurret addedTurret;
    Repository* repository;

public:
    ActionAdd(NorvenTurret turret, Repository* givenRepository): addedTurret{std::move(turret)}, repository{givenRepository} {}
    void executeUndo() override;
    void executeRedo() override;
};

class ActionRemove: public Action{
private:
    NorvenTurret removedTurret;
    Repository* repository;

public:
    ActionRemove(NorvenTurret turret, Repository* givenRepository): removedTurret{std::move(turret)}, repository{givenRepository} {}
    void executeUndo() override;
    void executeRedo() override;
};

class ActionUpdate : public Action{
private:
    NorvenTurret beforeUpdateTurret;
    NorvenTurret afterUpdatedTurret;
    Repository* repository;

public:
    ActionUpdate(NorvenTurret beforeTurret, NorvenTurret turret, Repository* givenRepository): beforeUpdateTurret{std::move(beforeTurret)}, afterUpdatedTurret{std::move(turret)}, repository{givenRepository} {}
    void executeUndo() override;
    void executeRedo() override;
};
#endif //ASSIGNMENT8_REMASTERED_ACTION_H
