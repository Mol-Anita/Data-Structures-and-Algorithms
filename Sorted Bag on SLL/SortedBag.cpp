#include "SortedBag.h"
#include "SortedBagIterator.h"


SortedBag::SortedBag(Relation r) {
	relation = r;
	bag_size = 0;
	head = NULL;
	tail = NULL;
}
// BC = WC = TC = Theta(1)

void SortedBag::add(TComp e) {
	if (head == NULL) {
		Node* new_node = new Node;
		new_node->value.first = e;
		new_node->value.second = 1;
		new_node->previous = new_node->next = NULL;
		head = tail = new_node;
		bag_size++;
		return;
	}
	Node* current_node = head;
	while (current_node != NULL) {
		if (current_node->value.first == e) {
			current_node->value.second++;
			bag_size++;
			return;
		}

		if (relation(e, current_node->value.first)) {
			Node* new_node = new Node;
			new_node->value.first = e;
			new_node->value.second = 1;
			new_node->next = current_node;
			if (current_node->previous != NULL) {
				current_node->previous->next = new_node;
			}
			else
				head = new_node;

			new_node->previous = current_node->previous;
			current_node->previous = new_node;
			bag_size++;
			return;
		}

		current_node = (Node*)current_node->next;
	}
	Node* new_node = new Node;
	new_node->value.first = e;
	new_node->value.second = 1;
	tail->next = new_node;
	new_node->previous = tail;
	new_node->next = NULL;
	tail = new_node;
	bag_size++;
}
// BC = Theta(1) - the element needs to be added at the head of the list
// WC = Theta(bag_size) - the element needs to be added at the tail of the list
// TC = O(bag_size)


bool SortedBag::remove(TComp e) {
	if (head == NULL)
		return false;
	if (head->value.first == e) {
		if (head->value.second == 1) {
			Node* node = head;
			head = head->next;
			if (head != NULL)
				head->previous = NULL;
			else
				tail = NULL;
			delete node;
		}
		else
			head->value.second--;
		bag_size--;
		return true;
	}

	Node* current_node;
	current_node = head->next;
	while (current_node != NULL) {
		if (!relation(current_node->value.first, e))
			return false;
		if (current_node->value.first != e)
			current_node = current_node->next;
		else {
			if (current_node->value.second == 1) {
				current_node->previous->next = current_node->next;
				if (current_node->next != NULL)
					current_node->next->previous = current_node->previous;
				else
					tail = current_node->previous;
				delete current_node;
			}
			else
				current_node->value.second--;
			bag_size--;
			return true;
		}
	}
	return false;
}
// BC = Theta(1) - the element is found at the head of the list
// WC = Theta(bag_size) - the element is at the tail of the list or is not in the list but based on the relation is supposed to be at the tail
// TC = O(bag_size)


bool SortedBag::search(TComp elem) const {
	Node* current_node;
	current_node = head;
	while (current_node != NULL && relation(current_node->value.first, elem)) {
		if (current_node->value.first == elem)
			return true;
		current_node = current_node->next;
	}
	return false;
}
// BC = Theta(1) - the element is at the head of the list
// WC = Theta(bag_size) - the element is at the tail of the listor is not in the list but based on the relation is supposed to be at the tail
// TC = O(bag_size)


int SortedBag::nrOccurrences(TComp elem) const {
	Node* current_node = head;
	while (current_node != NULL && relation(current_node->value.first, elem)) {
		if (current_node->value.first == elem) {
			return current_node->value.second;
		}
		current_node = (Node*)current_node->next;
	}

	return 0;
}
// BC = Theta(1) - the element is at the head of the list
// WC = Theta(bag_size) - the element is at the tail of the list or is not in the list but based on the relation is supposed to be at the tail
// TC = O(bag_size)


int SortedBag::size() const {
	return bag_size;
}
// BC = WC = TC = Theta(1)


bool SortedBag::isEmpty() const {
	return bag_size == 0;
}
// BC = WC = TC = Theta(1)


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}
// BC = WC = TC = Theta(1)


SortedBag::~SortedBag() {
	Node* next_node;

	while (head != NULL) {
		next_node = head->next;
		delete head;
		head = next_node;
	}
}
// BC = WC = TC = Theta(bag_size)


void SortedBag::filter(Condition cond)
{
	Node* current_node = head;
	while (current_node != NULL) {
		if (!cond(current_node->value.first))
			if (current_node == head) {
				bag_size -= current_node->value.second;
				Node* node = head;
				head = head->next;
				if (head != NULL)
					head->previous = NULL;
				else
					tail = NULL;
				delete node;

				current_node = head;
				continue;
			}
			else {
				bag_size -= current_node->value.second;
				Node* node = current_node;
				current_node->previous->next = current_node->next;
				if (current_node->next != NULL)
					current_node->next->previous = current_node->previous;
				else
					tail = current_node->previous;
				current_node = current_node->next;
				delete node;
				continue;
			}
		current_node = current_node->next;
	}
}
// BC = WC = TC = Theta(number of nodes)