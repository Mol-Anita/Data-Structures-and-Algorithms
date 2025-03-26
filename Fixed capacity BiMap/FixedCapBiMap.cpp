#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"

FixedCapBiMap::FixedCapBiMap(int capacity) {
	if (capacity <= 0) {
		throw exception();
	}	
	this->capacity = capacity;
	mapSize = 0;
	elements = new TElem[capacity];
	
}
// BC = WC = TC = Theta(1)

FixedCapBiMap::~FixedCapBiMap() {
	delete[] elements;
}
// BC = WC = TC = Theta(1)


bool FixedCapBiMap::add(TKey c, TValue v){
	if (mapSize == capacity) {
		throw exception();
	}
	int count = 0;
	for (int i = 0; i < mapSize && count < 2; i++) {
		if (elements[i].first == c) {
			count++;
		}
	}

	if (count == 2)
		return false;
	else {
		elements[mapSize].first = c;
		elements[mapSize].second = v;
		mapSize++;
		return true;
	}
}
//BC = Theta(1) - when the key c can already be found on the first two positions
//WC = Theta(mapSize) - when there is one or zero occurences of the given key, or not at all
// TC = O(mapSize) 

ValuePair FixedCapBiMap::search(TKey c) const {
	ValuePair values = pair<TValue, TValue>(NULL_TVALUE, NULL_TVALUE);
	int count = 0;
	for (int i = 0; i < mapSize && count < 2; i++) {
		if (elements[i].first == c)
			if (values.first == NULL_TVALUE)
				values.first = elements[i].second;
			else
				values.second = elements[i].second;
	}
	return std::pair<TValue, TValue>(values.first, values.second);
}
//BC = Theta(1) - when the key c can already be found on the first two positions
//WC = Theta(mapSize) - when there is one or zero occurences of the given key, or not at all
// TC = O(mapSize) 

bool FixedCapBiMap::remove(TKey c, TValue v){
	for (int i = 0; i < mapSize; i++) {
		if (elements[i].first == c and elements[i].second == v) {
			elements[i].first = elements[mapSize - 1].first;
			elements[i].second = elements[mapSize - 1].second;
			mapSize--;
			return true;
		}
	}
	return false;
}
//BC = Theta(1) - when the key-value pair can be found on the first position
//WC = Theta(mapSize) - when there is no occurence of the given key-value pair, or it can be found on the last position
// TC = O(mapSize) 

int FixedCapBiMap::size() const {
	return mapSize;
}
// BC = WC = TC = Theta(1)

bool FixedCapBiMap::isEmpty() const{
	return mapSize == 0;
}
// BC = WC = TC = Theta(1)

bool FixedCapBiMap::isFull() const {
	return mapSize == capacity;
}
// BC = WC = TC = Theta(1)

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}
// BC = WC = TC = Theta(1)


ValuePair FixedCapBiMap::removeKey(TKey k) {
	ValuePair values;
	values.first = NULL_TVALUE;
	values.second = NULL_TVALUE;
	int count = 0;

	for (int i = 0; i < mapSize && count < 2; i++) {
		if (elements[i].first == k) {
			if (count == 0) {
				values.first = elements[i].second;
				count++;
				elements[i] = elements[--mapSize];
				i--;
			}
			else {
				values.second = elements[i].second;
				count++;
				elements[i] = elements[--mapSize];
				i--;
			}
		}
	}
	return std::pair<TValue, TValue>(values.first, values.second);
}
//BC = Theta(1) - when the key k and its two values appear on the first two positions
//WC = Theta(mapSize) - when the the key k appears zero or one times, or its second appearence is on the last position
//TC = O(mapSize)
