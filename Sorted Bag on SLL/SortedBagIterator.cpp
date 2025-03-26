#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	current_node = bag.head;
	current_frequency = 0;
}
// BC = WC = TC = Theta(1)


TComp SortedBagIterator::getCurrent() {
	if (current_node == NULL)
		throw exception();
	return current_node->value.first;
}
// BC = WC = TC = Theta(1)


bool SortedBagIterator::valid() {
	return current_node != NULL;
}
// BC = WC = TC = Theta(1)


void SortedBagIterator::next() {
	if (current_node == NULL)
		throw exception();
	if (current_frequency < current_node->value.second - 1)
		current_frequency++;
	else {
		current_frequency = 0;
		current_node = current_node->next;
	}
}
// BC = WC = TC = Theta(1)

void SortedBagIterator::first() {
	current_node = bag.head;
	current_frequency = 0;
}
// BC = WC = TC = Theta(1)

