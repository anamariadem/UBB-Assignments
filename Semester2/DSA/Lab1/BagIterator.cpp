//
// Created by Ana Maria on 10/03/2020.
//

#include <exception>
#include "BagIterator.h"
#include "bag.h"

using namespace std;

// theta(1)
BagIterator::BagIterator(const Bag& c): bag(c)
{
    //TODO - Implementation
    this->position_in_positions_array = 0;
}

// theta(1)
void BagIterator::first() {
    //TODO - Implementation
    this->position_in_positions_array = 0;
}

// theta(1)
void BagIterator::next() {
    //TODO - Implementation
    if(valid())
        position_in_positions_array +=1;
    else
        throw std::exception();
}



// theta(1)
void BagIterator::last() {
    this->position_in_positions_array = bag.number_of_positions-1;
}

// theta(1)
void BagIterator::previous() {
    if(validBiDirectional())
        this->position_in_positions_array--;
    else
        throw std::exception();
}

// theta(1)
bool BagIterator::validBiDirectional() const{
    return this->position_in_positions_array > 0 and this->position_in_positions_array < bag.number_of_positions;
}



// theta(1)
bool BagIterator::valid() const {
    //TODO - Implementation
    return this->position_in_positions_array < bag.number_of_positions;
}

// theta(1)
TElem BagIterator::getCurrent() const
{
    //TODO - Implementation
    if(valid())
        return bag.array_of_unique_elements[bag.array_of_positions[position_in_positions_array]];
    else
        throw std::exception();
}

