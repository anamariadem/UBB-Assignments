//
// Created by Ana Maria on 14/03/2020.
//

#ifndef ASSIGNMENT4_GEAR_H
#define ASSIGNMENT4_GEAR_H

#include "dinamicArray.h"

typedef struct {
    int catalogueNumber;
    char* state;
    char* type;
    double value;
}Gear;

/*
 creates an item of type gear
 catalogueNumber - the given catalogue number
 state - the given state
 type - the given type
 value - the given value
 */
Gear* createItemOfTypeGear(int catalogueNumber, char state[], char type[], double value);
/*
 destroys an item of type gear
 Gear* - item to be destroyed
 */
void destroyGear(Gear*);
int getCatalogueNumber(Gear* gearItem);
char* getStateOfGearItem(Gear* gearItem);
void setStateOfGearItem(Gear* gearItem, char* newState);
char* getTypeOfGearItem(Gear* gearItem);
void setTypeOfGearItem(Gear* gearItem, char* newType);
double getValueOfGearItem(Gear* gearItem);
void setValueOfGearItem(Gear* gearItem, double newValue);

void swapTwoGears(Gear*, Gear*);
#endif //ASSIGNMENT4_GEAR_H
