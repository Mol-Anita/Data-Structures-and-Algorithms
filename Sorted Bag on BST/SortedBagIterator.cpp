#include "SortedBagIterator.h"
#include <exception>

using namespace std;


SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    stack = new BSTNode * [bag.size()];  
    index = 0;  
    count = 0;  
    current = nullptr;  
    first();  
}


SortedBagIterator::~SortedBagIterator() {
    delete[] stack;
}


TComp SortedBagIterator::getCurrent() {
    if (!valid())
        throw std::exception();
    return current->info;
}


bool SortedBagIterator::valid() {
    return current != nullptr;
}


void SortedBagIterator::next() {
    if (!valid())
        throw std::exception();

    if (count < current->frequency - 1) {
        count++;
    }
    else {
        count = 0;
        if (current->rightChild == nullptr) {
            current = nullptr;
        }
        else {
            if (current->rightChild != nullptr) {
                current = current->rightChild;
                while (current != nullptr) {
                    stack[index++] = current;
                    current = current->leftChild;
                }
            }

            if (index != 0) {
                current = stack[--index];
            }
            else {
                current = nullptr;  
            }
        }
    }
}


void SortedBagIterator::first() {
    index = 0;
    count = 0;
    current = bag.root;
    while (current != nullptr) {
        stack[index++] = current;
        current = current->leftChild;
    }
    if (index != 0) {
        current = stack[--index];
    }
    else {
        current = nullptr;  
    }
}
