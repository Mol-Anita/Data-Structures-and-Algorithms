#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	this->current = 0;
}

void SMIterator::first(){
	this->current = 0;
}
// BC = WC = TC = Theta(1)

void SMIterator::next(){
	if (current >= map.map_size)
		throw exception();
	this->current++;
}
// BC = WC = TC = Theta(1)

bool SMIterator::valid() const{
	if (current >= map.map_size)
		return false;
	return true;
}
// BC = WC = TC = Theta(1)

TElem SMIterator::getCurrent() const{
	if (current >= map.map_size)
		throw exception();
	return map.elements[current];
}
// BC = WC = TC = Theta(1)
