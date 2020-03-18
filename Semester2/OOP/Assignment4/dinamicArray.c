//
// Created by Ana Maria on 14/03/2020.
//

#include "dinamicArray.h"
#include <stdlib.h>

DynamicArray* createDynamicArray(int capacity){
    DynamicArray* dynamicArray = (DynamicArray*)malloc(sizeof(DynamicArray));
    dynamicArray->capacity = capacity;
    dynamicArray->size = 0;
    dynamicArray->elements = (TElem*)malloc(capacity* sizeof(TElem));
    return dynamicArray;
}

void destroyDynamicArray(DynamicArray** dynamicArray){
    free((*dynamicArray)->elements);
    free(*dynamicArray);
}

int getSizeOfDynamicArray(DynamicArray* dynamicArray){
    return dynamicArray->size;
}

void resizeDynamicArray(DynamicArray* dynamicArray){
    TElem* resizedArray = (TElem*)malloc(sizeof(TElem) * dynamicArray->capacity *2);
    for(int i=0; i<dynamicArray->size;i++)
        resizedArray[i] = dynamicArray->elements[i];
    free(dynamicArray->elements);
    dynamicArray->capacity *= 2;
    dynamicArray->elements = resizedArray;
}

int isFullCapacity(DynamicArray* dynamicArray){
    return dynamicArray->size == dynamicArray ->capacity;
}

void appendToDynamicArray(DynamicArray* dynamicArray, TElem element){
    if(isFullCapacity(dynamicArray))
        resizeDynamicArray(dynamicArray);
    dynamicArray->elements[dynamicArray->size++] = element;
}

int deleteFromDynamicArray(DynamicArray* dynamicArray, int indexOfElement){
    if(indexOfElement < 0 || indexOfElement >= dynamicArray->size || dynamicArray->size ==0)
        return -1;
    for(int i=indexOfElement; i<dynamicArray->size;i++)
        dynamicArray->elements[i] = dynamicArray->elements[i+1];
    dynamicArray->size--;
    return 1;
}

int updateFromDynamicArray(DynamicArray* dynamicArray, int indexOfElement, TElem element) {
    if(indexOfElement < 0 || indexOfElement >= dynamicArray->size || dynamicArray->size ==0)
        return -1;
    dynamicArray->elements[indexOfElement] = element;
    return 1;
}

TElem getElement(DynamicArray* dynamicArray, int indexOfElement){
    return dynamicArray->elements[indexOfElement];
}


DynamicArray* getCopyOfArray(DynamicArray* dynamicArray){
    DynamicArray* copyOfArray = createDynamicArray(dynamicArray->capacity);
    copyOfArray->size = dynamicArray->size;
    for(int i=0; i<copyOfArray->size;i++)
        copyOfArray->elements[i] = dynamicArray->elements[i];
    return copyOfArray;
}
