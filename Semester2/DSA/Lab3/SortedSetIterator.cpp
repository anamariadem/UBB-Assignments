#include "SortedSetIterator.h"
#include <exception>

using namespace std;

//theta(1)
SortedSetIterator::SortedSetIterator(const SortedSet& m) : sortedSet(m)
{
	//TODO - Implementation
}

//theta(1)
void SortedSetIterator::first() {
	//TODO - Implementation
    this->currentIndexInList = sortedSet.head;
}

//theta(1)
void SortedSetIterator::next() {
	//TODO - Implementation
    if (valid())
        this->currentIndexInList = sortedSet.next[this->currentIndexInList];
    else
        throw std::exception();
}

//theta(1)
TElem SortedSetIterator::getCurrent()
{
	//TODO - Implementation
    if(valid())
        return sortedSet.elements[this->currentIndexInList];
    else
        throw std::exception();
}

//theta(1)
bool SortedSetIterator::valid() const {
	//TODO - Implementation
    return this->currentIndexInList!=-1;
}