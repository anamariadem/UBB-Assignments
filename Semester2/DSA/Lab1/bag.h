//
// Created by Ana Maria on 10/03/2020.
//

#ifndef ASSIGNMENT1_6_BAG_H
#define ASSIGNMENT1_6_BAG_H

//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -11111;
typedef int TElem;
class BagIterator;
class Bag {

private:
    //TODO - Representation
    TElem* array_of_unique_elements;
    int capacity_of_array_of_unique_elements;
    int number_of_unique_elements;

    TElem* array_of_positions;
    int capacity_of_array_of_positions;
    int number_of_positions;

    int search_position(TElem elem) const;


    //DO NOT CHANGE THIS PART
    friend class BagIterator;
public:
    //constructor
    Bag();

    //adds an element to the bag
    void add(TElem e);

    //removes one occurence of an element from a bag
    //returns true if an element was removed, false otherwise (if e was not part of the bag)
    bool remove(TElem e);

    //checks if an element appearch is the bag
    bool search(TElem e) const;

    //returns the number of occurrences for an element in the bag
    int nrOccurrences(TElem e) const;

    //returns the number of elements from the bag
    int size() const;

    int number_unique_elems() const;

    //returns an iterator for this bag
    BagIterator iterator() const;

    //checks if the bag is empty
    bool isEmpty() const;

    void printBag();

    //destructor
    ~Bag();
};

#endif //ASSIGNMENT1_6_BAG_H
