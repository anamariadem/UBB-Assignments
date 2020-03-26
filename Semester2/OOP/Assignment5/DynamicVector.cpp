//
// Created by Ana Maria on 19/03/2020.
//

#include "DynamicVector.h"

DynamicVector::DynamicVector(int capacity) {
    this->size = 0;
    this->capacity = capacity;
    this->elements = new TElement[this->capacity];
}

DynamicVector::DynamicVector(const DynamicVector &dynamicVector) {
    this->size = dynamicVector.size;
    this->capacity = dynamicVector.capacity;
    this->elements = new TElement[this->capacity];

    for(int i=0; i< this->size; i++){
        this->elements[i] = dynamicVector.elements[i];
    }
}

DynamicVector& DynamicVector::operator=(const DynamicVector &dynamicVector) {
    if (this == &dynamicVector)
        return *this;

    this->size = dynamicVector.size;
    this->capacity = dynamicVector.capacity;

    delete [] this->elements;
    this->elements = new TElement[this->capacity];
    for(int i=0; i< this->size; i++){
        this->elements[i] = dynamicVector.elements[i];
    }

    return *this;
}

int DynamicVector::getSizeOfVector() const {
    return this->size;
}

TElement DynamicVector::getElement(int& positionInArray) {
    return this->elements[positionInArray];
}

bool DynamicVector::isFullCapacity() const {
    return this->size==this->capacity;
}

void DynamicVector::resizeDynamicVector(int factor) {
    this->capacity *= factor;

    auto* newDynamicVector = new TElement[this->capacity];
    for(int i=0; i< this->size; i++){
        newDynamicVector[i] = this->elements[i];
    }
    delete [] this->elements;
    this->elements = newDynamicVector;
}

void DynamicVector::addToDynamicVector(const TElement & element) {
    if(isFullCapacity())
        this->resizeDynamicVector();

    this->elements[this->size++] = element;
}

void DynamicVector::deleteFromDynamicVector(int& positionInArray) {
    for(int i = positionInArray;i <this->size; i++)
        this->elements[i] = this->elements[i+1];
    this->size --;
}

void DynamicVector::updateElementInDynamicArray(int& positionInArray, TElement & newElement) {
    this->elements[positionInArray] = newElement;
}

DynamicVector::~DynamicVector() {
    delete [] this->elements;
}