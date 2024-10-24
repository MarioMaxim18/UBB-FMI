    #include "Set.h"
    #include "SetITerator.h"
    #include <cmath>

    // Complexity: Theta(1)
    int Set::hCode(int k) const
    {
        return abs(k);
    }

    // Complexity: Theta(1)
    int Set::h1(TElem k) const
    {
        return hCode(k) % this->capacity;
    }

    // Complexity: Theta(1)
    int Set::h2(TElem k) const
    {
        return 1 + (hCode(k) % (this->capacity - 1));
    }

    // Complexity: Theta(1)
    int Set::h(TElem k, int i) const
    {
        return (h1(k) + i * h2(k)) % this->capacity;
    }

    // Complexity: O(√x)
    bool Set::isPrime(int x)
    {
        if (x < 2 || (x > 2 && x % 2 == 0)) {
            return false;
        }
        for (int d = 3; d * d <= x; d = d + 2) {
            if (x % d == 0) {
                return false;
            }
        }
        return true;
    }

    int Set::firstPrimeGreaterThan(int x)
    {
        x++;
        while (!isPrime(x)) {
            x++;
        }
        return x;
    }

    // Complexity: Theta(maxCapacity)
    Set::Set()
    {
        this->capacity = maxCapacity;
        this->length = 0;
        this->empty = -1111;
        this->deleted = -1112;
        this->hashTable = new TElem[maxCapacity];
        for (int i = 0; i < maxCapacity; i++)
        {
            this->hashTable[i] = this->empty;
        }
    }

    // Complexity:  BC = Theta(1)
    //				WC = O(oldCap + capacity)
    bool Set::add(TElem elem)
    {
        if (this->length == this->capacity)
        {
            int primeNumber = firstPrimeGreaterThan(this->capacity * 2);
            int oldCapacity = this->capacity;
            this->capacity = primeNumber;
            TElem* oldHashTable = this->hashTable;
            this->hashTable = new TElem[capacity];
            this->length = 0;
            for (int i = 0; i < this->capacity; i++)
            {
                this->hashTable[i] = this->empty;
            }
            for (int i = 0; i < oldCapacity; i++)
            {
                this->add(oldHashTable[i]);
            }
            delete[] oldHashTable;
        }
        int i = 0;
        int position = h(elem, i);
        while (i < this->capacity && this->hashTable[position] != this->empty && this->hashTable[position] != this->deleted)
        {
            if (this->hashTable[position] == elem)
            {
                return false;
            }
            i++;
            position = h(elem, i);
        }
        this->hashTable[position] = elem;
        this->length++;
        return true;
    }

    // Complexity : BC = Theta(1)
    //				WC = O(capacity)
    bool Set::remove(TElem elem)
    {
        int i = 0;
        int position = h(elem, i);
        while (i < this->capacity && this->hashTable[position] != elem && this->hashTable[position] != this->empty)
        {
            i++;
            position = h(elem, i);
        }
        if (i == this->capacity || this->hashTable[position] == this->empty)
            return false;

        this->hashTable[position] = this->deleted;
        this->length--;
        return true;
    }

    // Complexity : BC = Theta(1)
    //				WC = O(capacity)
    bool Set::search(TElem elem) const
    {
        int i = 0;
        int position = h(elem, i);
        while (i < this->capacity && this->hashTable[position] != elem && this->hashTable[position] != this->empty)
        {
            i++;
            position = h(elem, i);
        }
        if (i == this->capacity || this->hashTable[position] == this->empty)
            return false;
        return true;
    }

    // Complexity: Theta(1)
    int Set::size() const
    {
        return this->length;
    }

    // Complexity: Theta(1)
    bool Set::isEmpty() const
    {
        return this->length == 0;
    }


    // Complexity: Theta(1)
    Set::~Set()
    {
        delete[] this->hashTable;
    }

    // Complexity: Theta(1)
    SetIterator Set::iterator() const {
        return SetIterator(*this);
    }


