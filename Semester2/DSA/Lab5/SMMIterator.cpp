#include "SMMIterator.h"
#include "SortedMultiMap.h"

#include <iostream>
using namespace std;

//O(n*m)
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	//TODO - Implementation
    Node* finalPointer = nullptr;
    auto copyOfTable = map.copyTable();

    this->merge(copyOfTable[0], copyOfTable[1], &finalPointer);
    for(int i=2;i<this->map.m;i++)
        this->merge(finalPointer, copyOfTable[i], &finalPointer);

    this->headOfListToIterate = finalPointer;
    this->currentKey = this->headOfListToIterate;
    if(currentKey!=nullptr)
        this->currentValue = this->headOfListToIterate->values.begin();

}

//theta(1)
void SMMIterator::first(){
	//TODO - Implementation
    this->currentKey = this->headOfListToIterate;
    if(currentKey!=nullptr)
        this->currentValue = this->headOfListToIterate->values.begin();
}

//theta(1)
void SMMIterator::next(){
	//TODO - Implementation
	if(this->currentKey == nullptr)
	    throw std::exception();
    this->currentValue++;
    if(this->currentValue == this->currentKey->values.end()){
        this->currentKey = this->currentKey->next;
        if(this->currentKey != nullptr)
            this-> currentValue = this->currentKey->values.begin();
    }
}

//theta(1)
bool SMMIterator::valid() const{
	//TODO - Implementation
    return this->currentKey != nullptr;
}

//theta(1)
TElem SMMIterator::getCurrent(){
	//TODO - Implementation
	if(this->currentKey == nullptr)
	    throw std::exception();
	TElem elem;
	elem.first = this->currentKey->key;
	elem.second = *this->currentValue;

	return elem;
}

//O(n+m) where n is the number of elements of the first list and m is the number of elements of the second list
void SMMIterator::merge(Node *head1, Node *head2, Node **finalHead) {
    Node* newListHead = nullptr;
    Node* newListTail= nullptr;

    while (head1!= nullptr and head2!= nullptr){
        Node* chosenNode = nullptr;
        if(this->map.relation(head1->key, head2->key)){
            chosenNode = head1;
            head1=head1->next;
        } else{
            chosenNode = head2;
            head2 = head2->next;
        }
        if(newListHead == nullptr){
            newListHead = chosenNode;
            newListTail = chosenNode;
        } else{
            newListTail->next = chosenNode;
            newListTail = chosenNode;
        }
    }
    Node* remainingNode = nullptr;
    if(head1!=nullptr)
        remainingNode = head1;
    else
        remainingNode = head2;
    if(newListHead!= nullptr)
        newListTail->next = remainingNode;
    else
        newListHead = remainingNode;

    *finalHead = newListHead;
}

SMMIterator::~SMMIterator() {
}


