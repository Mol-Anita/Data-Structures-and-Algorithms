#include "SetIterator.h"
#include "Set.h"
#include <exception>

SetIterator::SetIterator(const Set& s) : set(s)
{
	current = 0;
	while (s.table[current] == NULL_TELEM && current < set.m)
		current++;
}
//BC = Theta(1) - there is an element on the first position of the array
//WC = Theta(m) - the array is empty or it has only an element at the end
//TC = O(m)


void SetIterator::first() {
	current = 0;
	while (set.table[current] == NULL_TELEM && current < set.m)
		current++;
}
//BC = Theta(1) - there is an element on the first position of the array
//WC = Theta(m) - the array is empty or it has only an element at the end
//TC = O(m)

void SetIterator::next() {
	if (current == set.m)
		throw std::exception();
	current++;
	while (set.table[current] == NULL_TELEM && current < set.m)
		current++;
}
//BC = Theta(1) - there is an element right after the current one
//WC = Theta(m) - we are at the first element and the next one is at the end of the array
//TC = O(m)

TElem SetIterator::getCurrent()
{
	if (current == set.m)
		throw std::exception();
	return set.table[current];
}
//BC = WC = TC = Theta(1)

bool SetIterator::valid() const {
	return current < set.m;
}
//BC = WC = TC = Theta(1)



