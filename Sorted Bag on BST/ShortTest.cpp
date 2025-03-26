#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>
#include <iostream>

bool relation1(TComp e1, TComp e2) {
	return e1 <= e2;
}

bool relation4(TComp e1, TComp e2) {
	return e1 >= e2;
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

void testRange()
{
	SortedBag sb(relation1);
	assert(sb.getRange() == -1);
	sb.add(5);
	assert(sb.getRange() == 0);
	sb.add(6);
	assert(sb.getRange() == 1);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);

	assert(sb.getRange() == 10);

	SortedBag sb2(relation4);
	sb2.add(5);
	sb2.add(6);
	sb2.add(0);
	sb2.add(5);
	sb2.add(10);
	sb2.add(8);

	assert(sb2.getRange() == -10);

	std::cout << "Range test passed!" << std::endl;

}




