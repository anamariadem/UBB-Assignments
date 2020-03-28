//
// Created by Ana Maria on 22/03/2020.
//

#ifndef ASSIGNMENT2_27_SORTEDINDEXEDLIST_H
#define ASSIGNMENT2_27_SORTEDINDEXEDLIST_H


//DO NOT INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
#define NULL_TCOMP -11111

class Node{
public:
    TComp data;
    Node* next;
};

class SLL{
private:
    Node* head;
    int size;
public:
    SLL() { head = nullptr, size =0 ;}

    Node* getHead() const { return head;}
    int getSize() const { return size; }
    void setHead(Node* newNode) {head = newNode;}
    void setSize(int newSize) {size = newSize;}
};

class SortedIndexedList {
private:
    friend class ListIterator;
private:
    //TODO - Representation
    SLL SortedList{};
    Relation relation;

public:
    // constructor
    SortedIndexedList(Relation r);

    // returns the size of the list
    int size() const;

    //checks if the list is empty
    bool isEmpty() const;

    // returns an element from a position
    //throws exception if the position is not valid
    TComp getElement(int pos) const;

    // adds an element to a given position
    //throws an exception if the position is not valid
    void add(TComp e);

    // removes an element from a given position
    //returns the removed element
    //throws an exception if the position is not valid
    TComp remove(int pos);

    // searches for an element and returns the first position where the element appears or -1 if the element is not in the list
    int search(TComp e) const;

    // returns an iterator set to the first element of the list or invalid if the list is empty
    ListIterator iterator();

    //destructor
    ~SortedIndexedList();

};


#endif //ASSIGNMENT2_27_SORTEDINDEXEDLIST_H
