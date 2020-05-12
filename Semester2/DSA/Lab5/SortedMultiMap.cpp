#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

//theta(1)
int hashF(int TKey, int m) {
    return abs(TKey%m);
}

//theta(m)
SortedMultiMap::SortedMultiMap(Relation r) {
	//TODO - Implementation
	this->relation = r;
	this->hashFunction = hashF;
	this->length = 0;
	this->m = 7;
	this->hashTable = new Node*[this->m];
	for(int i=0; i<this->m;i++)
	    this->hashTable[i] = nullptr;
}

//O(n)
void SortedMultiMap::add(TKey c, TValue v) {
	//TODO - Implementation
	if((double)(this->length/this->m) >= 0.7)
	    this->resize();
    Node* currentNode = nullptr;
    Node* previousNode = nullptr;
    int position = this->hashFunction(c, this->m);
    Node* head = this->hashTable[position];

    this->findCurrentAndPreviousOfElementInList(head, c, &currentNode, &previousNode);

    if(currentNode != nullptr){
        currentNode->values.addToDynamicVector(v);
        this->length++;
        return;
    }
    if(previousNode == nullptr and currentNode == nullptr){
        Node* newNode = new Node();
        newNode->key = c;
        newNode->values.addToDynamicVector(v);
        newNode->next = this->hashTable[position];
        this->hashTable[position] = newNode;
        this->length ++;
    }

    if(previousNode != nullptr){
        Node* newNode = new Node();
        newNode->key =c;
        newNode->values.addToDynamicVector(v);
        newNode->next = previousNode->next;
        previousNode->next = newNode;
        this->length ++;
    }
}

//O(n)
DynamicVector<TValue> SortedMultiMap::search(TKey c) const {
	//TODO - Implementation
    int position = this->hashFunction(c, this->m);
    Node* currentNode = this->hashTable[position];
    while (currentNode != nullptr and this->relation(currentNode->key,c)){
        if(currentNode->key == c)
            return currentNode->values;
        else{
            currentNode = currentNode->next;
        }
    }
	return DynamicVector();
}

//O(n)
bool SortedMultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
    Node* currentNode = nullptr;
    Node* previousNode = nullptr;
    int position = this->hashFunction(c, this->m);
    Node* head = this->hashTable[position];

    this->findCurrentAndPreviousOfElementInList(head, c, &currentNode, &previousNode);
    if(currentNode == nullptr)
        return false;

    if(previousNode == nullptr){
        int positionToRemove = currentNode->values.getPositionOfElement(v);
        if(positionToRemove == -1)
            return false;
        currentNode->values.deleteFromDynamicVector(positionToRemove);
        if(currentNode->values.getSizeOfVector() == 0){
            this->hashTable[position] = currentNode->next;
        }
        this->length --;
    } else{
        int positionToRemove = currentNode->values.getPositionOfElement(v);
        if(positionToRemove == -1)
            return false;
        currentNode->values.deleteFromDynamicVector(positionToRemove);
        if(currentNode->values.getSizeOfVector() == 0){
            previousNode->next = currentNode->next;
            currentNode->next = nullptr;
        }
        this->length --;
    }
    return true;
}

/*
 * BC-theta(1)- the key is the first in the corresponding list
 * WC-theta(n) - the current node remains nullptr, so it goes through the whole list trying to find it
 * Total: O(n)
 * n-> the number of elem in that corresponding list
 */
DynamicVector<TValue> SortedMultiMap::removeKey(TKey key) {
    Node* currentNode = nullptr;
    Node* previousNode = nullptr;
    int position = this->hashFunction(key, this->m);
    Node* head = this->hashTable[position];
    DynamicVector<TValue > values;

    this->findCurrentAndPreviousOfElementInList(head, key, &currentNode, &previousNode);

    if(currentNode == nullptr)
        return DynamicVector<TValue>();

    if(previousNode == nullptr){
        values = currentNode->values;
        this->hashTable[position] = currentNode->next;
        this->length = this->length - values.getSizeOfVector();
    }else{
        values = currentNode->values;
        previousNode->next = currentNode->next;
        currentNode->next = nullptr;
        this->length = this->length - values.getSizeOfVector();
    }

    return values;
}


//theta(1)
int SortedMultiMap::size() const {
	//TODO - Implementation
	return length;
}

//theta(1)
bool SortedMultiMap::isEmpty() const {
	//TODO - Implementation
	return length==0;
}

//theta(1)
SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

//O(n*n) -> n is the number of elements in hash table
void SortedMultiMap::resize() {
    this->m *= 2;
    auto newTable = new Node*[this->m];
    for(int i=0; i<this->m;i++)
        newTable[i] = nullptr;

    for(int i=0;i<this->m/2;i++){
        Node* nodeToAdd = this->hashTable[i];
        while(nodeToAdd != nullptr){
            int position = this->hashFunction(nodeToAdd->key, this->m);
            Node* head = newTable[position];
            Node* current= nullptr;
            Node* previous = nullptr;

            this->findCurrentAndPreviousOfElementInList(head, nodeToAdd->key, &current, &previous);

            if(previous == nullptr){
                Node* newNode = new Node();
                newNode->key = nodeToAdd->key;
                newNode->values = nodeToAdd->values;
                newNode->next = head;
                newTable[position] = newNode;
            } else{
                Node* newNode = new Node();
                newNode->key = nodeToAdd->key;
                newNode->values = nodeToAdd->values;
                newNode->next = previous->next;
                previous->next = newNode;
            }

            nodeToAdd = nodeToAdd->next;
        }
    }

    for(int i=0;i<m/2;i++){
        Node* current = this->hashTable[i];
        while(current != nullptr){
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    delete this->hashTable;

    this->hashTable = newTable;
}

//O(n)
void SortedMultiMap::findCurrentAndPreviousOfElementInList(Node *head, TKey elem, Node **current, Node **previous) const{
    Node* auxiliaryCurrent = head;
    Node* auxiliaryPrevious = nullptr;
    bool found = false;

    while(auxiliaryCurrent != nullptr and found == false and this->relation(auxiliaryCurrent->key, elem)){
        if(auxiliaryCurrent->key == elem)
            found = true;
        else{
            auxiliaryPrevious = auxiliaryCurrent;
            auxiliaryCurrent = auxiliaryCurrent->next;
        }
    }

    if(found){
        *current = auxiliaryCurrent;
        *previous = auxiliaryPrevious;
    } else{
        *current = nullptr;
        *previous = auxiliaryPrevious;
    }
}

//O(n*n) -> n in the number of elements in hash table
Node **SortedMultiMap::copyTable() const {
    auto newTable = new Node*[this->m];
    for(int i=0; i<this->m;i++)
        newTable[i] = nullptr;

    for(int i=0;i<this->m;i++){
        Node* nodeToAdd = this->hashTable[i];
        while(nodeToAdd != nullptr){
            //int position = this->hashFunction(nodeToAdd->key, this->m);
            Node* head = newTable[i];
            Node* current= nullptr;
            Node* previous = nullptr;
            this->findCurrentAndPreviousOfElementInList(head, nodeToAdd->key, &current, &previous);

            if(previous == nullptr){
                Node* newNode = new Node();
                newNode->key = nodeToAdd->key;
                newNode->values = nodeToAdd->values;
                newNode->next = head;
                newTable[i] = newNode;
            } else{
                Node* newNode = new Node();
                newNode->key = nodeToAdd->key;
                newNode->values = nodeToAdd->values;
                newNode->next = previous->next;
                previous->next = newNode;
            }

            nodeToAdd = nodeToAdd->next;
        }
    }
    return newTable;
}

//theta(n)
SortedMultiMap::~SortedMultiMap() {
    //TODO - Implementation
    for(int i=0;i<this->m;i++){
        Node* current = this->hashTable[i];
        while(current != nullptr){
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    delete this->hashTable;
}

void SortedMultiMap::myPrint() {
    for(int i=0;i<m;i++){
        Node* head = this->hashTable[i];
        cout<<"List on position "<<i<<" \n";
        while(head!= nullptr){
            cout<<head->key<<" has values: ";
            for(auto &value: head->values)
                cout<<value<<" ";
            head = head->next;
            cout<<"\n";
        }
    }
}
