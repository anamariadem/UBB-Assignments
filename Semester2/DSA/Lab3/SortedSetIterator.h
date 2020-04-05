#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& sortedSet;
	SortedSetIterator(const SortedSet& m);

	//TODO - Representation
    int currentIndexInList = sortedSet.head;

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};

