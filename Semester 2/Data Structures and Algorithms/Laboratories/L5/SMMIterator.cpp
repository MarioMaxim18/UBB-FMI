#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <stack>
#include <iostream>
#include <exception>

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	first();
}

/*
 * Complexity:
 * - Best Case: Θ(1), if the map is empty.
 * - Worst Case: Θ(h), where h is the height of the tree.
 * - Total Complexity: O(h), where h is the height of the tree.
 */
void SMMIterator::first() {
    while (!inorderStack.empty()) {
        inorderStack.pop();
    }

    curNode = map.root;

    while (curNode != nullptr) {
        inorderStack.push(curNode);
        curNode = curNode->getLeftChild();
    }

    if (!inorderStack.empty()) {
        curNode = inorderStack.top();
    } else {
        curNode = nullptr;
    }
}

/*
 * Complexity:
 * - Best Case: Θ(1), if the node is nullptr.
 * - Worst Case: Θ(h), where h is the height of the tree.
 * - Total Complexity: O(h), where h is the height of the tree.
 */
void SMMIterator::pushLeft(Node* node)
{
	while(node !=  nullptr)
	{
		this->inorderStack.push(node);
		node = node->getLeftChild();
	}
}

/*
 * Complexity:
 * - Best Case: Θ(1), if there is no right subtree.
 * - Worst Case: Θ(h), where h is the height of the tree.
 * - Total Complexity: O(h), where h is the height of the tree.
 */
void SMMIterator::next(){
	if (!valid()) {
		throw std::out_of_range("Iterator is not valid");
	}

	curNode = inorderStack.top();
	inorderStack.pop();

	pushLeft(curNode->getRightChild());
}

/*
 * Complexity:
 * - Best Case: Θ(1)
 * - Worst Case: Θ(1)
 * - Total Complexity: Θ(1)
 */
bool SMMIterator::valid() const{
	return !inorderStack.empty();
}

/*
 * Complexity:
 * - Best Case: Θ(1)
 * - Worst Case: Θ(1)
 * - Total Complexity: Θ(1)
 */
TElem SMMIterator::getCurrent() const{
	if(!valid())
	{
		throw std::out_of_range("Iterator is not valid");
	}
	return this->curNode->getPair();
}
