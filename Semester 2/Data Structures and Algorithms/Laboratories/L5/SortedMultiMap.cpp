#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

Node::Node(Node *leftChild, Node *rightChild, TElem pair)
{
	this->leftChild = leftChild;
	this->rightChild = rightChild;
	this->pair = pair;
}

SortedMultiMap::SortedMultiMap(Relation r)
{
	this->root = nullptr;
	this->rel = r;
	this->sz = 0;
}

/*
 * Complexity:
 * - Best Case: Θ(1), when the current node is nullptr and a new node is created
 * - Worst Case: Θ(h), where h is the height of the tree
 * - Total Complexity: O(h), where h is the height of the tree
 */
Node *SortedMultiMap::addRec(Node *curNode, TKey c, TValue v)
{
	if (curNode == nullptr)
	{
		curNode = new Node(nullptr, nullptr, make_pair(c, v));
	}
	else if (this->rel(c, curNode->pair.first))
		curNode->leftChild = addRec(curNode->leftChild, c, v);
	else
		curNode->rightChild = addRec(curNode->rightChild, c, v);

	return curNode;
}

/*
 * Complexity:
 * - Best Case: Θ(1), when the tree is empty and a new root is created
 * - Worst Case: Θ(h), where h is the height of the tree
 * - Total Complexity: O(h), where h is the height of the tree
 */
void SortedMultiMap::add(TKey c, TValue v)
{
	this->root = addRec(this->root, c, v);
	++this->sz;
}

/*
 * Complexity:
 * - Best Case: Θ(1), when the key is found at the first node
 * - Worst Case: Θ(n), where n is the number of nodes in the tree (degenerate tree)
 * - Total Complexity: O(n), where n is the number of nodes in the tree
 */
void SortedMultiMap::searchRec(Node *curNode, TKey c, vector<TValue> &values) const
{
	if (curNode != nullptr)
	{
		if (this->rel(curNode->pair.first, c))
		{
			if (curNode->pair.first == c)
			{
				values.push_back(curNode->pair.second);
				searchRec(curNode->leftChild, c, values);
			}
			else
				searchRec(curNode->rightChild, c, values);
		}
		else
			searchRec(curNode->leftChild, c, values);
	}
}

/*
 * Complexity:
 * - Best Case: Θ(1), when the key is found at the first node
 * - Worst Case: Θ(n), where n is the number of nodes in the tree (degenerate tree)
 * - Total Complexity: O(n), where n is the number of nodes in the tree
 */
vector<TValue> SortedMultiMap::search(TKey c) const
{

	vector<TValue> values;
	searchRec(this->root, c, values);
	return values;
}

/*
 * Complexity:
 * - Best Case: Θ(1), when the current node is the leftmost node
 * - Worst Case: Θ(h), where h is the height of the tree
 * - Total Complexity: O(h), where h is the height of the tree
 */
Node *SortedMultiMap::findMin(Node *curNode)
{
	if (curNode == nullptr)
		return nullptr;
	else
	{
		while (curNode->leftChild != nullptr)
			curNode = curNode->leftChild;
		return curNode;
	}
}

/*
 * Complexity:
 * - Best Case: Θ(1), when the element is found at the first node
 * - Worst Case: Θ(h), where h is the height of the tree
 * - Total Complexity: O(h), where h is the height of the tree
 */
Node *SortedMultiMap::removeRec(Node *curNode, TKey c, TValue v)
{
	if (curNode == nullptr)
	{
		return curNode;
	}

	if (this->rel(c, curNode->pair.first))
	{
		if (c != curNode->pair.first)
		{
			curNode->leftChild = removeRec(curNode->leftChild, c, v);
		}
		else if (curNode->pair.second != v)
		{
			curNode->leftChild = removeRec(curNode->leftChild, c, v);
		}
		else
		{
			if (curNode->leftChild != nullptr && curNode->rightChild != nullptr)
			{
				Node *temp = findMin(curNode->rightChild);
				curNode->pair = temp->pair;
				curNode->rightChild = removeRec(curNode->rightChild, temp->pair.first, temp->pair.second);
			}
			else if (curNode->leftChild == nullptr)
			{
				Node *temp = curNode->rightChild;
				delete curNode;
				return temp;
			}
			else
			{
				Node *temp = curNode->leftChild;
				delete curNode;
				return temp;
			}
		}
	}
	else
	{
		curNode->rightChild = removeRec(curNode->rightChild, c, v);
	}

	return curNode;
}

/*
 * Complexity:
 * - Best Case: Θ(1), when the element is found and removed immediately
 * - Worst Case: Θ(n), where n is the number of nodes in the tree
 * - Total Complexity: O(n), where n is the number of nodes in the tree
 */
bool SortedMultiMap::remove(TKey c, TValue v)
{
	vector<TValue> values = search(c);
	for (int i = 0; i < values.size(); ++i)
		if (values[i] == v)
		{
			this->root = removeRec(this->root, c, v);
			--this->sz;
			return true;
		}
	return false;
}

/*
 * Complexity:
 * - Best Case: Θ(1), directly returns the size
 * - Worst Case: Θ(1), directly returns the size
 * - Total Complexity: Θ(1)
 */
int SortedMultiMap::size() const
{
	return this->sz;
}

/*
 * Complexity:
 * - Best Case: Θ(1), directly checks the size
 * - Worst Case: Θ(1), directly checks the size
 * - Total Complexity: Θ(1)
 */
bool SortedMultiMap::isEmpty() const
{
	return this->sz == 0;
}

/*
 * Complexity:
 * - Best Case: Θ(1), creating an iterator object
 * - Worst Case: Θ(1), creating an iterator object
 * - Total Complexity: Θ(1)
 */
SMMIterator SortedMultiMap::iterator() const
{
	return SMMIterator(*this);
}

/*
 * Complexity:
 * - Best Case: Θ(n), where n is the number of nodes in the subtree.
 * - Worst Case: Θ(n), where n is the number of nodes in the subtree.
 * - Total Complexity: Θ(n), where n is the number of nodes in the subtree.
 */
void SortedMultiMap::deleteAll(Node *node) {
    if (node != nullptr) {
        deleteAll(node->leftChild);  
        deleteAll(node->rightChild); 
        delete node; 
    }
}

/*
 * Complexity:
 * - Best Case: Θ(n), where n is the number of nodes in the tree.
 * - Worst Case: Θ(n), where n is the number of nodes in the tree.
 * - Total Complexity: Θ(n), where n is the number of nodes in the tree.
 */
SortedMultiMap::~SortedMultiMap()
{
	deleteAll(this->root);
}
