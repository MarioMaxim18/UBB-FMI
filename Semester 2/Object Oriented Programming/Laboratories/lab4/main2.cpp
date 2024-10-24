    #include <iostream>

    using namespace std;

    class Deque {
    public:
        Deque(int capacity = 10):m_data{new int[capacity]}, m_length{0}, m_front(0), m_back(9), m_capacity{capacity}{}

        int length() const {return m_length;}
        int capacity() const {return m_capacity;}

        friend ostream& operator<<(ostream& os, const Deque& d) {
            for (int i = 0; i < d.m_length; ++i) {
                os << d.m_data[i] << " ";
            }
            return os;
        }

        ~Deque(){
            if(m_data){
                delete[] m_data;
                m_data = nullptr;
            }
        }

        Deque(const Deque& other) {
            m_length = other.m_length;
            m_capacity = other.m_capacity;
            m_front = other.m_front;
            m_back = other.m_back;
            m_data = new int[m_capacity]();
            for (int i = 0; i < m_length; ++i) {
                m_data[i] = other.m_data[i];
            }
        }

        Deque& operator=(const Deque& other) {
            if(this != &other){
                if(m_data)
                    delete[] m_data;

                m_length = other.m_length;
                m_capacity = other.m_capacity;
                m_front = other.m_front;
                m_back = other.m_back;
                m_data = new int[m_capacity];
                for(int i{0}; i < m_length; ++i)
                    m_data[i] = other.m_data[i];
            }
            return *this;
        }

        void push_front(int value) {
            if (m_length == m_capacity) {
                resize(2 * m_capacity);
            }
            m_front = (m_front - 1 + m_capacity) % m_capacity;
            m_data[m_front] = value;
            ++m_length;
        }

        void pop_front() {
            if (m_length == 0) {
                throw out_of_range("Deque is empty");
            }
            m_front = (m_front + 1) % m_capacity;
            --m_length;
            if (m_length > 0 && m_length == m_capacity / 4) {
                resize(m_capacity / 2);
            }
        }

        void push_back(int value) {
            if (m_length == m_capacity) {
                resize(2 * m_capacity);
            }
            m_back = (m_back + 1) % m_capacity;
            m_data[m_back] = value;
            ++m_length;
        }

        void pop_back() {
            if (m_length == 0) {
                throw out_of_range("Deque is empty");
            }
            m_back = (m_back - 1 + m_capacity) % m_capacity;
            --m_length;
            if (m_length > 0 && m_length == m_capacity / 4) {
                resize(m_capacity / 2);
            }
        }

    private:
        int* m_data;
        int m_length;
        int m_capacity;
        int m_front;
        int m_back;

        void resize(int new_capacity) {
            int* new_data = new int[new_capacity]();
            for (int i = 0; i < m_length; ++i) {
                new_data[i] = m_data[(m_front + i) % m_capacity];
            }
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
            m_front = 0;
            m_back = m_length - 1;
        }
    };

    int main() {
        Deque d;

        d.push_front(1);
        d.push_back(2);
        cout << d << "\n";  // Output: 1 2

    //    d.pop_front();
    //    d.pop_back();
    //    cout << d << "\n";  // Output: (empty line)
        return 0;
    }