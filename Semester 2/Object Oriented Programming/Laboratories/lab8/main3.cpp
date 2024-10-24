#include <iostream>
#include <string>

using namespace std;
template<typename T>
T findmax(const T& a, const T& b) {
    return (a < b) ? b : a;
}

int main() {
    int int1 = 2, int2 = 3;
    string str1 = "ab", str2 = "abc";
    double double1 = 1.2, double2 = 2.3;
    cout << "Max of " << int1 << " and " << int2 << " is: " << findmax(int1, int2) << "\n";
    cout << "Max of " << double1 << " and " << double2 << " is: " << findmax(double1, double2) << "\n";
    cout << "Max of " << str1 << " and " << str2 << " is: " << findmax(str1, str2) << "\n";
    return 0;
}

