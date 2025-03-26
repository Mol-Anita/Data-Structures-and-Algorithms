#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;


FixedCapBiMapIterator::FixedCapBiMapIterator(const FixedCapBiMap& d) : map(d)
{
	current = 0;
}
// BC = WC = TC = Theta(1)


void FixedCapBiMapIterator::first() {
	current = 0;
}// BC = WC = TC = Theta(1)

void FixedCapBiMapIterator::next() {
	if (current >= map.mapSize)
		throw exception();
	current++;
}
// BC = WC = TC = Theta(1)

TElem FixedCapBiMapIterator::getCurrent(){
	if (current >= map.mapSize)
		throw exception();
	return map.elements[current];
}
// BC = WC = TC = Theta(1)

bool FixedCapBiMapIterator::valid() const {
	if (current >= map.mapSize)
		return false;
	return true;
}
// BC = WC = TC = Theta(1)


