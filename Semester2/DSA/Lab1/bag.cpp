//
// Created by Ana Maria on 10/03/2020.
//

#include "bag.h"
#include "BagIterator.h"
#include <iostream>
using namespace std;

// theta(1)
Bag::Bag() {
    //TODO - Implementation
    this->capacity_of_array_of_unique_elements = 500;
    this->number_of_unique_elements = 0;
    this->array_of_unique_elements = new TElem [this->capacity_of_array_of_unique_elements];

    this->capacity_of_array_of_positions = 500;
    this->number_of_positions = 0;
    this->array_of_positions = new TElem [this->capacity_of_array_of_positions];
}

// O(n) n = max{number of unique elements, number of positions}
void Bag::add(TElem elem) {
    //TODO - Implementation
    if(this->capacity_of_array_of_unique_elements == this->number_of_unique_elements){
        this->capacity_of_array_of_unique_elements *= 2;
        auto* new_array_unique_elements = new TElem[this->capacity_of_array_of_unique_elements];
        for(int i=0; i<this->number_of_unique_elements; i++)
            new_array_unique_elements[i] = this->array_of_unique_elements[i];
        delete [] this->array_of_unique_elements;
        this->array_of_unique_elements = new_array_unique_elements;
    }

    if(this->capacity_of_array_of_positions == this->number_of_positions){
        this->capacity_of_array_of_positions *=2;
        auto* new_array_positions = new TElem[this->capacity_of_array_of_positions];
        for(int i=0;i<this->number_of_positions; i++)
            new_array_positions[i] = this->array_of_positions[i];
        delete [] this->array_of_positions;
        this->array_of_positions = new_array_positions;
    }
    int index_in_array_of_unique_elements = search_position(elem);
    if (index_in_array_of_unique_elements == -1){
        this->array_of_unique_elements[this->number_of_unique_elements++] = elem;
        this->array_of_positions[this->number_of_positions] = this->number_of_unique_elements-1;
        this->number_of_positions ++;
    } else{
        this->array_of_positions[this->number_of_positions ++] = index_in_array_of_unique_elements;
    }

}

// O(n)
bool Bag::remove(TElem elem) {
    //TODO - Implementation
    if(!search(elem))
        return false;

    int index_of_element = search_position(elem);

    if(nrOccurrences(elem) == 1){
        for(int i = index_of_element; i < this->number_of_unique_elements ; i++)
            this->array_of_unique_elements[i] = this->array_of_unique_elements[i+1];
        this->number_of_unique_elements --;

        int pos_of_index =-1;
        for(int i=0; i < this->number_of_positions;i++) {
            if (this->array_of_positions[i] == index_of_element)
                pos_of_index = i;
            if(this->array_of_positions[i] > index_of_element)
                this->array_of_positions[i] --;
        }
        this->array_of_positions[pos_of_index] = this->array_of_positions[this->number_of_positions-1];
        this->number_of_positions--;

    }
    else if(nrOccurrences(elem) >=1){
        int pos_of_index = -1;
        for(int i=0; i < this->number_of_positions;i++)
            if(this->array_of_positions[i] == index_of_element) {
                pos_of_index = i;
                break;
            }
        //for(int i=pos_of_index; i< this->number_of_positions ;i++)
          //  this->array_of_positions[i] = this->array_of_positions[i+1];
        //this->number_of_positions --;
        this->array_of_positions[pos_of_index] = this->array_of_positions[this->number_of_positions-1];
        this->number_of_positions--;
    }
    return true;
}

// O(n) n - number of unique elements
bool Bag::search(TElem elem) const {
    //TODO - Implementation
    for(int i=0; i<this->number_of_unique_elements; i++) {
        if (this->array_of_unique_elements[i] == elem)
            return true;
    }
    return false;
}

// O(n) n - number of unique elements
int Bag::search_position(TElem elem) const{
    for(int i=0; i<this->number_of_unique_elements; i++)
        if (this->array_of_unique_elements[i] == elem)
            return i;
    return -1;
}

// theta(n) n - number of positions
int Bag::nrOccurrences(TElem elem) const {
    //TODO - Implementation
    int index_of_elem = search_position(elem), nrOccurences = 0;
    for(int i=0; i<number_of_positions ;i++)
        if(this->array_of_positions[i] == index_of_elem)
            nrOccurences ++;
    return nrOccurences;
}

// theta(1)
int Bag::size() const {
    //TODO - Implementation
    return this->number_of_positions;
}

// theta(1)
int Bag::number_unique_elems() const {
    return this->number_of_unique_elements;
}

// theta(1)
bool Bag::isEmpty() const {
    //TODO - Implementation
    return this->number_of_unique_elements == 0 && this->number_of_positions == 0;
}

//theta(1)
BagIterator Bag::iterator() const {
    return BagIterator(*this);
}

void Bag::printBag(){
    cout<<"Unique elems: ";
    for(int i =0; i<this->number_of_unique_elements;i++)
        cout<<this->array_of_unique_elements[i]<<" ";
    cout<<endl;

    cout<<"Positions: ";
    for(int i =0; i<this->number_of_positions;i++)
        cout<<this->array_of_positions[i]<<" ";
    cout<<endl;

    for(int i=0; i<this->number_of_positions;i++){
        cout<<this->array_of_unique_elements[this->array_of_positions[i]]<<" ";
    }
    cout<<endl;
}

// theta(1)
Bag::~Bag() {
    //TODO - Implementation
    delete [] array_of_positions;
    delete [] array_of_unique_elements;
}



