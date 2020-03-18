//
// Created by Ana Maria on 14/03/2020.
//
#include "gear.h"
#include <string.h>
#include <stdlib.h>

Gear* createItemOfTypeGear(int catalogueNumber, char state[], char type[], double value){
    Gear* gearItem = (Gear*)malloc(sizeof(Gear));
    gearItem->catalogueNumber = catalogueNumber;
    gearItem->state = (char*)malloc(sizeof(char) * strlen(state) +1);
    strcpy(gearItem->state, state);
    gearItem->type = (char*)malloc(sizeof(char) * strlen(type) +1);
    strcpy(gearItem->type, type);
    gearItem->value = value;
    return gearItem;
}

void destroyGear(Gear* gearItem){
    free(gearItem->type);
    free(gearItem->state);
    free(gearItem);
}

int getCatalogueNumber(Gear* gearItem){
    return gearItem->catalogueNumber;
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

double getValueOfGearItem(Gear* gearItem){
    return gearItem->value;
}

void setValueOfGearItem(Gear* gearItem, double newValue){
    gearItem->value = newValue;
}

void swapTwoGears(Gear* firstGearToSwap, Gear* secondGearToSwap){
    Gear* auxiliaryGearToSwap = createItemOfTypeGear(0,"","",0);
    auxiliaryGearToSwap->catalogueNumber = firstGearToSwap->catalogueNumber;
    strcpy(auxiliaryGearToSwap->state, firstGearToSwap->state);
    strcpy(auxiliaryGearToSwap->type, firstGearToSwap->type);
    auxiliaryGearToSwap->value = firstGearToSwap->value;

    firstGearToSwap->catalogueNumber = secondGearToSwap->catalogueNumber;
    strcpy(firstGearToSwap->state, secondGearToSwap->state);
    strcpy(firstGearToSwap->type, secondGearToSwap->type);
    firstGearToSwap->value = secondGearToSwap->value;

    secondGearToSwap->catalogueNumber = auxiliaryGearToSwap->catalogueNumber;
    strcpy(secondGearToSwap->state, auxiliaryGearToSwap->state);
    strcpy(secondGearToSwap->type, auxiliaryGearToSwap->type);
    secondGearToSwap->value = auxiliaryGearToSwap->value;
}
