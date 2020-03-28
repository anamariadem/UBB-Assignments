//
// Created by Ana Maria on 22/03/2020.
//

#ifndef ASSIGNMENT2_27_LISTITERATOR_H
#define ASSIGNMENT2_27_LISTITERATOR_H

#include "SortedIndexedList.h"

//DO NOT CHANGE THIS PART
class ListIterator{
    friend class SortedIndexedList;
private:
    const SortedIndexedList& list;
    ListIterator(const SortedIndexedList& list);

    //TODO - Representation
    int currentIndex = 0;

public:
    void first();
    void next();
    bool valid() const;
    TComp getCurrent() const;
};
#endif //ASSIGNMENT2_27_LISTITERATOR_H
