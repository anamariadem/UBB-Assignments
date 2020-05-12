#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
    Node* headOfListToIterate;
    Node* currentKey;
    DynamicVector<TValue>::iterator currentValue{};
	//TODO - Representation
private:
    void merge(Node* head1, Node* head2, Node** finalHead);
public:
    SMMIterator(const SortedMultiMap& map);
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent();
   	~SMMIterator();
};

