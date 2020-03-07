//
// Created by Ana Maria on 04/03/2020.
//
#include <string.h>
#include "gear.h"
#include <assert.h>

Gear createItemOfTypeGear(int catalogueNumber, char state[], char type[], double value){
    Gear gearItem;
    gearItem.catalogueNumber = catalogueNumber;
    strcpy(gearItem.state, state);
    strcpy(gearItem.type, type);
    gearItem.value = value;

    return gearItem;
}

int getCatalogueNumber(Gear gearItem){
    return gearItem.catalogueNumber;
}

char* getStateOfGearItem(Gear* gearItem){
    return gearItem->state;
}

void setStateOfGearItem(Gear* gearItem, char* newState){
    strcpy(gearItem->state, newState);
}

char* getTypeOfGearItem(Gear* gearItem){
    return gearItem->type;
}

void setTypeOfGearItem(Gear* gearItem, char* newType){
    strcpy(gearItem->type, newType);
}

double getValueOfGearItem(Gear gearItem){
    return gearItem.value;
}

void setValueOfGearItem(Gear* gearItem, double newValue){
    gearItem->value = newValue;
}

void testCreateGear(){
    Gear gearItem;
    gearItem = createItemOfTypeGear(23, "used", "cogwheel", 45.08);
    assert(getCatalogueNumber(gearItem) == 23);
    assert(strcmp(getStateOfGearItem(&gearItem), "used") == 0);
    assert(strcmp(getTypeOfGearItem(&gearItem), "cogwheel") == 0);
    assert(getValueOfGearItem(gearItem) == 45.08);
}
