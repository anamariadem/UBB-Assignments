//
// Created by Ana Maria on 04/03/2020.
//

#ifndef ASSIGNMENT3_GEAR_H
#define ASSIGNMENT3_GEAR_H

typedef struct {
    int catalogueNumber;
    char state[50];
    char type[50];
    double value;
}Gear;

/*
 creates an item of type gear
 catalogueNumber - the given catalogue number
 state - the given state
 type - the given type
 value - the given value
 */
Gear createItemOfTypeGear(int catalogueNumber, char state[], char type[], double value);
int getCatalogueNumber(Gear gearItem);
char* getStateOfGearItem(Gear* gearItem);
void setStateOfGearItem(Gear* gearItem, char* newState);
char* getTypeOfGearItem(Gear* gearItem);
void setTypeOfGearItem(Gear* gearItem, char* newType);
double getValueOfGearItem(Gear gearItem);
void setValueOfGearItem(Gear* gearItem, double newValue);

void testCreateGear();

#endif //ASSIGNMENT3_GEAR_H
