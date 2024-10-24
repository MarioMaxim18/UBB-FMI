#include <ostream>
#include <iostream>

using namespace std;

class Array {
public:
// precondition capacity > 0
    Array(unsigned int capacity = 10):m_data{new int[capacity]}, m_length{0}, m_capacity{capacity}{}

    unsigned int length() const {return m_length;}
    unsigned int capacity() const {return m_capacity;}

    bool append(int elem) {
        if (m_length < m_capacity) {
            m_data[m_length++] = elem;
            return true;
        }
        return false;
    }

    // precondition: i < m_capacity
    int& at(unsigned int i){
        return m_data[i];
    }

    friend ostream& operator<<(ostream& os, const Array& a){
        for(unsigned int i {0}; i < a.m_length; i++)
            os <<a.m_data[i] << " ";
        os << endl;
        return os;
    }

    ~Array(){
        if(m_data){
            delete[] m_data;
            m_data = nullptr;
        }
    }

    Array(const Array& other){
        m_capacity = other.m_capacity;
        m_length = other.m_length;
        m_data = new int[m_capacity]();
        for(int i{0}; i < m_length; i++)
            m_data[i] = other.m_data[i];
    }

    Array& operator=(const Array& other){
        if(this != &other){ // self assignment check
            // release the memory
            if(m_data)
                delete[] m_data;

            // deep copy
            m_capacity = other.m_capacity;
            m_length = other.m_length;
            m_data = new int[m_capacity]();
            for(int i{0}; i < m_length; i++)
                m_data[i] = other.m_data[i];
        }
        // returning the current object
        // this is a pointer, so we need to dereference it
        return *this;
    }

private:
    int* m_data;
    unsigned int m_length;
    unsigned int m_capacity;
};

int main() {
    Array a1{10};
    a1.append(1);
    a1.append(2);
    a1.append(3);
    a1.append(4);
    a1.append(5);

    cout<<"Array 1: "<<a1;
    Array a2{a1};
    cout<<"Array 2: "<<a2;

    Array a3{};

    a3 = a1;
    cout<<"Array 3: "<<a3;
    a2.at(0) = 10;

    cout<<"a2[0] = 10\nNow the arrays are:"<<endl;
    cout<<"Array 1: "<<a1;
    cout<<"Array 2: "<<a2;
    cout<<"Array 3: "<<a3;

    return 0;
}