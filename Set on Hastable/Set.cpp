#include "Set.h"
#include "SetITerator.h"
#include <math.h>


int Set::hash(TElem k) const
{
	return abs(k % m);
}
//BC = WC = TC = Theta(1)

void Set::resize()
{
	int newM = 2 * this->m;
	TElem* newTable = new TElem[newM];
	int* newNext = new int[newM];
	int newFirstEmpty = 0;
	for (int i = 0; i < newM; i++) {
		newTable[i] = NULL_TELEM;
		newNext[i] = -1;
	}
	int oldM = m;
	this->m = newM;
	for (int i = 0; i < oldM; i++) {
		int pos = hash(table[i]);
		if (table[i] != NULL_TELEM) {
			if (newTable[pos] == NULL_TELEM) {
				newTable[pos] = table[i];
				if (pos == newFirstEmpty) {
					newFirstEmpty++;
					while (newFirstEmpty < newM && newTable[newFirstEmpty] != NULL_TELEM)
						newFirstEmpty++;
				}
			}
			else {
				int current = pos;
				while (newNext[current] != -1)
					current = newNext[current];
				newTable[newFirstEmpty] = table[i];
				newNext[current] = newFirstEmpty;
				newFirstEmpty++;
				while (newFirstEmpty < newM && newTable[newFirstEmpty] != NULL_TELEM)
					newFirstEmpty++;
			}
			
		}
	}
	delete[] table;
	delete[] nextPos;
	table = newTable;
	nextPos = newNext;
	firstEmpty = newFirstEmpty;
}
//BC = WC = TC = Theta(newM)


void Set::changeFirstEmpty()
{
	firstEmpty++;
	while (firstEmpty < this->m && table[firstEmpty] != NULL_TELEM)
		firstEmpty++;
}

Set::Set() {
	m = 13;
	table = new TElem[m];
	nextPos = new int[m];
	firstEmpty = 0;
	for (int i = 0; i < m; i++) {
		table[i] = NULL_TELEM;
		nextPos[i] = -1;
	}
}
//BC = WC = TC = Theta(m)

bool Set::add(TElem elem) {
	if (firstEmpty == m)
		resize();
	int pos = hash(elem);
	if (table[pos] == NULL_TELEM) {
		table[pos] = elem;
		nextPos[pos] = -1;
		if (pos == firstEmpty)
			changeFirstEmpty();
		return true;
	}
	else {
		int current = pos;
		while (nextPos[current] != -1 && table[current] != elem) {
			current = nextPos[current];
		}
		if (table[current] == elem)
			return false;
		table[firstEmpty] = elem;
		nextPos[firstEmpty] = -1;
		nextPos[current] = firstEmpty;
		changeFirstEmpty();
		return true;
	}
}
//BC = Theta(1) - the position which the element hashes to is free
//WC = Theta(m) amortized - there are m-1 other elements in the list which hash to the same position as the element we want to add
//TC = O(m)

bool Set::remove(TElem elem) {

	int pos = hash(elem);
	int prevpos = -1;
	while (table[pos] != elem && pos != -1) {
		prevpos = pos;
		pos = nextPos[pos];
	}
		
	if (pos == -1)
		return false;
	else {
		bool over = false;
		do {
			int p = nextPos[pos];
			int prevp = pos;
			while (p != -1 && hash(table[p]) != pos) {
				prevp = p;
				p = nextPos[p];
			}
			if (p == -1)
				over = true;
			else {
				table[pos] = table[p];
				prevpos = prevp;
				pos = p;
			}
		} while (!over);

		if (prevpos == -1) {
			int idx = 0;
			while (idx < m && prevpos == -1)
				if (nextPos[idx] == pos)
					prevpos = idx;
				else
					idx++;
		}
		if (prevpos != -1)
			nextPos[prevpos] = nextPos[pos];

		table[pos] = NULL_TELEM;
		nextPos[pos] = -1;
		if (firstEmpty > pos)
			firstEmpty = pos;
		return true;
	}
}
//BC = Theta(1) - if the element doesn't exist and no other element is on the position to which it hashes or its the only element which hashes to that position 
//and its nextPos is -1
//WC = Theta(m) - we have to move all elements of the array before we can delete our element from it
//TC = O(m)


int Set::size() const {
	int size = 0;
	for (int i = 0; i < m;i++)
		if (table[i] != NULL_TELEM)
			size++;
	return size;
}
//BC = WC = TC = Theta(m)

bool Set::isEmpty() const {
	if (firstEmpty != 0)
		return false;
	else {
		int pos = 0;
		while (pos < m) {
			if (table[pos] != NULL_TELEM)
				return false;
			pos++;
		}
	}
	return true;
}
//BC = Theta(1) - the first position is occupied
//WC = Theta(m) - only the last position is occupied
//TC = O(m)

Set::~Set() {
	delete[] this->table;
	delete[] this->nextPos;
}
//BC = WC = TC = Theta(1)


SetIterator Set::iterator() const {
	return SetIterator(*this);
}
//BC = WC = TC = Theta(1)



bool Set::search(TElem elem) const {
	int pos = hash(elem);

	while (pos != -1) {
		if (table[pos] == elem)
			return true;
		pos = nextPos[pos];
	}
	return false;
}
//BC = Theta(1) - we find our elem on the first pos we look
//WC = Theta(m) - the element is not in the list or it has m-1 other elements in front of it in its linked list
//TC = O(m)

bool Set::isSubsetOf(Set& s) const
{
	if (this->isEmpty())
		return true;
	for (int i = 0; i < this->m; i++) {
		if (this->table[i] != NULL_TELEM) {
			if (!s.search(this->table[i])) {
				return false;
			}
		}
	}
	return true;
}
//BC = Theta(this->m) - we find every element from this set on the first position that we look for it in set s
//WC = Theta(this->m * k) - k - avg lengths of the linked lists from S,  
// we have to go through the linked lists from the positions the elements hash to and find the at the end
//TC = O(this->m * k)


