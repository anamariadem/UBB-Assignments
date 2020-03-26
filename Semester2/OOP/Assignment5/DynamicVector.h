//
// Created by Ana Maria on 19/03/2020.
//

#ifndef ASSIGNMENT5_DYNAMICVECTOR_H
#define ASSIGNMENT5_DYNAMICVECTOR_H

#include "Domain.h"
typedef NorvenTurret TElement;

class DynamicVector {
private:
    int size;
    int capacity;
    TElement* elements;

    void resizeDynamicVector(int factor =2);
    bool isFullCapacity() const ;

public:
    // constructor for a Dynamic Vector
    DynamicVector(int capacity = 2);

    // copy constructor for a Dynamic Vector
    DynamicVector(const DynamicVector& dynamicVector);

    // overload of the assignment operator
    DynamicVector& operator=(const DynamicVector& dynamicVector);

    // adds a new element to the dynamic vector
    void addToDynamicVector(const TElement& element);

    void deleteFromDynamicVector(int& positionInArray);

    void updateElementInDynamicArray(int& positionInArray, TElement& newElement);

    int getSizeOfVector() const;

    TElement getElement(int& positionInArray);

    ~DynamicVector();
};


#endif //ASSIGNMENT5_DYNAMICVECTOR_H
