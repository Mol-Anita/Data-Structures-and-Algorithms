#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>
#include <iostream>

bool relation1(TComp e1, TComp e2) {
	return e1 <= e2;
}

void testAll() {
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);

	assert(sb.size() == 6);
	assert(sb.nrOccurrences(5) == 2);

	assert(sb.remove(5) == true);
	assert(sb.size() == 5);

	assert(sb.search(6) == true);
	assert(sb.isEmpty() == false);

	SortedBagIterator it = sb.iterator();
	assert(it.valid() == true);
	while (it.valid()) {
		it.getCurrent();
		it.next();
	}
	assert(it.valid() == false);
	it.first();
	assert(it.valid() == true);

}

bool evenNumber(TComp elem) {
	return elem % 2 == 0;
}

bool oddNumber(TComp elem) {
	return elem % 2 != 0;
}

void testFilter() {
	std::cout << "Test filter";
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);

	sb.filter(evenNumber);
	assert(sb.size() == 4);
	
	sb.add(2);
	sb.add(7);
	sb.add(7);
	sb.add(3);
	sb.filter(oddNumber);
	assert(sb.size() == 3);

	SortedBag sb2(relation1);
	sb.filter(oddNumber);

}
