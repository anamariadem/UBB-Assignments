//
// Created by Ana Maria on 14/03/2020.
//

#ifndef ASSIGNMENT4_DINAMICARRAY_H
#define ASSIGNMENT4_DINAMICARRAY_H

typedef void* TElem;

typedef struct {
    int capacity;
    int size;
    TElem* elements;
}DynamicArray;

/*
 creates a new dynamic array with a given capacity
 */
DynamicArray* createDynamicArray(int);
/*
 destroys the given dynamic array
 */
void destroyDynamicArray(DynamicArray**);
/*
 returns the size of a given dynamic array
 */
int getSizeOfDynamicArray(DynamicArray* dynamicArray);
/*
 turns the array into one of a bigger capacity
 */
void resizeDynamicArray(DynamicArray*);
int isFullCapacity(DynamicArray*);
void appendToDynamicArray(DynamicArray*, TElem);
int deleteFromDynamicArray(DynamicArray*, int);
int updateFromDynamicArray(DynamicArray*, int, TElem);
TElem getElement(DynamicArray*, int);
DynamicArray* getCopyOfArray(DynamicArray*);

#endif //ASSIGNMENT4_DINAMICARRAY_H
