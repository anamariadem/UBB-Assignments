//
// Created by Ana Maria on 22/03/2020.
//

#include "SortedIndexedList.h"
#include "ListIterator.h"
#include <iostream>
using namespace std;
#include <exception>

// theta(1)
SortedIndexedList::SortedIndexedList(Relation r) {
    //TODO - Implementation
    this->relation = r;
}

// theta(1)
int SortedIndexedList::size() const {
    //TODO - Implementation
    return this->SortedList.getSize();
}

// theta(1)
bool SortedIndexedList::isEmpty() const {
    //TODO - Implementation
    return size() == 0;
}

// O(n)
TComp SortedIndexedList::getElement(int i) const{
    //TODO - Implementation
    if(i >= size())
        throw std::exception();

    Node* current = this->SortedList.getHead();
    int position = 0;
    while (current != nullptr && position < i){
        current = current->next;
        position++;
    }
    return current->data;
}

// O(n)
TComp SortedIndexedList::remove(int i) {
    //TODO - Implementation

    if(i == -1)
        throw std::exception();

    if(i >= size())
        throw std::exception();

    Node* currentNode = this->SortedList.getHead();
    Node* previousNode = nullptr;
    int currentPosition = 0;

    while (currentNode != nullptr and currentPosition < i){
        previousNode = currentNode;
        currentNode=currentNode->next;
        currentPosition++;
    }

    if(currentNode != nullptr and previousNode == nullptr){
        // we delete the head
        this->SortedList.setHead(currentNode->next);
        int currentSize = this->SortedList.getSize();
        this->SortedList.setSize(currentSize -1);
    } else if (currentNode != nullptr){
        previousNode->next = currentNode->next;
        currentNode->next = nullptr;
        int currentSize = this->SortedList.getSize();
        this->SortedList.setSize(currentSize -1);
    }
    return currentNode->data;
}

// O(n)
int SortedIndexedList::search(TComp e) const {
    //TODO - Implementation
    Node* current = this->SortedList.getHead();
    int position = 0;
    while(current != nullptr && current->data != e) {
        current = current->next;
        position++;
    }
    if(position == size())
        return -1;
    return position;
}

// O(n)
void SortedIndexedList::add(TComp e) {
    //TODO - Implementation
    int position = 0;
    Node* current = this->SortedList.getHead();
    while(current != nullptr && !this->relation(e, current->data)){
        current = current->next;
        position++;
    }

    if(position == 0){
        // we insert at the beginning
        Node* newNode = new Node();
        newNode->data = e;
        newNode->next = this->SortedList.getHead();
        this->SortedList.setHead(newNode);
        int currentSize = this->SortedList.getSize();
        this->SortedList.setSize(currentSize +1);
    } else{
        Node* currentNode = this->SortedList.getHead();
        int currentPosition = 0;
        while(currentPosition < position - 1 and currentNode != nullptr){
            currentNode = currentNode->next;
            currentPosition++;
        }
        if(currentNode!= nullptr){
            Node* newNode = new Node();
            newNode->data = e;
            newNode->next = currentNode->next;
            currentNode->next = newNode;
            int currentSize = this->SortedList.getSize();
            this->SortedList.setSize(currentSize +1);
        }
    }
}

// theta(1)
ListIterator SortedIndexedList::iterator(){
    return ListIterator(*this);
}

//destructor
// O(n)
SortedIndexedList::~SortedIndexedList() {
    //TODO - Implementation
    Node* current = this->SortedList.getHead();
    while(current != nullptr){
        Node* next = current->next;
        delete current;
        current = next;
    }
}
