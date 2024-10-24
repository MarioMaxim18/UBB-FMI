#pragma once

#include "SortedMultiMap.h"
#include <stack>


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	stack<Node*> inorderStack;
	Node* curNode;

public:
	void first();
	void next();
	void pushLeft(Node* node);
	bool valid() const;
   	TElem getCurrent() const;
};

