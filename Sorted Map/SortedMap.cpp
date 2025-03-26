#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

void SortedMap::resize()
{
	TElem* new_array = new TElem[capacity * 2];
	for (int i = 0; i < map_size; i++) {
		new_array[i] = elements[i];
	}
	capacity *= 2;
	delete[] elements;
	elements = new_array;
}
//BC = WC = TC = Theta(map_size);


SortedMap::SortedMap(Relation r) {
	this->capacity = 20;
	this->map_size = 0;
	this->elements = new TElem[capacity];
	this->relation = r;
}
//BC = WC = TC = Theta(1)


TValue SortedMap::add(TKey k, TValue v) {
	int left = 0, right = map_size - 1, middle;

	while (left <= right) {
		middle = (left + right) / 2;
		if (elements[middle].first == k) {
			TValue old_value = elements[middle].second;
			elements[middle].second = v;
			return old_value;
		}
		if (relation(elements[middle].first, k))
			left = middle + 1;
		else
			right = middle - 1;

	}

	if (map_size == capacity)
		resize();

	int position = 0;
	while (relation(elements[position].first, k) and position < map_size)
		position++;
	for (int i = map_size; i > position; i--)
		elements[i] = elements[i - 1];
	elements[position] = pair<TKey, TValue>(k, v);
	map_size++;

	return NULL_TVALUE;
}
//BC = Theta(1) - the element is already in the array and it is found in the middle
//WC = Theta(map_size) - the array needs to be resized for the element to be added
//TC = amortized complexity of O(map_size) - the resize only happens rarely


TValue SortedMap::search(TKey k) const {
	int left = 0, right = map_size - 1, middle;

	while (left <= right) {
		middle = (left + right) / 2;
		if (elements[middle].first == k)
			return elements[middle].second;
		if (relation(elements[middle].first, k))
			left = middle + 1;
		else
			right = middle - 1;
	}

	return NULL_TVALUE;
}
//BC = Theta(1) - the element is found in the middle position
//WC = Theta(log2 map_size) -  the element is not in the array or its on the first or last position
// TC = O(log2 mapsize) 


TValue SortedMap::remove(TKey k) {
	int left = 0, right = map_size - 1, middle;
	TValue value = NULL_TVALUE;
	bool is_ascending = elements[0].first <= elements[map_size - 1].first;

	while (left <= right) {
		middle = (left + right) / 2;
		if (elements[middle].first == k) {
			value = elements[middle].second;
			break;
		}
		if (relation(elements[middle].first, k))
			left = middle + 1;
		else
			right = middle - 1;
	}

	if (value == NULL_TVALUE)
		return NULL_TVALUE;

	for (int i = middle; i < map_size - 1; i++)
		elements[i] = elements[i + 1];
	map_size--;
	return value;
}
//BC = Theta(log2 n) - the element is on the last position of the array or it is not int the array
//WC = Theta(map_size) - the element is on the first position of the array and all elements need to be shifted 
//TC = O(map_size)

int SortedMap::size() const {
	return map_size;
}
//BC = WC = TC = Theta(1)

bool SortedMap::isEmpty() const {
	return map_size == 0;
}
//BC = WC = TC = Theta(1)

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}
//BC = WC = TC = Theta(1)

SortedMap::~SortedMap() {
	delete[] elements;
}
//BC = WC = TC = Theta(1)

int SortedMap::getValueRange() const
{
	if (map_size == 0)
		return -1;

	int i = 1, min, max;
	min = max = this->elements[0].second;

	while (i < map_size) {
		if (min > this->elements[i].second)
			min = this->elements[i].second;

		if (max < this->elements[i].second)
			max = this->elements[i].second;
		i++;
	}
	return max - min;
}
//BC = WC = TC = Theta(map_size)
