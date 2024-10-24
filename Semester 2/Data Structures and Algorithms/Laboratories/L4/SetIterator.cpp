#include "SetIterator.h"
#include "Set.h"
#include <exception>

SetIterator::SetIterator(const Set& m) : set(m)
{
	this->capacity = this->set.capacity;
	this->first();
}


void SetIterator::first() {
	this->index = 0;
	while (this->index < this->capacity && (this->set.hashTable[this->index] == this->set.empty || this->set.hashTable[this->index] == this->set.deleted))
	{
		this->index++;
	}
}


void SetIterator::next() {
	if (!valid())
	{
		throw std::exception();
	}
	this->index++;
	while (valid() && (this->set.hashTable[this->index] == this->set.empty || this->set.hashTable[this->index] == this->set.deleted))
	{
		this->next();
	}
}


TElem SetIterator::getCurrent()
{
	if (valid())
	{
		return this->set.hashTable[this->index];
	}
	else 
	{
		throw std::exception();
	}
}

bool SetIterator::valid() const 
{
	return this->index < this->capacity && this->index >= 0;
}



