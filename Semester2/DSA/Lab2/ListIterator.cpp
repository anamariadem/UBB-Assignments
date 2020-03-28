//
// Created by Ana Maria on 22/03/2020.
//

#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

//theta(1)
ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
    //TODO - Implementation
}

//theta(1)
void ListIterator::first(){
    //TODO - Implementation
    this->currentIndex = 0;
}

//theta(1)
void ListIterator::next(){
    //TODO - Implementation
    if(valid())
        this->currentIndex ++;
    else
        throw std::exception();
}

//theta(1)
bool ListIterator::valid() const{
    //TODO - Implementation
    return currentIndex < list.size();
}

//O(n)
TComp ListIterator::getCurrent() const{
    //TODO - Implementation
    return list.getElement(currentIndex);
}


