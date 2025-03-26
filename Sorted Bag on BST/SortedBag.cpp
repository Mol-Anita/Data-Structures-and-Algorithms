#include "SortedBag.h"
#include "SortedBagIterator.h"

BSTNode* SortedBag::initNode(TComp e) {
    BSTNode* newNode = new BSTNode;
    newNode->info = e;
    newNode->frequency = 1;
    newNode->leftChild = nullptr;
    newNode->rightChild = nullptr;
    return newNode;
}
//BC = WC = TC = Theta(1)

SortedBag::SortedBag(Relation r) {
    relation = r;
    root = nullptr;
}
//BC = WC = TC = Theta(1)

void SortedBag::add(TComp e) {
    if (root == nullptr) {
        root = initNode(e);
        return;
    }

    BSTNode* current = root;
    BSTNode* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (current->info == e) {
            current->frequency++;
            return;
        }
        if (relation(current->info, e)) {
            current = current->rightChild;
        }
        else {
            current = current->leftChild;
        }
    }

    BSTNode* newNode = initNode(e);
    if (relation(parent->info, e)) {
        parent->rightChild = newNode;
    }
    else {
        parent->leftChild = newNode;
    }
}
//BC = Theta(1) - if we have at the root the element we are inserting
//WC = Theta(n) - we have a skewed tree and we have to add a new element to its "end"
//TC = O(n)

void SortedBag::inOrderTraversal(BSTNode* node, int& count) const {
    if (node != nullptr) {
        inOrderTraversal(node->leftChild, count);
        count += node->frequency;
        inOrderTraversal(node->rightChild, count);
    }
}

void SortedBag::removeNode(BSTNode* node, BSTNode* parent) {
    BSTNode* nodeToDelete = node;

    if (node->leftChild == nullptr && node->rightChild == nullptr) {  // Case 1: Node is a leaf
        if (parent == nullptr) {
            root = nullptr;
        }
        else if (parent->leftChild == node) {
            parent->leftChild = nullptr;
        }
        else {
            parent->rightChild = nullptr;
        }
    }
    else if (node->leftChild == nullptr) {  // Case 2: Node has only a right child
        if (parent == nullptr) {
            root = node->rightChild;
        }
        else if (parent->leftChild == node) {
            parent->leftChild = node->rightChild;
        }
        else {
            parent->rightChild = node->rightChild;
        }
    }
    else if (node->rightChild == nullptr) {  // Case 2: Node has only a left child
        if (parent == nullptr) {
            root = node->leftChild;
        }
        else if (parent->leftChild == node) {
            parent->leftChild = node->leftChild;
        }
        else {
            parent->rightChild = node->leftChild;
        }
    }
    else {  // Case 3: Node has two children
        BSTNode* maxNode = node->leftChild;
        BSTNode* maxNodeParent = node;

        while (maxNode->rightChild != nullptr) {
            maxNodeParent = maxNode;
            maxNode = maxNode->rightChild;
        }

        node->info = maxNode->info;
        node->frequency = maxNode->frequency;

        if (maxNodeParent->leftChild == maxNode) {
            maxNodeParent->leftChild = maxNode->leftChild;
        }
        else {
            maxNodeParent->rightChild = maxNode->leftChild;
        }

        nodeToDelete = maxNode;
    }

    delete nodeToDelete;
}


bool SortedBag::remove(TComp e) {
    BSTNode* currentNode = root;
    BSTNode* parent = nullptr;

    while (currentNode != nullptr) {
        if (currentNode->info == e) {
            if (currentNode->frequency > 1) {
                currentNode->frequency--;
                return true;
            }
            else {
                break;
            }
        }
        parent = currentNode;
        if (relation(currentNode->info, e)) {
            currentNode = currentNode->rightChild;
        }
        else {
            currentNode = currentNode->leftChild;
        }
    }

    if (currentNode == nullptr)
        return false;

    removeNode(currentNode, parent);
    return true;
}
//BC = Theta(1) - removing an element found at the root which has frequency greater than 1 after removal
//WC = Theta(n) - removing the root node when the tree is unbalanced and we have to search for the maximum
// element from the left subtree a lot
//TC = O(n)

bool SortedBag::search(TComp elem) const {
    BSTNode* currentNode = root;
    while (currentNode != nullptr) {
        if (currentNode->info == elem)
            return true;
        if (relation(currentNode->info, elem))
            currentNode = currentNode->rightChild;
        else
            currentNode = currentNode->leftChild;
    }
    return false;
}
//BC = Theta(1) - finding the element we are looking for at the root
//WC = Theta(n) - searching for a leaf node in a tree with height n, or an element that isn't in the list
//TC = O(n)

int SortedBag::nrOccurrences(TComp elem) const {
    BSTNode* current = root;
    while (current != nullptr) {
        if (current->info == elem)
            return current->frequency;
        if (relation(current->info, elem))
            current = current->rightChild;
        else
            current = current->leftChild;
    }
    return 0;
}
//BC = Theta(1) - we find the element at the root
//WC = Theta(n) - searching for a leaf node in a tree with height n,or an element that isn't in the list
//TC = O(n)

int SortedBag::size() const {
    int count = 0;
    inOrderTraversal(root, count);
    return count;
}
//BC = WC = TC = Theta(n)

bool SortedBag::isEmpty() const {
    return root == nullptr;
}
//BC = WC = TC = Theta(1)

SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}
//BC = WC = TC = Theta(1)


void SortedBag::deleteTree(BSTNode* node) {
    if (node == nullptr) {
        return;
    }
    deleteTree(node->leftChild);
    deleteTree(node->rightChild);
    delete node;
}
//BC = WC = TC = Theta(n)


SortedBag::~SortedBag() {
    deleteTree(root);
}
//BC = WC = TC = Theta(n)

int SortedBag::getRange() const
{
    if (root == nullptr) {
        return -1;
    }

    int min, max;
    BSTNode* current = root;
    while (current->leftChild != nullptr){
        current = current->leftChild;
    }
    min = current->info;

    current = root;
    while (current->rightChild != nullptr) {
        current = current->rightChild;
    }
    max = current->info;
    return max - min;
}
//BC = Theta(log2n) - the tree has height log2n
//WC = Theta(n) - the tree has height n
//TC = O(n)
