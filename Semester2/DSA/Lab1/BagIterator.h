//
// Created by Ana Maria on 10/03/2020.
//

#ifndef ASSIGNMENT1_6_BAGITERATOR_H
#define ASSIGNMENT1_6_BAGITERATOR_H

#include "bag.h"

class BagIterator
{
    //DO NOT CHANGE THIS PART
    friend class Bag;

private:
    const Bag& bag;
    //TODO  - Representation
    int position_in_positions_array;


    BagIterator(const Bag& c);
public:

    void last();
    //changes the current element from the iterator to the previous element, or, if the current element was the first, makes the iterator invalid
    //throws an exception if the iterator is not valid
    void previous();
    bool validBiDirectional() const;
    void first();
    void next();
    TElem getCurrent() const;
    bool valid() const;
};

#endif //ASSIGNMENT1_6_BAGITERATOR_H
