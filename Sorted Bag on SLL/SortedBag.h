#pragma once
#include <utility>
//DO NOT INCLUDE SORTEDBAGITERATOR

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

typedef TComp TKey;
typedef TElem TValue;
typedef std::pair<TKey, TValue> Pair;
typedef bool(*Condition)(TComp);

typedef struct Node {
	Node* previous = NULL;
	Node* next = NULL;
	Pair value;
} Node;


class SortedBagIterator;

class SortedBag {
	friend class SortedBagIterator;

private:
	Relation relation;
	int bag_size;
	Node* head;
	Node* tail;


public:
	//constructor
	SortedBag(Relation r);

	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurence of an element from a sorted bag
	//returns true if an element was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appears is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	//destructor
	~SortedBag();

	void filter(Condition cond);
};