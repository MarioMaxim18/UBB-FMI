#include <iostream>
#include "ListIterator.h"

ListIterator::ListIterator(const SortedIndexedList &list): list{list}, current{list.list.head} {}

bool ListIterator::valid() const { return current != -1; }

void ListIterator::next() {
	if (!valid())
		throw std::runtime_error("Iterator not valid");
	current = list.list.next[current];
}

void ListIterator::first() {
	current = list.list.head;
}

TComp ListIterator::getCurrent() const {
	if (!valid())
		throw std::runtime_error("Iterator not valid");
	return list.list.elems[current];
}