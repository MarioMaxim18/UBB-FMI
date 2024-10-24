#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

class Node
{
private:
    Node *leftChild;
    Node *rightChild;
    TElem pair;
public:
    friend class SortedMultiMap;
    Node(Node *rightChild, Node *leftChild, TElem pair);
    inline Node* getLeftChild(){return this->leftChild;}
    inline Node* getRightChild(){return this->rightChild;}
    inline TElem getPair(){return this->pair;}
};

class SortedMultiMap {
	friend class SMMIterator;
private:
	Node *root;
    Relation rel;
    int sz;

public:

    // constructor
    SortedMultiMap(Relation r);

    

    Node* addRec(Node *curNode, TKey c, TValue v);
	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);


    void searchRec(Node *curNode, TKey c, vector<TValue> &values) const;
	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

    Node* removeRec(Node *curNode, TKey c, TValue v);
    Node* findMin(Node *curNode);
    Node* findParent(Node *curNode);
    Node* findSuccessor(Node *curNode);
	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    void deleteAll(Node* node);

    // destructor
    ~SortedMultiMap();
};
