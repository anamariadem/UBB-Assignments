#include <iostream>
#include "SortedSet.h"
#include "SortedSetIterator.h"

//theta(1) as INIT_CAPACITY is very small at the beginning
SortedSet::SortedSet(Relation r) {
	//TODO - Implementation
	this->relation = r;
	this->capacity = INIT_CAPACITY;
	this->elements = new TComp[this->capacity];
	this->next = new int[this->capacity];
	this->head = -1;

	for(int i=0;i<this->capacity-1;i++)
	    this->next[i] = i+1;
	this->next[this->capacity-1] = -1;
	this->firstEmpty = 0;
	this->sizeOfArray = 0;
}

//O(n)
bool SortedSet::add(TComp elem) {
	//TODO - Implementation
	int currentPosition, previousPosition;
	this->findCurrentAndPrevious(elem, currentPosition, previousPosition);
	if(currentPosition!=-1)
        return false;

	if(this->firstEmpty == -1)
	    this->resize();

	if(previousPosition == -1){
        int newPosition = this->firstEmpty;
        this->elements[newPosition] = elem;
        this->firstEmpty = this->next[this->firstEmpty];
        this->next[newPosition] = this->head;
        this->head = newPosition;
        this->sizeOfArray++;
	} else{
        int newPosition = this->firstEmpty;
        this->firstEmpty = this->next[this->firstEmpty];
        this->elements[newPosition] = elem;
        this->next[newPosition] = this->next[previousPosition];
        this->next[previousPosition] = newPosition;
        this->sizeOfArray++;
	}

	return true;
}

//O(n)
bool SortedSet::remove(TComp elem) {
	//TODO - Implementation
    int currentPosition, previousPosition;
    this->findCurrentAndPrevious(elem, currentPosition, previousPosition);
    if(currentPosition==-1)
        return false;

    if(currentPosition == this->head){
        this->head = this->next[this->head];
    } else{
        this->next[previousPosition] = this->next[currentPosition];
    }

    this->next[currentPosition] = this->firstEmpty;
    this->firstEmpty = currentPosition;
    this->sizeOfArray--;
	return true;
}

//O(n)
bool SortedSet::search(TComp elem) const {
	//TODO - Implementation
	int current = this->head;
	while(current!=-1 and this->relation(this->elements[current],elem))
	    if(this->elements[current] == elem)
            return true;
	    else
            current = this->next[current];

    return false;
}

//theta(n) n is the doubled capacity
void SortedSet::resize() {
    auto* newElements = new TComp[this->capacity*2];
    auto* newNext = new int[this->capacity*2];

    for(int i=0; i<this->sizeOfArray;i++){
        newElements[i] = this->elements[i];
        newNext[i] = this->next[i];
    }

    for(int i=this->capacity; i<this->capacity*2-1;i++)
        newNext[i] = i+1;
    newNext[this->capacity*2-1] =-1;

    delete [] this->elements;
    delete [] this->next;

    this->elements = newElements;
    this->next = newNext;
    this->firstEmpty = this->capacity;
    this->capacity *= 2;
}

//O(n)
void SortedSet::findCurrentAndPrevious(TComp elem, int &current, int &previous) {
    int auxiliar = this->head, auxiliarPrevious = -1;
    bool found = false;

    while(auxiliar!=-1 and found == false and this->relation(this->elements[auxiliar], elem)){
        if(this->elements[auxiliar] == elem)
            found = true;
        else{
            auxiliarPrevious = auxiliar;
            auxiliar = this->next[auxiliar];
        }
    }

    if(found){
        current = auxiliar;
        previous = auxiliarPrevious;
    } else{
        current = -1;
        previous = auxiliarPrevious;
    }
}

//theta(1)
int SortedSet::size() const {
	//TODO - Implementation
	return this->sizeOfArray;
}

//theta(1)
bool SortedSet::isEmpty() const {
	//TODO - Implementation
	return this->sizeOfArray==0;
}

//theta(1)
SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}

//theta(1)
SortedSet::~SortedSet() {
	//TODO - Implementation
	delete [] this->elements;
	delete [] this->next;
}