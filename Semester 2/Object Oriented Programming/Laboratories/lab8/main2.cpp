#include <iostream>

using namespace std;

template <typename T>
void swapValue(T& a, T& b) {
    swap(a, b);
}

int main() {
    int a = 5, b = 10;
    cout << "a = " << a << ", b = " << b << endl;
    swapValue(a, b);
    cout << "a = " << a << ", b = " << b << endl;

    string str1 = "Hello", str2 = "World";
    cout << "str1 = " << str1 << ", str2 = " << str2 << endl;
    swapValue(str1, str2);
    cout << "str1 = " << str1 << ", str2 = " << str2 << endl;

    return 0;
}