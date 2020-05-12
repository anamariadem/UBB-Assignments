#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include "DynamicVector.h"
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);
typedef int(*HashFunction)(TKey, int);

class Node{
public:
    Node* next;
    TKey key;
    DynamicVector<TValue> values;
};

class SortedMultiMap {
	friend class SMMIterator;

private:
    HashFunction hashFunction;
public:
    int length;
    int m; //capacity of hashtable
    Relation relation;
    Node** hashTable;
private:
    void findCurrentAndPreviousOfElementInList(Node* head, TKey elem, Node** current, Node** previous) const;

public:

    friend int hashF(int TKey, int m);
    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    DynamicVector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //removes a key together with all its values
    //returns a vector with the values that were previously associated to this value (and were removed)
    DynamicVector<TValue> removeKey(TKey key);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    void resize();

    void myPrint();

    Node** copyTable() const;

    // destructor
    ~SortedMultiMap();
};
